#include <stdio.h>
#include <math.h>

float funkcja(float a,float b,float c,float x){
	return a*x*x + b*x + c;
}
int main(){
	float A,B,C,x1,x2,e;
	float a,b,x;
	int i=0,maxi=64;
	
	printf("Podaj liczbe a,b,c,x1,x2 i dokladnosc\n");
	scanf("%f%f%f%f%f%f",&A,&B,&C,&x1,&x2,&e);
	a=x1; 
	b=x2;
	do{
		x=(a+b)/2;
		if(funkcja(A,B,C,x)==0) break;
		else if((funkcja(A,B,C,x)*funkcja(A,B,C,a))<0) b=x;
		else a=x;
		i++;
		if(i>maxi) break;
		
	}while(fabs(funkcja(A,B,C,x))>e);
	if(i<maxi){
		printf("W funkcji y=%.0fx^2 %.0fx %.0f w zakresie od %.0f do %.0f i dokladnosci %.2f.\n",A,B,C,x1,x2,e);
		printf("Pierwiastek kwadratowy to %.2f",x);
	}else{
		printf("Nie znaleziono rozwiazania.");
	}
	return 0;
}
