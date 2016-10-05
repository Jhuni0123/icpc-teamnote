#include <stdio.h>
#include <string.h>

void kmp(char *t, char *p, int *r, int *ff){
    int l = strlen(t)
    for(int i=0,j=0;i<l;i++){
        if(t[i]!=p[j]){
            if(j==0)r[i]=0;
            else{
                i--;
                j=ff[j-1];
            }
        }
        else r[i]=++j;
    }
}

int main(){
    int n;
    char a[1000], b[1000]; // a: 찾을 문자열, b: 대상문자열.
    int ff[1000], d[1000]; // ff: 실패함수 배열, d: 결과 배열.
    //입력
    kmp(a+1,a,ff+1,ff); // 실패함수 생성
    kmp(b,a,d,ff); 
    
}
