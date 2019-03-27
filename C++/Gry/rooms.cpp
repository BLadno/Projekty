#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
using namespace std;
class question{
	public:
	string zapytaj(string pytanie){
		string odpowiedz;
		cout << pytanie <<endl;
		cin >> odpowiedz;
		return odpowiedz;
	}
	int zapytaj2(string pytanie,string odpowiedz){
		string odpowiedz2;
		cout << pytanie <<endl;
		cin >> odpowiedz2;
		if(odpowiedz==odpowiedz2) return 1; 
		else return 0;
	}
	int zapytajCzy(string pytanie){
		string odp;
		cout << pytanie <<endl;
		cin >> odp;
		if(odp=="tak"||odp=="Tak") return 1; 
		else if(odp=="nie"||odp=="Nie") return 0;
		else return -1;
	}
	void pytOdp(string pytanie,string odpowiedz1,string odpowiedz2){
		int a;
		do{
			a = zapytajCzy(pytanie);
		}while(a==-1);
		if(a==1) cout << odpowiedz1 <<endl;
		else if(a==0) cout << odpowiedz2 <<endl;	
	}
	void pytOdp2(string pytanie,string odpowiedz,string odpowiedz1,string odpowiedz2){
		int a;
		a = zapytaj2(pytanie,odpowiedz);
		if(a==1) cout << odpowiedz1 <<endl;
		else if(a==0) cout << odpowiedz2 <<endl;	
	}
};

class item{
	public:
	string nazwa,opis,typ;
	item(string nazwa, string opis, string typ){
		this->nazwa=nazwa;
		this->opis=opis;
		this->typ=typ;
	}
	void wyswietl(){
		cout << nazwa;
	}
	void wyswietlOpis(){
		cout << opis;
	}
};

class container{
	private:
	vector <item> items;
	public:
	string nazwa,opis;
	void start(){
		cout << opis << endl;
	}
	void addItem(string nazwa,string opis,string typ){
		item * przedmiot = new item(nazwa,opis,typ);
		items.push_back(*przedmiot);
	}
	void display(){
		cout << "W "<< nazwa <<" znajduja sie" << endl;
		if(items.size()<=0) cout <<nazwa <<" jest pusty"<<endl; else
    	for( int i = 0; i < items.size(); i++ ){
			items[i].wyswietl();
			cout << ", ";
    	}
    	cout <<endl;
	}
	void check(string nazwa){
    	for( int i = 0; i < items.size(); i++ ){
			if(items[i].nazwa==nazwa) items[i].wyswietlOpis();
    	}
    	cout <<endl;
	}
	int exist(string nazwa){
		for( int i = 0; i < items.size(); i++ ){
			if(items[i].nazwa==nazwa){
				return 1;
			}
    	}
    	return 0;
	}
	item getItem(string nazwa){
		for( int i = 0; i < items.size(); i++ ){
			if(items[i].nazwa==nazwa){
				if(items[i].typ == "door"||items[i].typ == "decoration") {
					cout <<"Nie mozesz tego podniesc" <<endl;
					continue;
				}
				return items[i];
			}
    	}
	}
	void destroyItem(string nazwa){
		for( int i = 0; i < items.size(); i++ ){
			if(items[i].nazwa==nazwa){
				items.erase(items.begin()+i);
			}
    	}
	}
};

class room{
	public:
	vector <item> items;
	container backpack,room;
	question pytania;
	string opis;
	void start(){
		cout << opis << endl;
	}
	void take(string nazwa){
		if(room.exist(nazwa)){
			item przedmiot=room.getItem(nazwa);
			room.destroyItem(nazwa);
			backpack.addItem(przedmiot.nazwa,przedmiot.opis,przedmiot.typ);
		}
	}
	void drop(string nazwa){
		if(backpack.exist(nazwa)){
			item przedmiot=backpack.getItem(nazwa);
			backpack.destroyItem(nazwa);
			room.addItem(przedmiot.nazwa,przedmiot.opis,przedmiot.typ);
		}
	}
	void init(){
		opis="Znajdujesz sie w pustym pokoju";
		start();
	}
	int conditions(string arr[]){
		if (arr[0] == "help") cout << "Witaj w grze" <<endl;
		else if (arr[0]!="exit" && arr[0]!="EXIT")cout << "Nie rozpoznaje polecenia" <<endl;
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

class room1: public room{
	public:
	void init(){
		opis="Budzisz sie i rozgladasz wokol siebie";
		room.addItem("klucz","czerwony klucz","key");
		room.addItem("noz","zwykly kuchenny noz","weapon");
		room.addItem("pistolet","colt 1911","weapon");
		room.addItem("drzwi","zwykle drzwi","door");
		room.addItem("okno","zwykle okno","decoration");
		room.addItem("krzeslo","zwykle krzeslo","decoration");
		room.addItem("stol","zwykly stol","decoration");
		backpack.nazwa="plecaku";
		backpack.opis="zwykly skorzany plecak";
		room.nazwa = "pokoju";
		room.opis = "Znajdujesz sie w ciemnym pokoju";
		//pytania.pytOdp("Czy jestes gotow","Fajnie","Aha");
		//pytania.pytOdp2("2+2=?","4","dobrze","zle");
		start();
		room.start();
	}
	int conditions(string arr[]){
		if (arr[0] == "help") cout << "Witaj w grze" <<endl;
		else if(arr[0]== "start") start();
    	else if(arr[0]== "look" && arr[1]=="around") room.display();
    	else if(arr[0]== "check" && arr[1]=="room" && arr[2]!="") room.check(arr[2]);
    	else if(arr[0]== "check" && arr[1]=="backpack" && arr[2]!="") backpack.check(arr[2]);
    	else if(arr[0]== "take" && arr[1]!="") take(arr[1]);
    	else if(arr[0]== "drop" && arr[1]!="") drop(arr[1]);
    	else if(arr[0]== "look" && arr[1]=="backpack") backpack.display();
    	else if(arr[0]== "check" && arr[1]=="backpack"&&arr[2]!="") backpack.check(arr[2]);
    	else if (arr[0]=="open" && arr[1]=="drzwi") return 1;
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
	room1 pokoj;
	pokoj.init();
	pokoj.run();
	cout << "Gra zostala zakonczona"<<endl;
	getch();
    return 0;
}

