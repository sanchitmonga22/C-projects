#include <stdio.h>
int main(){
	printf("Fahrenheit-Celsius\n");
	int f=0;
	int c=0;
	while(f<=300){
		c=(f-32)*5/9;
		printf("     %d      %d\n",f,c);
		f++;
	}
}
