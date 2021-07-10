#define SIMULATE
// for file open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

#include "DriverInterface.h"


using namespace std;

DriverInterface::DriverInterface() {
    std::cout << "Entering driver interface\n";
    #ifdef SIMULATE
      fd = open("output.txt", O_WRONLY| O_CREAT, 0666);
    #else
      // para escribir o leer en dispositivos es recomendable usar las funciones de más bajo nivel open y write
      fd = open("/dev/rpmsg_pru30", O_WRONLY);
    #endif
   if (fd==-1){
       cout << "Error opening the file\n";
       exit(-1);
   }
}

DriverInterface::~DriverInterface() {
  close(fd);
}

void DriverInterface::write_matrix(unsigned char matrix[30][3], unsigned int size) {
    cout << "[DriverInterface::write_matrix] matrix[0][0]" << int(matrix[0][1]) << endl;


  char str1[50];
  for (unsigned int i = 0; i < size; i++) {
    int l = sprintf(str1, "%d %d %d %d\n", int(i), matrix[i][0], matrix[i][1], matrix[i][2]);
    cout << str1;
    int res = write(fd,str1, l);
    if (res==-1){
//        char error_msg[1000];
//        perror(error_msg);
        cout << "Error writing on file with error " << strerror(errno)<< endl;
        exit(-1);
    }
  }
  // send render command
  write(fd,"-1 0 0 0\n", 9);
}
