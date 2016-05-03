#include <stdio.h>

int ccw(int x1,int x2,int x3,int y1,int y2,int y3){
    int t = x1*y2+x2*y3+x3*y1;
    t = t - y1*x2-y2*x3-y3*x1;
    return t;
}

int main(){
    int x1=0,y1=0;
    int x2=10,y2=10;
    int x3=4,y3=2;
    int x4=3,y4=15;
    int x5=20,y5=20;
    printf("%d\n",ccw(x1,x2,x3,y1,y2,y3));
    printf("%d\n",ccw(x1,x2,x4,y1,y2,y4));
    printf("%d\n",ccw(x1,x2,x5,y1,y2,y5));
}

