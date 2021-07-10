#define SIMULATE
// for file open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "DriverInterface.h"


using namespace std;

DriverInterface::DriverInterface() {
    std::cout << "Entering driver interface\n";
}

void DriverInterface::write_matrix(unsigned char matrix[30][3], unsigned int size) {
  // TODO: para escribir o leer en dispositivos es recomendable usar las funciones de más bajo nivel open y write

#ifdef SIMULATE
  int fd = open("./output.txt", O_WRONLY);
#else
  int fd = open("/dev/rpmsg_pru30", O_WRONLY);
#endif

  if (fd==-1){
      cout << "error al abrir el fichero\n";
      exit(-1);
  }
  char str1[50];
  for (unsigned int i = 0; i < size; i++) {
    // TODO: fix this not printing the number
    int l = sprintf(str1, "%d %d %d %d\n", i, matrix[i][0], matrix[i][1], matrix[i][2]);
    write(fd,str1, l);
  }
  // send render command
  write(fd,"-1 0 0 0\n", 9);
  close(fd);
}
