#include <stdio.h>

//Counter Clock-Wise
int ccw(int x1,int x2,int x3,int y1,int y2,int y3){
    int t = x1*y2+x2*y3+x3*y1;
    t = t - y1*x2-y2*x3-y3*x1;
    return t;
}

