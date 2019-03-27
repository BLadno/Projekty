//Klasy bazowe strony, ludzie i klasy pochodne blogi, strony wiadomosci, gazet, firm itp., administratorzy, goœcie, zalogowani.
//Przeci¹¿yæ operator strumienia i dodawania i odejmowania z grupy przegl¹daj¹cych lub zmieniaj¹cych strony i parê wed³ug w³asnego pomys³u.
#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>
using namespace std;

class osoba{
	public:
		string imie,nazwisko;
		osoba(string n_imie = "N/A", string n_nazwisko = "N/A") : imie(n_imie), nazwisko(n_nazwisko) {}
		friend ostream & operator<< (ostream &wyjscie, const osoba &o){
			return wyjscie <<o.imie << " " <<o.nazwisko;
		}
		bool operator==(const osoba &q) {return imie==q.imie;} 					//Przyjmuje obiekt
		bool operator==(const string &q) {return (imie+" "+nazwisko)==q;} 		//Przyjmuje stringa
		string operator>(const osoba &q) {return q.imie+" "+q.nazwisko;} 		//Przyjmuje stringa
		void operator=(const string &q) {imie=q;} 								//Przyjmuje stringa
		void operator=(const osoba &q) {imie=q.imie; nazwisko=q.nazwisko;} 		//przyjmuje obiekt
		void operator<<(const string &q) {cout << q<<endl;} 					//Przyjmuje stringa
		void operator<<(const osoba &q) {cout << q.imie<<endl;} 				//Przyjmuje obiekt
};

class admin: public osoba{
	public:
		string imie,nazwisko;
		admin(string n_imie = "N/A", string n_nazwisko = "N/A") : imie(n_imie), nazwisko(n_nazwisko) {}
		friend ostream & operator<< (ostream &wyjscie, const admin &o){
			return wyjscie <<o.imie << " " <<o.nazwisko;
		}
};

class gosc: public osoba{
	public:
		string imie,nazwisko;
		gosc(string n_imie = "N/A", string n_nazwisko = "N/A") : imie(n_imie), nazwisko(n_nazwisko) {}
		friend ostream & operator<< (ostream &wyjscie, const gosc &o){
			return wyjscie <<o.imie << " " <<o.nazwisko;
		}
};

class zalogowany: public osoba{
	public:
		string imie,nazwisko;
		zalogowany(string n_imie = "N/A", string n_nazwisko = "N/A") : imie(n_imie), nazwisko(n_nazwisko) {}
		friend ostream & operator<< (ostream &wyjscie, const zalogowany &o){
			return wyjscie <<o.imie << " " <<o.nazwisko;
		}
};
 
class strona{
	public:
		string tresc,tytul;
		vector <osoba> osoby;
		vector <gosc> goscie;
		vector <admin> admini;
		vector <zalogowany> zalogowani;
		strona(string temat = "N/A", string opis = "N/A") : tytul(temat), tresc(opis) {}
		friend ostream & operator<< (ostream &wyjscie, const strona &o){
			return wyjscie << "\nTytul: " <<o.tytul << endl << "Tresc: " <<o.tresc<<endl;
		}
		bool operator==(const strona &q) {return tytul==q.tytul;} 	//Przyjmuje obiekt
		bool operator==(const string &q) {return tytul==q;} 		//Przyjmuje stringa
		void operator +(const osoba &q) { osoby.push_back(q);}
		void operator +(const gosc &q) { goscie.push_back(q); }
		void operator +(const admin &q) { admini.push_back(q); }
		void operator +(const zalogowany &q) { zalogowani.push_back(q); }
		void operator -(const string &q) {
			if(!osoby.empty()) for(int i=0;i<osoby.size();i++){
				if(osoby[i]==q) {
					cout << osoby[i]<< " zostala usunieta\n";
					osoby.erase(osoby.begin()+i);
				}
			}
			if(!goscie.empty()) for(int i=0;i<goscie.size();i++){
				if(goscie[i]==q) {
					cout << goscie[i]<< " zostala usunieta\n";
					goscie.erase(goscie.begin()+i);
				}
			}
			if(!admini.empty()) for(int i=0;i<admini.size();i++){
				if(admini[i]==q) {
					cout << admini[i]<< " zostala usunieta\n";
					admini.erase(admini.begin()+i);
				}
			}
			if(!zalogowani.empty()) for(int i=0;i<zalogowani.size();i++){
				if(zalogowani[i]==q) {
					cout << zalogowani[i]<< " zostala usunieta\n";
					zalogowani.erase(zalogowani.begin()+i);
				}
			}
		}
		void wypisz(){
			cout <<endl;
			if(!osoby.empty()) cout << "Osoby: "<<endl;
			for(int i=0;i<osoby.size();i++) cout << osoby[i]<<endl;
			if(!goscie.empty()) cout << "Goscie: "<<endl;
			for(int i=0;i<goscie.size();i++) cout << goscie[i]<<endl;
			if(!admini.empty()) cout << "Administratorzy: "<<endl;
			for(int i=0;i<admini.size();i++) cout << admini[i]<<endl;
			if(!zalogowani.empty()) cout << "Zalogowani: "<<endl;
			for(int i=0;i<zalogowani.size();i++) cout << zalogowani[i]<<endl;
			cout <<endl;

		}
};

