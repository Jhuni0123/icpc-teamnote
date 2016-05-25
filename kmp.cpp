#include <stdio.h>
#include <string.h>

void kmp(char *t, char *p, int *r, int *ff){
    for(int i=0,j=0;i<strlen(t);i++;j++){
        if(t[i]!=p[j]){
            if(j==0){
                r[i]=0;
                j=-1;
            }
            else{
                i--;
                j=ff[j-1]-1;
            }
        }
        else r[i]=j+1;
    }
}

