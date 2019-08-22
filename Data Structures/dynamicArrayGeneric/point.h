#ifndef POINT_H
#define POINT_H

struct point{
    int x;
    int y;
};
typedef struct point point_t;


point_t* createPoint(int x, int y);

void destroyPoint(void* el, void* fpr);

void printPoint(point_t* elem);

int pointCmp(void* p1, void* p2);

#endif