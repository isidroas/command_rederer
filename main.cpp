#include <iostream>
#include <vector>
#include <array>
#define NLEDS 100

using namespace std;

class LedMatrix{
    public:
        LedMatrix(){};
        unsigned char matrix[NLEDS][3] = {{1,2,3}, {1,2,3}};
        // use << operator
        void print(){
            cout << "se entra en print\n";
            for(unsigned int i=0; i<NLEDS; i++){
                for(unsigned char j=0; j<3; j++){
                    cout << matrix[i][j]; 
                    printf("%d\t",matrix[i][j]);
                }
                printf("\n");
            }
        };
};

int main() {
    cout << "************************\n";
    cout << "*** Command Renderer ***\n";
    cout << "************************\n\n";

    LedMatrix led_matrix;
    led_matrix.print();

    return 0;
}
