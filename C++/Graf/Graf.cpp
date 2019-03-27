#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <conio.h>
#define N 25
/*
	a) czy graf jest pe³ny, spójny, dualny, itp.
	b) czy graf jest dwudzielny lub trójdzielny
	c) czy graf zawiera drzewa, jeœli tak to program ma je wymieniæ
	d) koñcowym efektem dzia³ania programu ma byæ wygenerowanie albo grafu dualnego albo grafu pe³nego, itp. decyzja nale¿y do twórcy
*/
using namespace std;

int main(){
	int tab[N][N],a,tab2[N];
	int W,czyPelny=1,los,los2;
	srand(time(NULL));
	do{
		printf("Podaj liczbe wierzcholkow.(Min: 2 Max: %d): ",N);
		scanf("%d",&W);
	}while(W>N||W<2);
	printf("Podaj szanse na wylosowanie 1(0-100):");
	scanf("%d",&los2);
	
	//printf("%d\n",W);
	for(int i=0;i<W;i++){
		tab2[i]=0;	// 0 - inicjalizacja 1 - do sprawdzenia 2 - sprawdzone
		for(int j=0;j<=i;j++){
			los = rand()%100;
			if(los<los2) a=1; else a=0;
			//a = rand()%2;
			if(i!=j) {
				tab[i][j]=a;
				tab[j][i]=a;
			} else tab[i][j]=0;
		}
	} // Tworzy macierz sasiedztwa
	
	printf("Wygenerowany graf:\n");
	for(int i=0;i<W;i++){
		printf("Wierzcholek %2d: ",i+1);
		for(int j=0;j<W;j++){
			printf("%d ",tab[i][j]); //Wyswietla macierz sasiedztwa
			if(i!=j && tab[i][j]==0) czyPelny=0; //Jezeli brakuje polaczenia z jednym z wierzcholkow graf jest nie pelny
		}	
		printf("\n");
	}
	printf("Graf jest ");
	if(czyPelny) printf("Pelny,"); else printf("Niepelny,");
	int c=1;
	int i=-1,l,m,k,o=1;
	do{
		c++;
		do{
			i++;
			if(tab2[i]==0) tab2[i]=1; // do sprawdzenia
		}while(tab2[i]>1&&i<W);
		do{
			for(int j=0;j<W;j++){
				if(tab2[j]==1){ // do sprawdzenia
					tab2[j]=c; // sprawdzone
					for(int i=0;i<W;i++){
						if(i!=j && tab[j][i]==1){
							if(tab2[i]==0) tab2[i]=1; //inicjalizacja, do sprawdzenia
						}
					}
				}
			}
			l=0,m=0;
			for(int j=0;j<W;j++){
				if(tab2[j]==1) l++; //zlicza wszystkie do sprawdzenia
				if(tab2[j]>1) m++; //zlicza wszystkie drzewa
			}
		}while(l>0);
	}while(m<W);
	if(c==2) printf("Spojny"); else printf("Niespojny");
	printf("\n");
	getch();
	if(c>2) {
		for(int g=2;g<=c;g++){
			k=0;
			for(int i=0;i<W;i++){
				if(tab2[i]==g) k+=1;
			}
			if(k>1){
				printf("Drzewo %d:\n",o);
				for(int i=0;i<W;i++){
					if(tab2[i]==g){ //sprawdzone
						printf("Wierzcholek %2d: ",i+1);
						for(int j=0;j<W;j++){
							printf("%d ",tab[i][j]);
						}
						printf("\n");
					}
				}
				o++;
			}
		}
		printf("Graf jest %d - dzielny\n",o-1);
		getch();
	}
	printf("\nGraf pelny:\n");
	for(int i=0;i<W;i++){
		for(int j=0;j<=i;j++){
			a = 1;
			if(i!=j) {
				tab[i][j]=a;
				tab[j][i]=a;
			} else tab[i][j]=0;
		}
	}
	for(int i=0;i<W;i++){
		printf("Wierzcholek %2d: ",i+1);
		for(int j=0;j<W;j++) printf("%d ",tab[i][j]);
		printf("\n");
	}
	getch();
	return 0;
}
