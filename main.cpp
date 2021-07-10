#include "LedMatrix.cpp"
#include <unistd.h>

using namespace std;

int main() {
  cout << "************************\n";
  cout << "*** Command Renderer ***\n";
  cout << "************************\n\n";

  LedMatrix led_matrix;
  struct color some_color {
    255, 0, 0
  };
  led_matrix.fill(some_color);
  led_matrix.send_matrix();
  led_matrix.print();
  

  sleep(5);
  some_color =  {
    0, 255, 0 
  };
  led_matrix.fill(some_color);
  led_matrix.send_matrix();
  led_matrix.print();

  sleep(5);
  some_color =  {
    0, 0, 255 
  };
  led_matrix.fill(some_color);
  led_matrix.send_matrix();
  led_matrix.print();

//  struct color_hsv some_hsv {
//    65.0, 0.4, 0.35
//  };
//  led_matrix.fill(some_hsv);
//  led_matrix.print();
//  struct color_hsv dhsv {
//    5.0, 0.1, 0.1
//  };
//  led_matrix.increase_hsv(dhsv);
//  led_matrix.print();
//  led_matrix.send_matrix();
//  sleep(1);



  return 0;
}
