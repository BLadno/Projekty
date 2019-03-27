#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;

#define NBUF 1024
string pobierzsciezke(){
	char buffer[NBUF];
    getcwd(buffer,NBUF);
	string ret(buffer);
    return ret;
}
const string domowy = pobierzsciezke();
const char * domowy_katalog = domowy.c_str();

//*****************************************************************************************

class navigation{
	public:
	string pobierzsciezke(){
	    char buffer[NBUF];
	    getcwd(buffer,NBUF);
	    string ret(buffer);
	    return ret;
	}
	
	void pwd(){
	    cout << pobierzsciezke() <<endl;
	}
	
	void cd(string argument2){
	    const char *par2=argument2.c_str();
	    if (argument2 == "")
	        chdir(domowy_katalog);
	    else
    		chdir(par2);
	}
	
	void ls(){
	    DIR *dpdf;
	    struct dirent *epdf;
	    dpdf = opendir("./");
	    if (dpdf != NULL){
	        while ((epdf = readdir(dpdf))){
	            cout << epdf->d_name << endl;
	        }
	    }
	}
};

class fileOperation{
	public:
	void kopiuj(string par2,string par3){
	    ifstream plik1 (par2.c_str(), fstream::binary);
	    if (!plik1.good() )
	        cout << "plik nie istnieje" <<endl;
	    else{
	        ofstream plik2 (par3.c_str(), fstream::trunc|fstream::binary);
	        if(!plik2.good())
	            cout << "Nie mozna otworzyc pliku do zapisu" << endl;
	        else{
	            plik2 << plik1.rdbuf ();
	            plik1.close();
	            plik2.close();
	            cout << " Wykonano " << endl;
	        }
	    }
	}
	void stworz(string inp,string tekst=""){
		ofstream plik1(inp.c_str());
		plik1 << tekst << endl;
		plik1.close();
	}

	void nazwa(string inp,string nazwa){
		if( rename( inp.c_str(),nazwa.c_str() ) == 0 )
	        cout << "Pomyslnie zmieniono nazwe pliku." <<endl;
	    else
	    	cout << "Nie udalo sie zmienic nazwy pliku." <<endl;
	}

	void usun(string inp){
		char c;
		cout << "Czy jestes pewien ze chcesz usunac plik: "<< inp <<" ?(T/N)"<<endl;
		cin >> c;
		if(c==84||c==116)
		if( remove( inp.c_str() ) == 0 )
	         cout << "Usunieto pomyslnie plik." <<endl;
	    else
	         cout << "Nie udalo sie skasowac pliku." <<endl;
	}

	void wypisz(string inp){
	    ifstream plik1 (inp.c_str(), fstream::in);
	    if (!plik1.good() )
	        cout << " Plik nie istnieje lub brak dostepu " <<endl;
	    else{
			cout << "Zawartosc pliku " << inp <<endl <<endl;
	        cout << plik1.rdbuf ();
	        cout << endl;
	        plik1.close();
	    }
	}
	
	void find(string inp,string napis){
		int a=1,b=0,j=0;
		string tekst;
	    ifstream plik1 (inp.c_str(), fstream::in);
	    if (!plik1.good() )
	        cout << " Plik nie istnieje lub brak dostepu " <<endl;
	    else{
    	    while( !plik1.eof() ){
    	        getline( plik1, tekst );
    	        for(int i=0;i<=tekst.size();i++){
					if(tekst[i]==napis[0])  a=0,j=0;
					while (a==0 && j+i<=tekst.size() ){
						if(tekst[i+j]!=napis[j]){
						 	a=1;
						 	if(j==napis.size()) b++;
						}
						j++;
					}
        	    }
       		}
        	cout << "Odnaleziono "<< b <<" "<<napis<<endl;
        	cout << "Zadanie zakonczone" << endl;
        	plik1.close();
    	}
	}
}; 

