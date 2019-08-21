#include <stdio.h>
#include "darray_int.h"

void errorCheck(AdtStatus result){
    switch (result){
        case OK: printf("OK\n");
                break;
        case AllocationError: printf("ALLOCATION ERROR\n");
                break;
        case IndexError: printf("INDEX ERROR\n");
                break;
        case NullPointerError: printf("NULL POINTER ERROR\n");
                break;
    }
}

int main(){
    size_t initCap;
    int input = 0, elem, ind;
    AdtStatus err;
    darray* dArr = NULL;

    printf("enter initial capacity\n");
    scanf("%lu", &initCap);
    if(darrayCreate(&dArr, initCap)==AllocationError)
        printf("create: ALLOCATION ERROR");
    while (input != -1){
        printf("type 1 to print\ntype 2 to add\ntype 3 to delete\ntype 4 to retrieve element\ntype 5 to set\ntype 6 to view size\ntype -1 to exit\n");
        scanf("%d", &input);
        switch (input){
            case 1: errorCheck(darrayPrint(dArr) == 1);
                    break;
            case 2: printf("enter element to insert\n");
                    scanf("%d", &elem);
                    errorCheck(darrayAdd(dArr, elem));
                    break;
            case 3: err = darrayDelete(dArr, &elem);
                    if (err == OK)
                        printf("deleted: %d\n", elem);
                    errorCheck(err);
                    break;
            case 4: printf("enter element index\n");
                    scanf("%d", &ind);
                    err = darrayGet(dArr, ind, &elem);
                    if (err == OK)
                        printf("element: %d\n", elem);
                    errorCheck(err);    
                    break;
            case 5: printf("enter element index and the element\n");
                    scanf("%d%d", &ind, &elem);
                    errorCheck(darraySet(dArr, ind, elem));
                    break;
            case 6: err = darrayItemsNum(dArr, &ind);
                    if (err == OK)
                        printf("number of items: %d\n", ind);
                    errorCheck(err);
                    break;
            case -1: break;
            default: printf("wrong input\n");

        }
    }
    darrayDestroy(dArr);
    return 0;
}