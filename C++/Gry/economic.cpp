#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
using namespace std;
class item{
	public:
	string nazwa,opis,typ;
	float wartosc,waga;
	int ilosc;
	item(string nazwa, string opis, string typ,float wartosc,int ilosc, float waga){
		this->nazwa=nazwa;
		this->opis=opis;
		this->typ=typ;
		this->wartosc=wartosc;
		this->ilosc=ilosc;
		this->waga=waga;
	}
	void wyswietl(){
		cout <<"produkt: " << nazwa << " cena: "<<wartosc << " ilosc: "<<ilosc <<" waga: "<<waga;
	}
	void wyswietlOpis(){
		cout << opis<<" cena: "<<wartosc<<" ilosc " <<ilosc <<" waga: "<<waga<<endl;
	}
};

class container{
	private:
	vector <item> items;
	public:
	string nazwa,opis;
	float bank,capacity,max_cap;
	void start(){
		cout << opis << endl;
	}
	void addItem(string nazwa,string opis,string typ,float wartosc,int ilosc, float waga){
		item * przedmiot = new item(nazwa,opis,typ,wartosc,ilosc,waga);
		items.push_back(*przedmiot);
	}
	void display(){
		cout << "Ilosc pieniedzy "<< bank<< " pojemnosc: "<<getCap()<<"/"<<max_cap<<endl;
		cout << "W "<< nazwa <<" znajduja sie" << endl;
		if(items.size()<=0) cout <<nazwa <<" jest pusty"<<endl; else
    	for( int i = 0; i < items.size(); i++ ){
			items[i].wyswietl();
			cout << endl;
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
				return items[i];
			}
    	}
	}
	void setAmount(string nazwa,int ilosc){
		for( int i = 0; i < items.size(); i++ ){
			if(items[i].nazwa==nazwa){
				if(items[i].typ == "door"||items[i].typ == "decoration") {
					cout <<"Nie mozesz tego podniesc" <<endl;
					continue;
				}
				items[i].ilosc+=ilosc;
			}
    	}
	}
	float getCap(){
		float cap=0,masa=0;
		for( int i = 0; i < items.size(); i++ ){
			masa=items[i].ilosc*items[i].waga;
			cap+=masa;
    	}
    	capacity=cap;
    	return cap;
	}
	void setMoney(float money){
		bank+=money;
	}
	void destroyItem(string nazwa){
		for( int i = 0; i < items.size(); i++ ){
			if(items[i].nazwa==nazwa){
				items.erase(items.begin()+i);
			}
    	}
	}
};

class shopping{
	public:
	container inventory,shop;
	string opis;
	void start(){
		cout << opis << endl;
	}
	int buy(string nazwa,int ilosc){
		if(shop.exist(nazwa)){
			item przedmiot=shop.getItem(nazwa);
			if(przedmiot.ilosc-ilosc<0) {cout << "Nieprawidlowa ilosc"<<endl; return 1;}
			float cena=ilosc*przedmiot.wartosc;
			if(inventory.bank<cena) {
				cout << "Nie stac cie"<<endl; 
				return 1;
			}else{
				inventory.setMoney(-cena);
				shop.setMoney(-cena);
			}
			if(przedmiot.ilosc-ilosc==0) shop.destroyItem(nazwa); else { przedmiot.ilosc=ilosc; shop.setAmount(nazwa,-ilosc);}
			if(inventory.exist(nazwa)) inventory.setAmount(nazwa,ilosc);
			else inventory.addItem(przedmiot.nazwa,przedmiot.opis,przedmiot.typ,przedmiot.wartosc,przedmiot.ilosc,przedmiot.waga);
			cout <<"Pomyslnie kupiles "<<ilosc<<" "<<przedmiot.nazwa<<" za "<<ilosc*przedmiot.wartosc<<endl;
		}
		return 0;
	}
	int sell(string nazwa,int ilosc){
		if(inventory.exist(nazwa)){
			item przedmiot=inventory.getItem(nazwa);
			if(przedmiot.ilosc-ilosc<0) {cout << "Nieprawidlowa ilosc"<<endl; return 1;}
			float cena=ilosc*przedmiot.wartosc;
			if(shop.bank<cena) {
				cout << "Nie stac banku"<<endl; 
				return 1;
			}else{
				shop.setMoney(-cena);
				inventory.setMoney(-cena);
			}
			if(przedmiot.ilosc-ilosc==0) inventory.destroyItem(nazwa); else { przedmiot.ilosc-=ilosc; inventory.setAmount(nazwa,-ilosc);}
			if(shop.exist(nazwa)) shop.setAmount(nazwa,ilosc);
			else shop.addItem(przedmiot.nazwa,przedmiot.opis,przedmiot.typ,przedmiot.wartosc,przedmiot.ilosc,przedmiot.waga);
			cout <<"Pomyslnie sprzedales "<<ilosc<<" "<<przedmiot.nazwa<<" za "<<ilosc*przedmiot.wartosc<<endl;
		}
		return 0;
	}
	void init(){
		opis="";
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

class shopping1: public shopping{
	public:
	void init(){
		inventory.nazwa="plecaku";
		shop.nazwa="sklepie";
		inventory.addItem("woda","woda mineralna","water",2.5,100,1);
		shop.addItem("chleb","zwykly chleb","food",2.5,100,1);
		shop.addItem("woda","woda mineralna","water",2.5,100,1);
		shop.addItem("9mm","standard 9mm rounds","ammo",1,100,0.1);
		shop.addItem("colt1911","old pistol gun","weapon",67,100,5);
		shop.bank=1000;
		shop.max_cap=100000;
		inventory.bank=1000;
		inventory.max_cap=1000;
	}
	int conditions(string arr[]){
		if (arr[0] == "help") cout << "Witaj w grze" <<endl;
		else if(arr[0]== "start") start();
    	else if(arr[0]== "look" && arr[1]=="sklep") shop.display();
    	else if(arr[0]== "check" && arr[1]=="inv" && arr[2]!="") inventory.check(arr[2]);
    	else if(arr[0]== "check" && arr[1]=="shop" && arr[2]!="") shop.check(arr[2]);
    	else if(arr[0]== "buy" && arr[1]!=""&& arr[2]!="") buy(arr[1],atoi(arr[2].c_str()));
    	else if(arr[0]== "sell" && arr[1]!=""&& arr[2]!="") sell(arr[1],atoi(arr[2].c_str()));
    	else if(arr[0]== "look" && arr[1]=="inv") inventory.display();
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
	shopping1 sklep;
	sklep.init();
	sklep.run();
	cout << "Gra zostala zakonczona"<<endl;
	getch();
    return 0;
}

