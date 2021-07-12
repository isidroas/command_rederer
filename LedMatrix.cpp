#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "LedMatrix.h"
#include <time.h>


#define NLEDS 30

using namespace std;


// Using initializer list
LedMatrix::LedMatrix(): driverInterface() {
    // Eliminé la siguiente línea porque esto es inicializar por asignación. 
    // El problema que se genera es que el destructor se ejecuta al principio
    // Supongo que cuando se sale de esta función.
    // Esta opción es flexible ya que admite los mismos argumentos que el costructor
//    driverInterface = DriverInterface();
}

void LedMatrix::print() {
  for (unsigned int i = 0; i < NLEDS; i++) {
    for (unsigned char j = 0; j < 3; j++) {
      std::cout << std::to_string(matrix[i][0]) << " "
                << std::to_string(matrix[i][1]) << " "
                << std::to_string(matrix[i][2]) << "\n";
    }
    printf("\n");
  }
};

// efects
void LedMatrix::fill(struct color color_aux) {
  for (unsigned int i = 0; i < get_size(); i++) {
    matrix[i][0] = color_aux.red;
    matrix[i][1] = color_aux.green;
    matrix[i][2] = color_aux.blue;
  }
};

void LedMatrix::setPixel(unsigned int pos, struct color color_aux){
    matrix[pos][0] = color_aux.red;
    matrix[pos][1] = color_aux.green;
    matrix[pos][2] = color_aux.blue;
};

//void setPixel

void LedMatrix::fill(struct color_hsv hsv) {
  struct color color_aux;
  HSVtoRGB(color_aux, hsv);
  fill(color_aux);
}

void LedMatrix::increase_hsv(const struct color_hsv &dhsv) {
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

void LedMatrix::send_matrix() {
    driverInterface.write_matrix(matrix, get_size());
}

void LedMatrix::RGBtoHSV(const struct color &c, struct color_hsv &hsv) {

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
void LedMatrix::HSVtoRGB(struct color &c, const struct color_hsv &hsv) {

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

unsigned int LedMatrix::get_millis() {
    struct timespec tm;
    int res = clock_gettime(CLOCK_REALTIME, &tm);
    if (res==-1){
        cout << "error in gettime" << endl;
        exit(-1);
    }
    return  tm.tv_sec*1e3 + tm.tv_nsec/1e6;
}

void LedMatrix::fill_transition_pos( unsigned int duration_ms, unsigned int init_pos, unsigned int end_pos) {
    // TODO: put target color
    if (end_pos==0){
        end_pos = get_size();
    }
    unsigned int pos = map_from_one_range_to_another( (double)((double)get_millis()-(double)time_base), 0, duration_ms, init_pos, end_pos);
    struct color c {100,100,100};
    for (unsigned int i=0; i< get_size(); i++){
        if (i<pos){
        setPixel(i, c);

        }

    }
}

float LedMatrix::map_from_one_range_to_another(double in ,float  in_min,float  in_max,float  out_min,float  out_max){
   float res = out_min + (out_max-out_min)/(in_max-in_min)*(in - in_min);
   if (res>out_max){
       res=out_max;
   }
   else if(res<out_min){
       res = out_min;
   }
   return res;
}
void LedMatrix::reset_time_base(){
    time_base = get_millis();
}
