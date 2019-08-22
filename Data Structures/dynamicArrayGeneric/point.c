#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"point.h"


point_t* createPoint(int x, int y){
    point_t* p;
    p = (point_t*)malloc(sizeof(point_t));
    p->x = x;
    p->y = y;
    return p;
}


void destroyPoint(void* el, void* fpr){
    
    point_t* element;
    FILE* fp;

    element = el;
    fp = fpr;

    if (fp == NULL){
        printf("FILE POINTER ERROR");
        return;
    }
    fprintf(fp, "x: %d, y: %d\n", element->x, element->y);
    free (element);
}

void printPoint(point_t* elem){
    printf("(%d,%d)  ", elem->x, elem->y);
}


static double pointVector(point_t* p){
    return sqrt(p->x * p->x + p->y * p->y);
}

int pointCmp(void* v1, void* v2){
    point_t *p1, *p2;
    p1 = v1;
    p2 = v2;
    return pointVector(p2) - pointVector(p1);
}