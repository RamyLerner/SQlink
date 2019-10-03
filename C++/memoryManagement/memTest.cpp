#include <iostream>
#include "memManager_t.h"
#include "memPool_t.h"
#include "memPage_t.h"

void test(MemManager_t* mm){
    char buffer[30] = "Good Morning Everybody";
    mm->write(buffer, 4);
    mm->read(buffer,4);
    buffer[5] = '\0';
    std::cout << buffer << std::endl;

}

int main(){
    int input;
    MemPage_t* mpg;
    MemPool_t* mpl;
    std::cout << "Type 1 to test MemPage\nType 2 to test MemPool\nType any other integer to exit\n";
    std::cin >> input;
    switch (input){
        case 1:
            mpg = new MemPage_t;
            test(mpg);
            delete mpg;
            break;
        case 2:
            mpl = new MemPool_t;
            test(mpl);
            delete mpl;
            break;
    }
}