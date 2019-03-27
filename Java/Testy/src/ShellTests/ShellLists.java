package ShellTests;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;


public class ShellLists extends ShellTemplate{

	private List<String> lista = new LinkedList<>();
	private Set<String> set = new HashSet<>();
	private Map<String, String> mapa = new HashMap<>();
	public void addToList(String a){
		lista.add(a);
	}
	public void displayList(){
		if(!lista.isEmpty()){
			System.out.println("Rozmiar listy "+lista.size());
			System.out.print("Zawartosc: ");
			for(String item : lista) {
			    System.out.print(item+",");
			}
			System.out.println("");
		}else{
			System.out.println("Lista jest pusta");
		}
	}
	public void containsList(String a){
		if(lista.contains(a)){
			System.out.println("lista zawiera "+a);
		}else{
			System.out.println("lista nie zawiera "+a);
		}
	}
	public void removeFromList(String a){
		lista.remove(a);
	}
	public void replaceFromList(String a,String b){
		int x=0;
		if(!lista.isEmpty()){
			for(String item : lista) {
			    if(item.equals(a)) x++;
			}
		}else System.out.println("Lista jest pusta");
		if(x==0) System.out.println("Nie odnaleziono przedmiotu");
		if(x>1) System.out.println("Zastapiono wiecej niz 1");
		while(x>0){
			lista.remove(a);
			lista.add(b);
			x--;
		}
	}
	public void conditions(String... word){
		if(word[0].equals("list")){
			if(word[1].equals("all")) displayList();
			else if(word.length>2){
				if(word[1].equals("add")) addToList(word[2]);
				else if(word[1].equals("contains")) containsList(word[2]);
				else if(word[1].equals("remove")) removeFromList(word[2]);
				else if(word.length>3){
					if(word[1].equals("replace")) replaceFromList(word[2],word[3]);
				}else System.out.println("Brakujacy argument");
			}else System.out.println("Brakujacy argument");
		}else if(word[0].equals("help")) help();
		else System.out.println("Nieznane polecenie");
	}
	public void help(){
		System.out.println("help exit\n" +
				"list [all/add/contains/remove/replace]");
	}
	public static void main(String[] args) {
		ShellLists obj = new ShellLists();
		obj.run();
		System.exit(0);
	}

}