class fileEditor{
	public:
	fileOperation FO;
	void zapisz(string inp,string tekst=""){
		ofstream plik1;
	    plik1.open(inp.c_str(), fstream::app);
	    if (!plik1.good() )
	    	FO.stworz(inp);
	    else{
			plik1.write( & tekst[0], tekst.length() );
			plik1.write("\n",1);
	        plik1.close();
	    }
	}

	void editOut(string inp,string tekst=""){
		if(tekst=="") {
			cout << "wprowdz tekst do zapisania"<<endl;
			getline(cin,tekst);
		}
		ofstream plik1;
	    plik1.open(inp.c_str(), fstream::out);
	    if (!plik1.good() )
	        cout << " Plik nie istnieje lub brak dostepu " <<endl;
	    else
	    {
			plik1.write( & tekst[0], tekst.length() );
			plik1.write("\n",1);
	        plik1.close();
	        cout << "Plik zostal zapisany" << endl;
	    }
	}
	void editApp(string inp,string tekst=""){
		if(tekst=="") {
			cout << "wprowdz tekst do zapisania"<<endl;
			getline(cin,tekst);
		}
		ofstream plik1;
	    plik1.open(inp.c_str(), fstream::app);
	    if (!plik1.good() )
	        cout << " Plik nie istnieje lub brak dostepu " <<endl;
	    else
	    {
			plik1.write( & tekst[0], tekst.length() );
			plik1.write("\n",1);
	        plik1.close();
	        cout << "Plik zostal zapisany" << endl;
	    }
	}
	
	void kwadrat(string inp){
		int n=(rand() % 20 ) + 1;
		int b;
		char a;
		ofstream plik1;
	    plik1.open(inp.c_str(), fstream::out);
	    if (!plik1.good() )
	    	FO.stworz(inp);
	    else{
			for (int j=0;j<n;j++){
				for(int i=0;i<n;i++){
					b=rand()%2;
					if(b==0)a = (rand() % 25 ) + 65; 
					else a = (rand() % 25 ) + 97; 
					plik1.write( & a, 1 );
				}
				plik1.write("\n",1);
			}
	        plik1.close();
	    }
	}
};

class messanger{
	public:
	void trojkat(string inp){
	    //int nParam = stod(inp,NULL);
	    int nParam=(rand() % 20 ) + 1;
	    for (int i=0; i<nParam; ++i){
	        for (int j=i; j<nParam; ++j){
	            printf("*");
	        }
	        printf("\n");
	    }
	}

	void help()
	{
	    cout << endl;
	    cout << " Mozliwe polecenia : "<< endl;
	    cout << " 'cd' 'ls' 'pwd' 'help' 'trojkat' 'exit' 'komunikat' 'pauza' 'kopiuj' 'kwadrat'"<<endl;
	    cout << " 'wypisz' 'stworz' 'usun' 'nazwa' 'editOut' 'editApp' 'find' 'zapiszHistoria'"<<endl;
	    cout << " <nazwa polecenia> --help (Wyswietla pomoc do danego polecenia)"<<endl;
	    cout << " exit -konczy dzialanie programu "<< endl;
	    cout << endl;
	}

	void pauza()
	{
	    cout <<"Wcisnij klawisz aby kontynuowac."<< endl;
	    getch();
	}

	void komunikat(string inp[])
	{
		int i=1;
		while(inp[i]!=""){
			cout << inp[i]+" ";
			i++;
		}
	    cout << endl;
	}
};

class shell{
	private:
	string polecenie;
	navigation Nav;
	fileOperation FO;
	fileEditor FE;
	messanger Mes;
	
