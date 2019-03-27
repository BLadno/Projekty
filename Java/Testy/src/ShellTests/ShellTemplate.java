package ShellTests;
/**Dokumentacja 
 * run - uruchamia terminal (uzyc po zrobieniu conditions)
 * conditions - zadania do wykonania (trzeba zaimplementować)
 * exitCondition - warunek zakonczenia terminalu
 * help - komunikat o pomocy
 * hello - komunikat poczatkowy
 * bye - komunikat koncowy
 * */

import java.util.Scanner;

public abstract class ShellTemplate {

	protected Scanner input = new Scanner(System.in);
	protected String dane;
	protected String[] word;
	public abstract void conditions(String... word);
	public String[] splitData(String input){
		String[] items = input.split(" ");
		//List<String> itemList = Arrays.asList(items);
		return items;
	}
	public void run(){
		hello();
		int x=0;
		do{
			dane=input.nextLine();
			word = splitData(dane);
			if(exitCondition(word)==1){
				x = 1;
			}else{
				conditions(word);
			}
		}while(x==0);
		input.close();
		bye();
	}
	public int exitCondition(String... word){
		if(word[0].equals("EXIT")||word[0].equals("exit")){
			return 1;
		}
		return 0;
	}
	public void help(){
		System.out.println("Przykładowa pomoc");
	}
	public void hello(){
		System.out.println("Terminal został uruchomiony");
	}
	public void bye(){
		System.out.println("Terminal zakończył działanie");
	}
	
}
