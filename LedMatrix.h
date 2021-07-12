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
  void setPixel(unsigned int pos, struct color color_aux);

  void fill(struct color color_aux);

  void fill(struct color_hsv hsv);

  void increase_hsv(const struct color_hsv &dhsv);

  void send_matrix();
  unsigned int get_millis();
  
  void fill_transition_pos(unsigned int duration_ms, unsigned int init_pos=0, unsigned int end_pos=0);
  void reset_time_base();
  unsigned int time_base =0;

private:
  void RGBtoHSV(const struct color &c, struct color_hsv &hsv);

  void HSVtoRGB(struct color &c, const struct color_hsv &hsv);
  unsigned char matrix[NLEDS][3] = {{1, 2, 3}, {1, 2, 3}};
  DriverInterface driverInterface;

  // TODO: make template for support more arguments?
  float map_from_one_range_to_another(double in,float  in_min,float  in_max,float  out_min,float  out_max);

};
