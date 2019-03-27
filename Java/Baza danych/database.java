import java.util.*;
import java.io.*;
class IO{
	String pobierz(String a){
		try{
			Scanner terminalInput = new Scanner(System.in);
			System.out.println(a);
			String s = terminalInput.nextLine();
			return s;
		}catch(Exception e){
			System.out.println("Bład wejścia");
			return "";
		}
	}
	int pobierzInt(String a){
		try{
			Scanner terminalInput = new Scanner(System.in);
			System.out.println(a);
			int n = terminalInput.nextInt();
			return n;
		}catch(Exception e){
			System.out.println("Niepoprawna liczba");
			return 0;
		}
	}
	float pobierzFloat(String a){
		try{
			Scanner terminalInput = new Scanner(System.in);
			System.out.println(a);
			float n = terminalInput.nextFloat();
			return n;
		}catch(Exception e){
			System.out.println("Niepoprawna liczba");
			return 0;
		}
	}
	osoba wprowadzOsoba(){
		String imie,nazwisko;
		float konto;
		imie = pobierz("Podaj imie"); 
		nazwisko = pobierz("Podaj nazwisko");
		konto = pobierzFloat("Podaj stan konta");
		osoba os = new osoba(imie,nazwisko,konto);
		return os;
	}
	produkt wprowadzProdukt(){
		String opis;
		float cena;
		opis = pobierz("Podaj opis produktu"); 
		cena = pobierzFloat("Podaj cene produktu");
		produkt pr = new produkt(opis,cena);
		return pr;
	}
}
class osoba{
	String imie,nazwisko;
	float konto;
	osoba(String imie,String nazwisko,float konto){
		this.imie=imie;
		this.nazwisko=nazwisko;
		this.konto=konto;
	}
	void wypisz(){
		System.out.println(imie + " " + nazwisko + " " + konto);
	}
	void kup(produkt rachunek,int ilosc){
		konto -= (rachunek.cena*ilosc);
	}
}
class produkt{
	String opis;
	float cena;
	produkt(String opis, float cena){
		this.opis=opis;
		this.cena=cena;
	}
	void wypisz(){
		System.out.println(opis + " cena za 1szt.: " + cena + "zł");
	}
}
public class database{
	public static void main(String args[]) {
		int a=1;
		IO io = new IO();
		osoba os;
		produkt pr;
		Vector <osoba> osoby = new Vector <osoba> (10);
		Vector <produkt> produkty = new Vector <produkt> (10);
		Scanner terminalInput = new Scanner(System.in);
		os = new osoba("Donald","Tfusk",10000);
		osoby.add(os);
		os = new osoba("Jaroslaw","Ka",1500);
		osoby.add(os);
		pr = new produkt("Chleb",2);
		produkty.add(pr);
		pr = new produkt("Woda",1);
		produkty.add(pr);
		do{
			System.out.println("\n1 - Dodaj osobe 2 - Dodaj produkt 3 - wypisz osoby \n4 - wypisz produkty 5 - Wykonaj zakup 0 - wyjscie\n");
			try{
				a = terminalInput.nextInt();
			}catch(Exception e){
				System.out.println("Niepoprawne dane");
			}
			switch(a){
				case 1:
					os=io.wprowadzOsoba();
					osoby.add(os);
				break;
				case 2:
					pr=io.wprowadzProdukt();
					produkty.add(pr);
				break;
				case 3:
					if(!osoby.isEmpty()){
						System.out.println("Osoby:");
						for(int i=0;i<osoby.size();i++){
							os = osoby.get(i);
							os.wypisz();
						}
					}else System.out.println("Brak osob");
				break;
				case 4:
					if(!produkty.isEmpty()){
					System.out.println("Produkty:");
						for(int i=0;i<produkty.size();i++){
							pr = produkty.get(i);
							pr.wypisz();
						}
					}else System.out.println("Brak produktow");
				break;
				case 5:
					int n1,n2,n3;
					do{
						n1 = io.pobierzInt("Podaj numer osoby");
						n2 = io.pobierzInt("Podaj numer produktu");
						n3 = io.pobierzInt("Podaj ilosc");
					}while(produkty.size()<n2||osoby.size()<n1||n1<=0||n2<=0);
					pr = produkty.get(n2-1);
				 	os = osoby.get(n1-1);
					os.kup(pr,n3);
					osoby.set(n1-1,os);
					System.out.println(os.imie+" "+os.nazwisko+" kupil "+n3+" sztuk "+pr.opis+" za "+pr.cena+ "zł i ma teraz "+os.konto+"zł");
				break;
				default:
					if(a!=0) System.out.println("Podales zla liczbe");
				break;
			}
		}while(a!=0);
	}
}
