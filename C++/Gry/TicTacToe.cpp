#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
using namespace std;
void init(int *tab){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			*((tab+i*3)+j)=0;
		}
	}
}
void wyswietl(int *tab){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
			if(*((tab+i*3)+j)==1) cout <<"x ";
			else if(*((tab+i*3)+j)==2) cout <<"o ";
			else cout <<"- ";
            //printf("%d ",*((tab+i*3)+j));
        }
        cout <<endl;
    }
    cout <<endl;
}
void losuj(int *tab,int x){
	int a,b;
    int y=0;
	do{
		int a=(rand() % 3 );
		int b=(rand() % 3 );
		if(*((tab+a*3)+b)==1||*((tab+a*3)+b)==2) {
			y=0;
		}
		else{
			*((tab+a*3)+b)=x;
			y=1;
		}
	}while(y==0);
}
void dodaj(int *tab,string tekst,int x){
    int y=0,a,b;
    cout << tekst<<endl;
	do{
		cin >> a >> b;
		if(*((tab+a*3)+b)==1||*((tab+a*3)+b)==2) {
			cout <<"Pole zajete"<<endl;
			y=0;
		}
		else{
			*((tab+a*3)+b)=x;
			y=1;
		}
	}while(y==0);
}
int warunek(int *tab){
	int x=0,z=0,i,j;
	for(int i=1;i<3;i++){
		if(*((tab+0*3)+0)==i&&*((tab+1*3)+1)==i&&*((tab+2*3)+2)==i) x=i;
		if(*((tab+0*3)+2)==i&&*((tab+1*3)+1)==i&&*((tab+2*3)+0)==i) x=i; //po skosie
	
		if(*((tab+0*3)+0)==i&&*((tab+0*3)+1)==i&&*((tab+0*3)+2)==i) x=i;
		if(*((tab+1*3)+0)==i&&*((tab+1*3)+1)==i&&*((tab+1*3)+2)==i) x=i;
		if(*((tab+2*3)+0)==i&&*((tab+2*3)+1)==i&&*((tab+2*3)+2)==i) x=i; //poziomo
	
		if(*((tab+0*3)+0)==i&&*((tab+1*3)+0)==i&&*((tab+2*3)+0)==i) x=i;
		if(*((tab+0*3)+1)==i&&*((tab+1*3)+1)==i&&*((tab+2*3)+1)==i) x=i;
		if(*((tab+0*3)+2)==i&&*((tab+1*3)+2)==i&&*((tab+2*3)+2)==i) x=i; //pionowo
		for(i=0;i<3;i++){
        	for(j=0;j<3;j++){
				if(*((tab+i*3)+j)==0) z++;
        	}
    	}
    	if(z==0&&x==0) x=3;
	}
	return x;
}
int main(){
	srand( time( NULL ) );
	int tab[3][3];
	int *tab2;
	tab2=&tab[0][0];
	int x=0,a;
	do{
		cout << "0 - exit 1 - PvP 2 - PvC 3 - CvC"<<endl;
		cin >> a;
		init(tab2);
		if(a==1){
			do{
				dodaj(tab2,"Teraz graja 'x' Podaj pole",1);
				wyswietl(tab2);
				x = warunek(tab2);
				if(x!=0) break;
				dodaj(tab2,"Teraz graja 'o' Podaj pole",2);
				wyswietl(tab2);
				x = warunek(tab2);
			}while(x==0);
		}else if(a==2){
			do{
				dodaj(tab2,"Teraz graja 'x' Podaj pole",1);
				wyswietl(tab2);
				x = warunek(tab2);
				if(x!=0) break;
				losuj(tab2,2);
				wyswietl(tab2);
				x = warunek(tab2);
			}while(x==0);		
		}else if(a==3){
			do{
				losuj(tab2,1);
				wyswietl(tab2);
				x = warunek(tab2);
				if(x!=0) break;
				losuj(tab2,2);
				wyswietl(tab2);
				x = warunek(tab2);
				getch();
			}while(x==0);
		}
		if(x==1) cout << "Wygraly 'x'" <<endl;
		else if(x==2) cout << "Wygraly 'o'" <<endl;
		else cout << "Nikt nie wygral"<<endl;
	}while(a!=0);
	cout << "Gra zostala zakonczona"<<endl;
	getch();
    return 0;
}

