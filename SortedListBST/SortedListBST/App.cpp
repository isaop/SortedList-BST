#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
    std::cout << "Short tests pass!" << std::endl;
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}