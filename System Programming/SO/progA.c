#include <stdio.h>
#include "progB.h"
#include "libN.h"

int main(){
    printf("progA: inside main\n");
    progBfunc();
    lib1func();
    lib2func();
    lib3func();


}