	public:
	void wykonaj(string inp){
		int args=8;
		string polecenie;
		ifstream plik1 (inp.c_str(), fstream::in);
		if (!plik1.good() )
	        cout << " Plik nie istnieje lub brak dostepu " <<endl;
	    else
		while( !plik1.eof() )
	    {
	        getline( plik1, polecenie );
    		string arr[args];
	    	int i = 0;
    		stringstream ssin(polecenie);
    		while (ssin.good() && i < args){
        		ssin >> arr[i];
        		++i;
    		}
			if (arr[0] == "pwd") Nav.pwd();
	        else if (arr[0] == "ls")	Nav.ls();
    	    else if (arr[0] == "help")	Mes.help();
        	else if (arr[0] == "pauza")	Mes.pauza();
	        else if (arr[0] == "komunikat" && !arr[1].empty())	Mes.komunikat(arr);
    	    else if (arr[0] == "cd" && !arr[1].empty())	Nav.cd(arr[1]);
        	else if (arr[0] == "wypisz" && !arr[1].empty())	FO.wypisz(arr[1]);
	        else if (arr[0] == "wykonaj" && !arr[1].empty()) wykonaj(arr[1]);
    	    else if (arr[0] == "usun" && !arr[1].empty()) FO.usun(arr[1]);
        	else if (arr[0] == "trojkat" && !arr[1].empty()) Mes.trojkat(arr[1]);
        	else if (arr[0] == "kwadrat" && !arr[1].empty()) FE.kwadrat(arr[1]);
	        else if (arr[0] == "stworz" && !arr[1].empty()) FO.stworz(arr[1],arr[2]);
    	    else if (arr[0] == "editOut" && !arr[1].empty()) FE.editOut(arr[1],arr[2]);
    	    else if (arr[0] == "editApp" && !arr[1].empty()) FE.editApp(arr[1],arr[2]);
        	else if (arr[0] == "nazwa" && !arr[1].empty() && !arr[2].empty()) FO.nazwa(arr[1],arr[2]);
	        else if (arr[0] == "find" && !arr[1].empty() && !arr[2].empty()) FO.find(arr[1],arr[2]);
    	    else if (arr[0] == "kopiuj" && !arr[1].empty() && !arr[2].empty()) FO.kopiuj(arr[1],arr[2]);
        	else cout << "Nieznane polecenie, lub brakuje argumentow. wpisz 'help',aby poznac dostepne polecenia" <<endl;
		}
	}
	
