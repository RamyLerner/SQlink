#include "tContainer_t.h"
#include <vector>
#include <list>
#include <iostream>

int main(){
    tContainer_t<int, std::vector<int*> > vecC;
    int i;
    int arr[5];
    for (i=0; i<5; i++){
        arr[i] = 2*i + 1;
        vecC.push_back(arr + i);
    }
    
    std::cout << vecC[3] << std::endl;
}

