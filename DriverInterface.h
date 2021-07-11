#include <netinet/in.h>
#define SIMULATE

class DriverInterface{
    public:
        DriverInterface();
        ~DriverInterface();
        void write_matrix(unsigned char matrix[30][3], unsigned int size);
    private:
        #ifdef SIMULATE
        int sockfd;
        void create_socket();
        struct sockaddr_in     servaddr;
        #else
        int fd;
        #endif

};
