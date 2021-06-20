#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

// for file open
//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>

// C++ way
#include <fstream>
#include <cstring>

#define NLEDS 20

using namespace std;

struct color {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

struct color_hsv {
  float hue;
  float saturation;
  float value;
};

class LedMatrix {
public:
  LedMatrix(){};
  unsigned char matrix[NLEDS][3] = {{1, 2, 3}, {1, 2, 3}};
  // TODO: use << operator
  void print() {
    for (unsigned int i = 0; i < NLEDS; i++) {
      for (unsigned char j = 0; j < 3; j++) {
        printf("%u\t", (unsigned int)matrix[i][j]);
      }
      printf("\n");
    }
  };
  unsigned int get_size() { return NLEDS; }

  // efects
  void fill(struct color color_aux) {
    for (unsigned int i = 0; i < get_size(); i++) {
      matrix[i][0] = color_aux.red;
      matrix[i][1] = color_aux.green;
      matrix[i][2] = color_aux.blue;
    }
  };

  void fill(struct color_hsv hsv) {
    struct color color_aux;
    HSVtoRGB(color_aux, hsv);
    fill(color_aux);
  }

  void increase_hsv(const struct color_hsv &dhsv) {
    struct color c;
    struct color_hsv hsv;
    for (unsigned int i = 0; i < get_size(); i++) {
      c.red = matrix[i][0];
      c.green = matrix[i][1];
      c.blue = matrix[i][2];
      RGBtoHSV(c, hsv);
      hsv.hue += dhsv.value;
      hsv.saturation += dhsv.saturation;
      hsv.value += dhsv.value;
      HSVtoRGB(c, hsv);
      matrix[i][0] = c.red;
      matrix[i][1] = c.green;
      matrix[i][2] = c.blue;
    }
  }

//  void send_led_matrix(){
//      char str1[100];
//      int fd = open("/dev/rpmsg_pru30",O_APPEND);
//      if (fd==-1){
//          printf("Error abriendo el archivo\n");
//          exit(-1);
//      }
//      for (unsigned int i = 0; i < get_size(); i++){
//          // TODO: investigar una forma C++ más compacta de hacer esto
//          sprintf(str1, "%d %d %d %d\n", i, matrix[i][0], matrix[i][1], matrix[i][2]);
//          write(fd, str1, sizeof(str1));
//      }
//      sprintf(str1, "%d %d %d %d\n");
//      // send render command
//  }
  void send_matrix(){
      std::ofstream  file;
      file.open("/dev/rpmsg_pru30", std::ios_base::app);
      if (file.fail())
          throw std::ios_base::failure(std::strerror(errno));
      for (unsigned int i = 0; i < get_size(); i++){
            file << i << " " << matrix[i][0] << " "  << matrix[i][1] << " "  << matrix[i][2] << "\n" ;
      }
      // send render command
      file <<  "-1 0 0 0\n" ;
  }

private:
  void RGBtoHSV(const struct color &c, struct color_hsv &hsv) {

    float fR = (float)c.red / 255.0;
    float fG = (float)c.green / 255.0;
    float fB = (float)c.blue / 255.0;

    float &fH = hsv.hue;
    float &fS = hsv.saturation;
    float &fV = hsv.value;

    float fCMax = max(max(fR, fG), fB);
    float fCMin = min(min(fR, fG), fB);
    float fDelta = fCMax - fCMin;

    if (fDelta > 0) {
      if (fCMax == fR) {
        fH = 60 * (fmod(((fG - fB) / fDelta), 6));
      } else if (fCMax == fG) {
        fH = 60 * (((fB - fR) / fDelta) + 2);
      } else if (fCMax == fB) {
        fH = 60 * (((fR - fG) / fDelta) + 4);
      }

      if (fCMax > 0) {
        fS = fDelta / fCMax;
      } else {
        fS = 0;
      }

      fV = fCMax;
    } else {
      fH = 0;
      fS = 0;
      fV = fCMax;
    }

    if (fH < 0) {
      fH = 360 + fH;
    }
  }

  /*! \brief Convert HSV to RGB color space

    Converts a given set of HSV values `h', `s', `v' into RGB
    coordinates. The output RGB values are in the range [0, 1], and
    the input HSV values are in the ranges h = [0, 360], and s, v =
    [0, 1], respectively.

    \param fR Red component, used as output, range: [0, 1]
    \param fG Green component, used as output, range: [0, 1]
    \param fB Blue component, used as output, range: [0, 1]
    \param fH Hue component, used as input, range: [0, 360]
    \param fS Hue component, used as input, range: [0, 1]
    \param fV Hue component, used as input, range: [0, 1]

  */
  void HSVtoRGB(struct color &c, const struct color_hsv &hsv) {

    const float &fH = hsv.hue;
    const float &fS = hsv.saturation;
    const float &fV = hsv.value;

    float fR = 0;
    float fG = 0;
    float fB = 0;

    float fC = fV * fS; // Chroma
    float fHPrime = fmod(fH / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = fV - fC;

    if (0 <= fHPrime && fHPrime < 1) {
      fR = fC;
      fG = fX;
      fB = 0;
    } else if (1 <= fHPrime && fHPrime < 2) {
      fR = fX;
      fG = fC;
      fB = 0;
    } else if (2 <= fHPrime && fHPrime < 3) {
      fR = 0;
      fG = fC;
      fB = fX;
    } else if (3 <= fHPrime && fHPrime < 4) {
      fR = 0;
      fG = fX;
      fB = fC;
    } else if (4 <= fHPrime && fHPrime < 5) {
      fR = fX;
      fG = 0;
      fB = fC;
    } else if (5 <= fHPrime && fHPrime < 6) {
      fR = fC;
      fG = 0;
      fB = fX;
    } else {
      fR = 0;
      fG = 0;
      fB = 0;
    }

    fR += fM;
    fG += fM;
    fB += fM;

    c.red = fR * 255.0;
    c.green = fG * 255.0;
    c.blue = fB * 255.0;
  }
};

int main() {
  cout << "************************\n";
  cout << "*** Command Renderer ***\n";
  cout << "************************\n\n";

  LedMatrix led_matrix;
  led_matrix.print();
  struct color some_color {
    0, 50, 200
  };
  led_matrix.fill(some_color);
  led_matrix.print();

  struct color_hsv some_hsv {
    65.0, 0.4, 0.35
  };
  led_matrix.fill(some_hsv);
  led_matrix.print();
  struct color_hsv dhsv {
    5.0, 0.1, 0.1
  };
  led_matrix.increase_hsv(dhsv);
  led_matrix.print();
  led_matrix.send_matrix();

  return 0;
}
