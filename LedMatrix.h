#define NLEDS 30
#include "DriverInterface.cpp"


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
  LedMatrix();
  // TODO: use << operator
  void print();
  unsigned int get_size() { return NLEDS; }

  // efects
  void fill(struct color color_aux);

  void fill(struct color_hsv hsv);

  void increase_hsv(const struct color_hsv &dhsv);

  void send_matrix();

private:
  void RGBtoHSV(const struct color &c, struct color_hsv &hsv);

  void HSVtoRGB(struct color &c, const struct color_hsv &hsv);
  unsigned char matrix[NLEDS][3] = {{1, 2, 3}, {1, 2, 3}};
  DriverInterface driverInterface;

};
