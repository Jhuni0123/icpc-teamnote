#include <stdio.h>

typedef struct point{
    int x,y;
}point;

int ccw(const point &a, const point &b, const point &c){
    return a.x*b.y+b.x*c.y+c.x*a.y - a.y*b.x-b.y*c.x-c.y*a.x;
}
