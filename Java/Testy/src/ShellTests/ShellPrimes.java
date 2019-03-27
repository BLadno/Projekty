package ShellTests;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class ShellPrimes extends ShellTemplate{

	/**
	 * @param args
	 */
	List<Long> primes = new ArrayList<>();
	ShellPrimes(){
		long num[] = {1,2,3};
		primes.add(num[0]);
		primes.add(num[1]);
		primes.add(num[2]);
	}
	public int getInt(String a){
		int num=0;
		try{
			num = Integer.parseInt(a);
		}catch(NumberFormatException nfe){
			System.out.println(nfe);
			num=0;
		}
		return num;
	}
	public long getLong(String a){
		long num=0;
		try{
			num = Long.parseLong(a);
		}catch(NumberFormatException nfe){
			System.out.println(nfe);
			num=0;
		}
		return num;
	}
	public void getSize(){
		System.out.println("Rozmiar tablicy "+(primes.size()-1));
	}
	public void display(){
		if(primes.size()<1000){
			for(long i:primes) System.out.print(i+", ");
		}
	}
	public void getById(int a){
		if(a<primes.size()) System.out.println(primes.get(a));
		else System.out.println("Zbyt duze id");
	}
	public void isPrime(long a){
		System.out.println(a);
		int j=1;
		
		while(j<=primes.size()){
			if(a%primes.get(j)==0) {
				System.out.println("Liczba "+ a +" nie jest pierwsza");
				break; // nie jest pierwsza
			}
			j++;
		}
		System.out.println("Liczba "+ a +" jest pierwsza");
	}
	public void saveToFile(){
        String fileName = "primes.txt";

        try {
            FileWriter fileWriter = new FileWriter(fileName);
            long start = System.currentTimeMillis();
            BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
            for(int i=0;i<primes.size();i++){
            	bufferedWriter.write(primes.get(i)+"\n");
            }
            bufferedWriter.close();
            long elapsedTimeMillis = System.currentTimeMillis()-start;
    		float elapsedTimeSec = elapsedTimeMillis/1000F;
    		System.out.println("Koniec "+elapsedTimeSec+"s");
        }
        catch(IOException ex) {
            System.out.println("Error writing to file '"+ fileName + "'");
        }
	}
	public void readFromFile(){
		String fileName = "primes.txt";

        String line = null;
        int i=0;
        try {
            FileReader fileReader = new FileReader(fileName);
            long start = System.currentTimeMillis();
            
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            
            while((line = bufferedReader.readLine()) != null) {
                //System.out.println(i+" "+line +" "+ getLong(line));
                if(i>=primes.size()) primes.add(getLong(line));
                i++;
            }   
            bufferedReader.close(); 
            long elapsedTimeMillis = System.currentTimeMillis()-start;
    		float elapsedTimeSec = elapsedTimeMillis/1000F;
    		System.out.println("Koniec "+elapsedTimeSec+"s");
        }
        catch(FileNotFoundException ex) {
            System.out.println("Unable to open file '" + fileName + "'");                
        }
        catch(IOException ex) {
            System.out.println("Error reading file '"  + fileName + "'");                  
        }
    }
	public void makePrimeTillId(int a){
		int size=primes.size()-1,e=size;
		long i=primes.get(size);
		int k=0;
		long start = System.currentTimeMillis();
		while(e<a){
			k=0;
			i+=2;
			for(int l=2;i>=primes.get(l)*primes.get(l) && k==0;l++){
				if(i%primes.get(l)==0) k=1;
			}
			if(k==0&&e<primes.size()) {
				e++;
				primes.add(i);
			}
		}
		long elapsedTimeMillis = System.currentTimeMillis()-start;
		float elapsedTimeSec = elapsedTimeMillis/1000F;
		System.out.println("Koniec "+elapsedTimeSec+"s");
	}
	public void makePrimeTillNum(long a){
		int size=primes.size()-1,e=size;
		long i=primes.get(size);
		int k=0;
		long start = System.currentTimeMillis();
		while(i<a){
			k=0;
			i+=2;
			for(int l=2;i>=primes.get(l)*primes.get(l) && k==0;l++){
				if(i%primes.get(l)==0) k=1;
			}
			if(k==0&&e<primes.size()) {
				e++;
				primes.add(i);
			}
		}
		long elapsedTimeMillis = System.currentTimeMillis()-start;
		float elapsedTimeSec = elapsedTimeMillis/1000F;
		System.out.println("Koniec "+elapsedTimeSec+"s");
	}
	public void makePrimeThreaded(int threadCount,long a){
		if(threadCount>128) threadCount=128;
		List<ThreadPrime> threads = new ArrayList<>();
		for(int i=0;i<threadCount;i++){
			threads.add(new ThreadPrime(i,primes,2*threadCount));
		}
		int size = primes.size()-2;
		long last = primes.get(size);
		long limit = last*last-1;
		if(a>limit) a=limit;
		System.out.println("size: "+size+" last: "+last+" a: "+a+" limit: "+limit);
		for(ThreadPrime i:threads){
			i.setTarget(a);
			i.start();
		}
		long start = System.currentTimeMillis();
		try {
			for(ThreadPrime i:threads){
				i.join();
			}
		}catch (Exception e) {
            System.out.println(e.getMessage());
        }
		List<Long> result = new ArrayList<>();
		for(ThreadPrime i:threads){
			i.display();
			result.addAll(i.getArray());
		}
		Collections.sort(result);
		primes.addAll(result);
		long elapsedTimeMillis = System.currentTimeMillis()-start;
		float elapsedTimeSec = elapsedTimeMillis/1000F;
		System.out.println("Koniec dzialan po czasie "+elapsedTimeSec+"s");
		//if(result.size()<100) for(long i:result) System.out.print(i+" ,");
	}
	public void conditions(String... word){
		if(word[0].equals("size")) getSize();
		else if(word[0].equals("show")) display();
		else if(word[0].equals("getLast")) getById(primes.size()-1);
		else if(word[0].equals("save")) saveToFile();
		else if(word[0].equals("load")) readFromFile();
		if(word.length>1){
			if(word[0].equals("get")) getById(getInt(word[1]));
			else if(word[0].equals("isPrime")) isPrime(getLong(word[1]));
			else if(word[0].equals("makeTillId")) makePrimeTillId(getInt(word[1]));
			else if(word[0].equals("makeTillNum")) makePrimeTillNum(getLong(word[1]));
		}
		if(word.length>2){
			if(word[0].equals("makeThreads")) makePrimeThreaded(getInt(word[1]),getLong(word[2]));
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ShellTemplate shell = new ShellPrimes();
		shell.run();
	}

}
class ThreadPrime extends Thread implements Runnable{
	List<Long> primes = new ArrayList<>();
	List<Long> localPrimes = new ArrayList<>();
	int jump = 2,offset=0;
	long a;
	ThreadPrime(int i,List<Long> primes,int jump){
		super();
		setName("Thread "+i);
		this.primes = primes;
		this.jump=jump;
		this.offset=i*2;
	}
	public void setTarget(long a){
		this.a=a;
	}
	public void run(){
		//System.out.println(Thread.currentThread().getName()+" Tu jestem");
		makePrimeTillNum(a);
	}
	public void makePrimeTillNum(long a){
		int size=primes.size()-1,e=size;
		long i=primes.get(size)+offset;
		int k=0;
		//long start = System.currentTimeMillis();
		while(i<a){
			k=0;
			i+=jump;
			for(int l=2;i>=primes.get(l)*primes.get(l) && k==0;l++){
				if(i%primes.get(l)==0) k=1;
			}
			if(k==0&&e<primes.size()) {
				//primes.add(i);
				localPrimes.add(i);
			}
		}
		/*long elapsedTimeMillis = System.currentTimeMillis()-start;
		float elapsedTimeSec = elapsedTimeMillis/1000F;
		System.out.println(Thread.currentThread().getName()+
				" skonczyl w czasie "
		+elapsedTimeSec+"s");*/
	}
	public List<Long> getArray(){
		return localPrimes;
	}
	public void display(){
		if(localPrimes.size()<1000){
			for(long i:localPrimes) System.out.print(i+", ");
			System.out.println("\n");
		}
		
	}
}
