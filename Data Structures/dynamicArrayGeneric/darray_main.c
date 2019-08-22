#include <stdio.h>
#include "darray_generic.h"
#include "point.h"

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

void runPrint(darray* dArr){
    int i, size;
    point_t* p;
    void* v;
    darrayItemsNum(dArr, &size);
    for (i=0; i<size; i++){
        darrayGet(dArr, i, &v);
        p = v;
        printPoint(p);
    }
    putchar('\n');
}

void runInsert(darray* dArr){
    point_t* elem;
    int x, y;
    printf("enter points coordinates\n");
    scanf("%d%d", &x, &y);
    elem = createPoint(x,y);
    errorCheck(darrayAdd(dArr, elem));
}

void runDelete(darray* dArr, FILE* fp){
    point_t* elem;
    void* result;
    AdtStatus err;
    err = darrayDelete(dArr, &result);
    if (err == OK){
        elem = (point_t*)result;
        printf("deleted: ");
        printPoint(elem);
        destroyPoint(elem, fp);
    } 
    errorCheck(err);
}

void runGetElement(darray* dArr){
    int ind;
    point_t* elem;
    AdtStatus err;
    void* result;
    printf("enter element index\n");
    scanf("%d", &ind);
    err = darrayGet(dArr, ind, &result);
    if (err == OK){
        elem = (point_t*)result;
        printPoint(elem);
    }
    errorCheck(err); 
}

void runSet(darray* dArr,  FILE* fp){
    int ind, x, y;
    point_t *newElem, *oldElem;
    void* result;
    AdtStatus err;
    printf("enter element index\n");
    scanf("%d", &ind);
    err = darrayGet(dArr, ind, &result);
    if (err == OK){
        oldElem = (point_t*)result;
        destroyPoint(oldElem, fp);
        printf("enter coordinates to set:\n");
        scanf("%d%d", &x, &y);
        newElem = createPoint(x, y);
        errorCheck(darraySet(dArr, ind, newElem));
    }
}

void runGetSize(darray* dArr){
    AdtStatus err;
    int ind;
    err = darrayItemsNum(dArr, &ind);
    if (err == OK)
        printf("number of items: %d\n", ind);
    errorCheck(err);
}

void runSort(darray* dArr){
    errorCheck(darraySort(dArr, pointCmp));
}

int main(){
    size_t initCap;
    int input = 0;
    darray* dArr;
    elementDestroy func;
    FILE* fp;

    fp = fopen("points.txt","a");
    printf("enter initial capacity\n");
    scanf("%lu", &initCap);
    if(darrayCreate(&dArr, initCap)==AllocationError){
        printf("create: ALLOCATION ERROR");
        return -1;
    }
    while (input != -1){
        printf("type 1 to print\ntype 2 to add\ntype 3 to delete\ntype 4 to retrieve element\ntype 5 to set\ntype 6 to view size\ntype 7 to sort\ntype -1 to exit\n");
        scanf("%d", &input);
        switch (input){
            case 1: runPrint(dArr);
                    break;
            case 2: runInsert(dArr);    
                    break;
            case 3: runDelete(dArr, fp);
                    break;
            case 4: runGetElement(dArr);   
                    break;
            case 5: runSet(dArr, fp);
                    break;
            case 6: runGetSize(dArr);
                    break;
            case 7: runSort(dArr);
                    break;
            case -1: break;
            default: printf("wrong input\n");

        }
    }

    func = destroyPoint;
    darrayDestroy(dArr, func, fp);
    fclose(fp);
    return 0;
}