#include <iostream>

// https://edabit.com/challenge/s695FkhRd3J65tmdQ
// A Tour of C++  9.2.1 String implementation 
//std::string& doubleSwap(std::string& s, char c1, char c2){
//    /*Write a function to replace all instances of character c1 with character c2 and vice versa.*/
//    for(int i =0; i<s.size(); ++i){
//        std::cout << s[i];
//    }
//    return NULL
//
//}

void doubleSwap(std::string& s, const char c1, const char c2){
    /*Write a function to replace all instances of character c1 with character c2 and vice versa.*/
    for(int i =0; i<s.size(); ++i){
//        std::cout << s.substr(i) + '\n';
        if (s.at(i)==c1)
            s[i] = c2; 
            //printf("%c", c1);
    }
}

int main() {
    std::cout << "Hola mundito!\n";
    std::string  s1 {"que pasa tio"};
    doubleSwap(s1, 'a', 'e');
    std::cout << s1;
    return 0;
}