class blog: public strona{
	public:
		string tresc,tytul;
		blog(string temat = "N/A", string opis = "N/A") : tytul(temat), tresc(opis) {}
		friend ostream & operator<< (ostream &wyjscie, const blog &o){
			return wyjscie << "\nTytul: " <<o.tytul << endl << "Tresc: " <<o.tresc<<endl;
		}
};

class wiadomosci: public strona{
	public:
		string tresc,tytul;
		wiadomosci(string temat = "N/A", string opis = "N/A") : tytul(temat), tresc(opis) {}
		friend ostream & operator<< (ostream &wyjscie, const wiadomosci &o){
			return wyjscie << "\nTytul: " <<o.tytul << endl << "Tresc: " <<o.tresc<<endl;
		}
};

class gazeta: public strona{
	public:
		string tresc,tytul;
		gazeta(string temat = "N/A", string opis = "N/A") : tytul(temat), tresc(opis) {}
		friend ostream & operator<< (ostream &wyjscie, const gazeta &o){
			return wyjscie << "\nTytul: " <<o.tytul << endl << "Tresc: " <<o.tresc<<endl;
		}
};

class firma: public strona{
	public:
		string tresc,tytul;
		firma(string temat = "N/A", string opis = "N/A") : tytul(temat), tresc(opis) {}
		friend ostream & operator<< (ostream &wyjscie, const firma &o){
			return wyjscie << "\nTytul: " <<o.tytul << endl << "Tresc: " <<o.tresc<<endl;
		}
};

int main(){
	//string test="test OK";
	//printf("%s\n", test.c_str());
	osoba os1("Osobista","Osobistosc"),os2("Donald","Tussecki");
   	gosc gosc1("test","czlowieka");
   	admin admin1("Administrator", "Administralny");
   	zalogowany log1("Zalogowany","Gosciu");
   	strona strona1("Prawa czlowieka","Taki dokument dla niewiedzacych");
   	blog blog1("Blog","Przykladowy blog");
   	wiadomosci news1("Wiadomosci","Przykladowe wiadomosci");
   	gazeta gazeta1("Gazeta","Przykladowa gazeta");
   	firma firma1("Firma","Przykladowa firma");
   	
   	strona1+os1; strona1+os2; strona1+gosc1; strona1+admin1; strona1+log1;
   	
	cout << strona1; strona1.wypisz();
   	string test2 =(os1 > os1);
   	strona1-test2;
   	cout << strona1; strona1.wypisz();
   	
   	blog1+os1; blog1+admin1;
   	cout << blog1; blog1.wypisz();

   	news1+os2; news1+admin1;
   	cout << news1; news1.wypisz();

   	gazeta1+gosc1; gazeta1+admin1;
   	cout << gazeta1; gazeta1.wypisz();
   	
   	firma1+os2; firma1+gosc1;
   	cout << firma1; firma1.wypisz();
	
	return 0;
}
