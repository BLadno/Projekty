#include <iostream>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

struct pole {int x, y;};

const int n=30;

char A[n][n];
int B[n][n];
pole p, k;
queue <pole> z;

void tablica(char A[n][n]){
    cout<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cout<<A[i][j];
        cout<<endl;
      }
}


int main(){
    ifstream we("droga.txt"),we2("droga2.txt"),we3("droga3.txt");

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            we3>>A[i][j]; //wczytanie z pliku do zmiennej char A[n][n]
            if(A[i][j]=='1') {p.x=i; p.y=j;} //Punkt pocz¹tkowy
            if(A[i][j]=='6') {k.x=i; k.y=j;} //Punkt koñcowy
    }

    tablica(A); //Wypisanie tablicy
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) {
		if(A[i][j]=='.')B[i][j]=2;
		else if(A[i][j]=='6')B[i][j]=3;
		else B[i][j]=1; //X
    } // zmienna B 1='X' 2='.' 3='6' 4='element drogi' 5='element sprawdzony'

    pole P[n][n]; //Utworzenie kolejki P[n][n]

    z.push(p); //wrzucenie do kolejki z punktu pocz¹tkowego
    pole w, v; //deklaracja kolejki w i v,
    clock_t start = clock();
    while(!z.empty()){ //Dopoki kolejka z nie jest pusta

        w=z.front(); //w staje siê punktem poprzednim
        z.pop(); //punkt powszedni zostaje zdjêty z kolejki
        B[w.x][w.y]=4; //Punkt w zostaje oznaczony jako true
        if(z.size()>1000) {
			cout << "sie wykrzaczylem"<<endl;
			for (int i=0,size=z.size();i<size;i++){
				w=z.front();
				cout << w.x<<":" <<w.y<<", ";
				if(i%10==0) cout <<endl;
				z.pop();
			}
			cout << z.size()<<endl;
			break;
        }
        if(w.x==k.x && w.y==k.y) break; //Jezeli punkt w jest rowny punktowi koncowemu, petla jest przerywana
        if(w.x<n-1) { v.x=w.x+1; v.y=w.y; if (B[v.x][v.y]==2 || B[v.x][v.y]==3){ B[v.x][v.y] = 5; z.push(v); P[v.x][v.y]=w; } } 
        if(w.x>0)   { v.x=w.x-1; v.y=w.y; if (B[v.x][v.y]==2 || B[v.x][v.y]==3){ B[v.x][v.y] = 5; z.push(v); P[v.x][v.y]=w; } }
        if(w.y<n-1) { v.x=w.x; v.y=w.y+1; if (B[v.x][v.y]==2 || B[v.x][v.y]==3){ B[v.x][v.y] = 5; z.push(v); P[v.x][v.y]=w; } }
        if(w.y>0)   { v.x=w.x; v.y=w.y-1; if (B[v.x][v.y]==2 || B[v.x][v.y]==3){ B[v.x][v.y] = 5; z.push(v); P[v.x][v.y]=w; } }
        /*Sprawdzane sa punkty z przodu i tylu, oraz na gorze i dole od punktu sprawdzanego,
		wziêta jest pod uwagê mo¿liwoœæ ¿e punkt mo¿e przekraczaæ granice grafu
		Jesli znak w punkcie v jest równy '.' lub '6' i punkt nie jest oznaczony jako false, punkt v jest wrzucony do kolejki z i punkt P kolejki staje siê w
		Kolejka z zawiera sprawdzane punkty
		Kolejka P w wspolrzednych przyszlego punktu zawiera wspolrzedne aktualnego punktu
		B zawiera sprawdzone punkty
		v - przyszly punkt, w punkt aktualny*/
	}
    clock_t czas = (clock()-start)/CLOCKS_PER_SEC;
	printf("Czas %lu,%lus\n",czas,(clock()-start)%1000);
	cout<<"\n\n\nWszyskie mozliwe miejsca do przebycia w labiryncie. \n\n";

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) {if(B[i][j]==4) cout<<(char)219; else cout<<'X';} //Wypisuje wszystkie punkty, gdzie B jest równe true
        cout<<endl;
    }

    if(w.x==k.x&&w.y==k.y){ //Gdy ostatni punkt sprawdzany w ostatniej petli jest rowny punktowi koncowemu
        cout<<"\nJest przejscie\n";
        cout<<"\nNajkrotsza droga do przebycia.\n\n";
        int i=k.x, j=k.y, a, b, droga=0; //zmienne i,j staj¹ siê wspó³rzêdnymi punktu docelowego, droga jest rowna 0
        while(i!=p.x || j!=p.y){
            //cout<<i<<" "<<j<<endl;
            A[i][j]=(char)219; //Nadpisanie punktu tablicy prostokatem lub znak w punkcie w tablicy o wspó³rzêdnych i,j staje siê znakiem (char)219
            a=i; //zmienna a przyjmuje i
            b=j; //zmienna b przjmuje j
            i=P[a][b].x; //i staje sie wspolrzedna x kolejki P wspolrzednych a i b
            j=P[a][b].y; //j staje sie wspolrzedna y kolejki P wspolrzednych a i b
            droga++; //droga zwiekszona o 1
            /*Przechodzi przez elementy kolejki P, znaczy siê idzie od koñca do pocz¹tku, kolejka P zawiera wspolrzedne poprzedniego punktu
			*/
		}
        //cout<<i<<" "<<j<<endl;
        cout<<"droga = "<<droga<<endl;
        tablica(A); //Wypisanie tablicy
	}else cout<<"\nNie ma przejscia";


    cout<<"\n"<<endl;

    system ("pause");
    return 0;

}