	void terminal(int debug=0){
		int args=8;
		queue <string> historia;
    	Mes.help();
    	cout <<endl;
    	while((polecenie !="exit") && (polecenie !="EXIT"))
    	{
    	    cout << pobierzsciezke() <<" -> ";
    	    getline(cin,polecenie);
    	    
        	string arr[args];
    		int i = 0;
    		stringstream ssin(polecenie);
    		while (ssin.good() && i < args){
    	    	ssin >> arr[i];
    	    	++i;
    		}
			historia.push(polecenie);
    	    if(debug==1) for(int i=0;i<args;i++) if(arr[i]!="") cout << "arr[" << i<<"]: "<< arr[i] << endl;
		
        	if (arr[1] == "--help")
			{
	            if (arr[0]=="pwd") 		     cout << "pwd - wyswietla aktualna sciezke "<<endl;
    	        else if (arr[0]=="ls") 	     cout << "ls - wyswietla listing biezacego katalogu "<< endl;
        	    else if (arr[0]=="help")     cout << "help - wyswietla liste mozliwych komend " <<endl;
            	else if (arr[0]=="wypisz")   cout << "wypisz <plik> - Wypisuje zawartosc pliku jako tekst"<<endl;
	            else if (arr[0]=="stworz")   cout << "stworz <plik> <zawartosc> - Tworzy plik"<<endl;
    	        else if (arr[0]=="usun")     cout << "usun <plik> - Usuwa plik"<<endl;
    	        else if (arr[0]=="nazwa")     cout << "nazwa <plik> <nowa nazwa pliku> - zmienia nazwe pliku"<<endl;
        	    else if (arr[0]=="find")     cout << "find <plik> - Odnajduje tekst w pliku"<<endl;
        	    else if (arr[0]=="komunikat")     cout << "komunikat <tekst> - Wyswietla tekst na ekranie"<<endl;
        	    else if (arr[0]=="pauza")     cout << "pauza - Oczekuje na wcisniecie przycisku"<<endl;
            	else if (arr[0]=="trojkat") cout << "trojkat liczba - rysuje trójkąt o podstawie liczba"<<endl;
            	else if (arr[0]=="kwadrat") cout << "kwadrat <plik> - zapisuje wylosowany ciag znakow do pliku"<<endl;
	            else if (arr[0]=="cd") 	     cout << "cd <sciezka> - zmienia katalog roboczy, cd - zmienia na domowy." <<
    	                 " cd / -zmienia na glowny. cd .. -cofa "<< endl;
        	    else if (arr[0]=="kopiuj")   cout << "kopiuj <plik zrodlowy> <plik docelowy> " <<
            	         "- kopiuje plik zrodlowy pod nazwa zadana jako docelowy"<< endl;
            	else if (arr[0]=="editOut")     cout << "editOut <plik> <tekst> - Zapisuje tekst na pocz�tku pliku" << endl;
            	else if (arr[0]=="editApp")     cout << "editApp <plik> <tekst> - Zapisuje tekst na koncu pliku" << endl;
            	else if (arr[0]=="wykonaj")     cout << "wykonaj <plik> - interpretuje plik jako polecenia" << endl;
            	else if (arr[0]=="zapiszHistoria")     cout << "zapiszHistoria <plik> - zapisuje historie wpisywanych polecen do danego pliku" << endl;
	        }else{
    	        if (arr[0] == "pwd") Nav.pwd();
        	    else if (arr[0] == "ls")	Nav.ls();
            	else if (arr[0] == "help")	Mes.help();
	            else if (arr[0] == "pauza")	Mes.pauza();
    	        else if (arr[0] == "komunikat" && !arr[1].empty())	Mes.komunikat(arr);
        	    else if (arr[0] == "cd" && !arr[1].empty())	Nav.cd(arr[1]);
            	else if (arr[0] == "wypisz" && !arr[1].empty())	FO.wypisz(arr[1]);
	            else if (arr[0] == "wykonaj" && !arr[1].empty()) wykonaj(arr[1]);
    	        else if (arr[0] == "usun" && !arr[1].empty()) FO.usun(arr[1]);
        	    else if (arr[0] == "trojkat" && !arr[1].empty()) Mes.trojkat(arr[1]);
        	    else if (arr[0] == "kwadrat" && !arr[1].empty()) FE.kwadrat(arr[1]);
            	else if (arr[0] == "stworz" && !arr[1].empty()) FO.stworz(arr[1],arr[2]);
            	else if (arr[0] == "editOut" && !arr[1].empty()) FE.editOut(arr[1],arr[2]);
            	else if (arr[0] == "editApp" && !arr[1].empty()) FE.editApp(arr[1],arr[2]);
	            else if (arr[0] == "nazwa" && !arr[1].empty() && !arr[2].empty()) FO.nazwa(arr[1],arr[2]);
    	        else if (arr[0] == "find" && !arr[1].empty() && !arr[2].empty()) FO.find(arr[1],arr[2]);
        	    else if (arr[0] == "kopiuj" && !arr[1].empty() && !arr[2].empty()) FO.kopiuj(arr[1],arr[2]);
        	    else if (arr[0] == "zapiszHistoria" && !arr[1].empty()){
					while(historia.empty()==false){
						string polecenie2 = historia.front();
						historia.pop();
						FE.zapisz(arr[1],polecenie2);
					}
					cout << "Historia zostala zapisana" << endl;
    	    	}
	        }
    	}
	}
};
int main(){
	srand( time( NULL ) );
	shell powloka;
	powloka.terminal();
    return 0;
}

