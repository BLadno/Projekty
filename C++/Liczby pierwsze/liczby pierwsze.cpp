#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <math.h>
using namespace std;
class primes{
	private:
	vector <long long> Primes;
	public:
	void init(){
		Primes.push_back(1);
		Primes.push_back(2);
		Primes.push_back(3);
	}
	bool isPrime(long long a,int b){
		int j=2,d=0;
		while(j<=b){
			if(a%Primes[j]==0) return false; // nie jest pierwsza
			j++;
		}
		return true;
	}
	int makePrimeList(int a){
		long size=Primes.size()-1;
		long c=size,e=size,i=Primes[size]+2;
		clock_t start = clock();
		while(e<a){
			for (long j=1;i>=Primes[j]*Primes[j];j++){
				c=j;
			}
			if(isPrime(i,c)){ //jezeli jest pierwsza
				e++;
				if(e>=Primes.size()) Primes.push_back(i);
			}
			i+=2;
		}
		clock_t czas = (clock()-start)/CLOCKS_PER_SEC;
		printf("\nTablica zostala stworzona w czasie %lu,%lus\n",czas,(clock()-start)%1000);
		return e;
	}
	int makePrimeList2(int a){
		long size=Primes.size()-1;
		long e=size,i=Primes[size];
		int k=0;
		clock_t start = clock();
		while(e<a){
			k=0;
			i+=2;
			for(int l=2;i>=Primes[l]*Primes[l] && k==0;l++){
				if(i%Primes[l]==0) k=1;
			}
			if(k==0&&e<Primes.size()) {
				e++;
				Primes.push_back(i);
			}
		}
		clock_t czas = (clock()-start)/CLOCKS_PER_SEC;
		printf("\nTablica zostala stworzona w czasie %lu,%lus\n",czas,(clock()-start)%1000);
		return e;
	}
	int showLargestPrime(){
		int c=1;
		long long a=Primes.size()-1;
		long long i=(a*a)-1;
		while(true){
			if(isPrime(i,a)){
				printf("Najwieksza liczba pierwsza to %lld\n",i);
				return 0;
			}
			i-=2;
		}
	}
	long long getLargestPrime(int z){
		int c=1;
		long long a=Primes.size()-1;
		long long i=(a*a)-1;
		while(true){
			if(isPrime(i,a)){
				if(z<=0) return i;
				z--;
			}
			i-=2;
		}
	}
	int showPrimes(){
		if(Primes.size()>10000) return 1;
		for(int i=0;i<Primes.size();i++){
			printf("%d ",Primes[i]);
		}
		printf("\n");
		return 0;
	}
	int getSize(){
		cout << Primes.size()-1 <<endl;
		return 0;
	}
	void showPrimeByNumber(int n){
		if(n<Primes.size())printf("%lld \n",Primes[n]);
	}
	long long getPrimeByNumber(int n){
		if(n>Primes.size()) return 0;
		return Primes[n];
	}
	void save(string inp){
		clock_t start = clock();
		ofstream plik;
	    plik.open(inp.c_str(), fstream::out);
	    if (!plik.good() ) cout << " Plik nie istnieje lub brak dostepu " <<endl;
	    else{
			for(int i=0;i<Primes.size();i++){
				plik << Primes[i];
				if(i<Primes.size()-1) plik <<endl;
			}
	        plik.close();
	        cout << "Plik zostal zapisany" << endl;
	    }
	    clock_t czas = (clock()-start)/CLOCKS_PER_SEC;
		printf("\nCzas %lu,%lus\n",czas,(clock()-start)%1000);
	}
	void load(string inp){
		long long a;
		int i=0;
		clock_t start = clock();
		ifstream plik;
    	plik.open(inp.c_str(), fstream::in);
    	while(!plik.eof()){
			plik >> a;
			if(i>=Primes.size()) Primes.push_back(a);
			i++;
    	}
    	plik.close();
    	clock_t czas = (clock()-start)/CLOCKS_PER_SEC;
    	printf("\nCzas %lu,%lus\n",czas,(clock()-start)%1000);
	}
};
class menu{
	primes Prime;
	string pomoc;
	public:
	void init(){
		pomoc = "Polecenia: make, make2, get, findMax, show, size, save, load, exit";
		Prime.init();
	}
	int conditions(string arr[]){
		if (arr[0] == "help") cout << pomoc <<endl; //buy(arr[1],atoi(arr[2].c_str()));
    	else if(arr[0]== "make" && arr[1]!="") Prime.makePrimeList(atoll(arr[1].c_str()));
    	else if(arr[0]== "make2" && arr[1]!="") Prime.makePrimeList2(atoll(arr[1].c_str()));
    	else if(arr[0]== "get" && arr[1]!="") Prime.showPrimeByNumber(atoll(arr[1].c_str()));
    	else if(arr[0]== "save" && arr[1]!="") Prime.save(arr[1]);
    	else if(arr[0]== "load" && arr[1]!="") Prime.load(arr[1]);
    	else if(arr[0]== "findMax") Prime.showLargestPrime();
    	else if(arr[0]== "size") Prime.getSize();
    	else if(arr[0]== "show") Prime.showPrimes();
    	else if (arr[0]=="exit" || arr[0]=="EXIT") return 1;
		return 0;
	}
	void run(){
		string polecenie;
		int args=8,x=0;
    	do{
			getline(cin,polecenie);
			string arr[args];
			int i = 0;
			stringstream ssin(polecenie);
			while (ssin.good() && i < args){
				ssin >> arr[i];
				++i;
    		}
    		x = conditions(arr);
		}while(x==0);
	}
};
int main(){
	menu Menu;
	Menu.init();
	Menu.run();
	cout << "Program zostal zakonczony"<<endl;
	getch();
    return 0;
}

