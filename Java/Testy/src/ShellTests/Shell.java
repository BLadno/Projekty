package ShellTests;
public class Shell extends ShellTemplate{
	
	public float add(String a,String... b){
		try{
			//int result = Integer.parseInt(a);
			float result = Float.parseFloat(a);
			for(int i=0;i<b.length;i++){
				result += Float.parseFloat(b[i]);
			}
			return result;
		}catch(NumberFormatException nfe){
			System.out.println(nfe);
		}
		return 0;
	}
	public void conditions(String... word){
		if(word[0].equals("add") && word[1]!="" && word[2]!=""){
			System.out.println(word[1] + "+" + word[2] +"="+ add(word[1],word[2]));
		}else if(word[0].equals("help")) {
			help();
		}else{
			System.out.println("Nieznane polecenie");
		}
		//int foo = Integer.parseInt(myString);
		//System.out.println("Pierwszy= "+word[0]+" Wszystko: "+dane);
	}
	public static void main(String[] args) {
		Shell obj = new Shell();
		obj.run();
		System.exit(0);
	}
}
