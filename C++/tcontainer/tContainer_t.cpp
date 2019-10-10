#include "tContainer_t.h"
#include <vector>
#include <list>
#include <iostream>

int main(){
    tContainer_t<int, std::vector> vecC;
   

    vecC.push_back(5);
    vecC.push_back(9);
    vecC.push_back(3);
    vecC.push_back(4);
    vecC.push_back(20);
    std::cout << vecC[3] << std::endl;
}

