//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

#include "Timers.h"
Timers <1> keys;
Timers <1> licznik;
Timers <1> akcja[9];
Timers <2> akcja2;

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

//Zmienne listy
String list[]={"Menu","Test przyciskow","Czas","Tekst 1", "Tekst pomoc", "Timer start", "Timer stop", "Timer reset", "Menu pomoc", "Timer pomoc"};
int list_size=9, list_choosen=0, list_select=0;

//Zmienne tekstu
int text_pos=0,text_skip=4;

//Zmienne timer
int timer=0,timer_isRun=0;

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);

 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  

 return btnNONE;  // when all others fail, return this...
}

void wypisz(int pos1,int pos2, String text){
     lcd.setCursor(pos1,pos2); //pos,1
     lcd.print(text);
}
void przyciski(){
  wypisz(0,0,"Test przyciskow");
  if(lcd_key==btnRIGHT) wypisz(4,1,"R");
  if(lcd_key==btnLEFT) wypisz(1,1,"L");
  if(lcd_key==btnUP) wypisz(2,1,"U");
  if(lcd_key==btnDOWN) wypisz(3,1,"D");
  if(lcd_key==btnSELECT) wypisz(0,1,"S");
  if(lcd_key==btnNONE) wypisz(0,1,"       ");
}
void czas(){
  wypisz(9,1,String(millis()/1000));  // display seconds elapsed since power-up 
}
void czas2(){
  String czas3 = String(millis()/1000) + "." + String(millis()%1000) + "s";
  lcd.clear();
  wypisz(0,0,"Czas od startu");
  wypisz(0,1,czas3);  // display seconds elapsed since power-up 

  if((lcd_key!=btnNONE)and(lcd_key!=btnSELECT)) list_choosen=0;
}

void menu(){
  if(lcd_key==btnUP) list_select-=1;
  if(lcd_key==btnDOWN) list_select+=1;
  if(lcd_key==btnLEFT) list_select-=2;
  if(lcd_key==btnRIGHT) list_select+=2;
  
  if(list_select<1) list_select=1;
  if(list_select>list_size)list_select=list_size;
  if(lcd_key==btnSELECT) {
    list_choosen=list_select;
  }
  
  lcd.clear(); //wyswietlanie
  if(list_select==list_size){
    wypisz(0,0,list[list_select-1]);
    wypisz(0,1,">"+list[list_select]+"<");
  }else{
    wypisz(0,0,">"+list[list_select]+"<");
    wypisz(0,1,list[list_select+1]);
  }
  if(list_choosen==list_select) lcd.clear();
}
void wypiszTekst(String naglowek,String text){
  String text2;
  for(int i=0;i<16;i++){
    text2+=text[text_pos+i];
  }
  if(lcd_key==btnDOWN) {
    list_choosen=0;
    text_pos=0;
    text2="";
  }
  if(lcd_key==btnLEFT) text_pos-=text_skip;
  if(lcd_key==btnRIGHT) text_pos+=text_skip;
  if(text_pos<0) text_pos=0;
  if(text_pos>text.length()-16) text_pos=text.length()-16;
  lcd.clear(); //wyswietlanie
  wypisz(0,0,naglowek);
  wypisz(0,1,text2);
}
void wypiszTekst1(){
  String nag="Tekst 1";
  String text="Oto przykladowy tekst ktory jest dlugi.";
  wypiszTekst(nag,text);
}
void wypiszTekst2(){
  String nag="Tekst - pomoc";
  String text="Right - przesuniecie w prawo, Left - przesuniecie w lewo, Down - powrot do menu";
  wypiszTekst(nag,text);
}
void wypiszTekst3(){
  String nag="Menu - pomoc";
  String text="Select - wybor opcji, DOWN - pole w dol, UP - pole w gore RIGHT - 2 pola w dol, LEFT - 2 pola w gore";
  wypiszTekst(nag,text);
}
void wypiszTekst4(){
  String nag="Timer - pomoc";
  String text="Timer start: DOWN - powrot do menu, UP - stop licznika, Timer stop: LEFT - powrot do menu, RIGHT - start licznika";
  wypiszTekst(nag,text);
}
void getKeys(){
  lcd_key = read_LCD_buttons();
}
void startLicznik(){
  lcd.clear();
  wypisz(0,0,"Licznik");
  wypisz(0,1,"wystartowal");
  timer_isRun=1;
  if(lcd_key==btnDOWN) list_choosen=0;
  if(lcd_key==btnUP) list_choosen=6;
}
void wypiszCzas(){
  String czas3="Czas: " + String(timer/100) + "." + String(timer%100) + "s";
  wypisz(0,1,czas3);
  timer_isRun=0;
}
void stopLicznik(){
  lcd.clear();
  wypisz(0,0,"Licznik stop");
  wypiszCzas();
  if(lcd_key==btnLEFT) list_choosen=0;
  if(lcd_key==btnRIGHT) list_choosen=5;
}
void resetLicznik(){
  lcd.clear();
  wypiszCzas();
  if((lcd_key!=btnNONE)and(lcd_key!=btnSELECT)) {
    timer=0;
    list_choosen=0;
  }
}
void licz(){
  timer+=1;
}
void setup(){
  lcd.begin(16, 2);              // start the library
  keys.attach(0,200,getKeys);
  licznik.attach(0, 10, licz);
  akcja[0].attach(0,200,menu);
  akcja2.attach(0, 200, przyciski);
  akcja2.attach(1, 1000, czas);
  akcja[1].attach(0, 1000, czas2);
  akcja[2].attach(0, 400, wypiszTekst1);
  akcja[3].attach(0, 400, wypiszTekst2);
  akcja[4].attach(0, 200, startLicznik);
  akcja[5].attach(0, 200, stopLicznik);
  akcja[6].attach(0, 200, resetLicznik);
  akcja[7].attach(0, 400, wypiszTekst3);
  akcja[8].attach(0, 400, wypiszTekst4);
}

void loop(){
  keys.process();                           //Pobiera wcisniety klawisz
  if(list_choosen==0) akcja[0].process();   //Menu
  if(list_choosen==1) akcja2.process();     //Test przyciskow
  if(list_choosen==2) akcja[1].process();   //Czas
  if(list_choosen==3) akcja[2].process();   //Tekst 1
  if(list_choosen==4) akcja[3].process();   //Tekst - pomoc
  if(list_choosen==5) akcja[4].process();   //timer start
  if(list_choosen==6) akcja[5].process();   //timer stop
  if(list_choosen==7) akcja[6].process();   //timer reset
  if(list_choosen==8) akcja[7].process();   //Menu - pomoc
  if(list_choosen==9) akcja[8].process();   //Timer - pomoc
  if(timer_isRun==1) licznik.process();     //licznik
} //inicjalizacja lub aktualizacja wszystkich procedur(wątków, zdarzeń itp.)
