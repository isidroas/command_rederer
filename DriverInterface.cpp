// for file open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

// for tcp comms
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "DriverInterface.h"

#define PORT 50007 

using namespace std;

DriverInterface::DriverInterface() {
    std::cout << "Entering driver interface\n";
    #ifdef SIMULATE
//      fd = open("output.txt", O_WRONLY| O_CREAT, 0666);
      create_socket();
    #else
      // para escribir o leer en dispositivos es recomendable usar las funciones de más bajo nivel open y write
      fd = open("/dev/rpmsg_pru30", O_WRONLY);
        if (fd==-1){
            cout << "Error opening the file\n";
            exit(-1);
        }
    #endif
}

DriverInterface::~DriverInterface() {
   #ifdef SIMULATE
   close(sockfd);
   #else
   close(fd);
   #endif
}

void DriverInterface::write_matrix(unsigned char matrix[30][3], unsigned int size) {
    cout << "[DriverInterface::write_matrix] matrix[0][0]" << int(matrix[0][1]) << endl;


  char str1[50];
  for (unsigned int i = 0; i < size; i++) {
    int l = sprintf(str1, "%d %d %d %d\n", int(i), matrix[i][0], matrix[i][1], matrix[i][2]);
    cout << str1;
    #ifdef SIMULATE
        sendto(sockfd, (const char *)str1, l,
            MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                sizeof(servaddr));
    #else
        int res = write(fd,str1, l);
        if (res==-1){
            cout << "Error writing on file with error " << strerror(errno)<< endl;
            exit(-1);
        }
    #endif
  }
  // send render command
  #ifdef SIMULATE
    sendto(sockfd, (const char *)"-1 0 0 0", 9,
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
  #else
    write(fd,"-1 0 0 0\n", 9);
  #endif
}

void DriverInterface::create_socket() {
  
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  
    memset(&servaddr, 0, sizeof(servaddr));
      
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
      
  
}
