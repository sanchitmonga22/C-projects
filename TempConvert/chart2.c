#include <stdio.h>
int main(){
        printf("Fahrenheit-Celsius\n");
        int fa=0;
        float c=0;
        while(fa<=300){
                c=(float)(fa-32)*5/9;
                printf("     %d      %.1f\n",fa,c);
                fa++;
        }
}

