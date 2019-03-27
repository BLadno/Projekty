import java.util.*;

class Node{
	List <Node> nodes;
	List <Integer> nodeDist;
	int id;
	String name;
	Node(int id, String name){
		this.id=id;
		this.name=name;
		this.nodes=new ArrayList<>();
		this.nodeDist = new ArrayList<>();
	}
	public int getID() {
		return id;
	}
	public int getID(int i) {
		return nodes.get(i).getID();
	}
	public String getName() {
		return name;
	}
	public void addNode(Node node,int dist) {
		nodes.add(node);
		nodeDist.add(dist);
	}
	public List<Node> getNodes(){
		return nodes;
	}
	public List<Integer> getDists(){
		return nodeDist;
	}
	public int getDist(int i) {
		return nodeDist.get(i);
	}
	public void displayNodes() {
		if(nodes.size()>0) {
			System.out.print(id+": ");
			for(int i=0;i<nodes.size();i++) {
				System.out.print(nodes.get(i).getName()+" "+nodeDist.get(i)+" ");
			}
			System.out.println();
		}
	}
	public void display() {
		for(int i=0;i<nodes.size();i++) {
			System.out.print(nodes.get(i).getName()+"\t");
		}
		System.out.println();
	}
}
public class Graph{
	List <Node> nodes;
	Graph(){
		this.nodes = new ArrayList<>();
	}
	public void addNode(String name) {
		nodes.add(new Node(nodes.size(), name));
	}
	public void connectNode(int nodeID1,int nodeID2,int dist) {
		Node node1 = nodes.get(nodeID1);
		Node node2 = nodes.get(nodeID2);
		node1.addNode(node2, dist);
		node2.addNode(node1, dist);
	}
	public void displayNodes() {
		if(nodes.size()>0)
		for(int i=0;i<nodes.size();i++) {
			nodes.get(i).displayNodes();
		}
	}
    void printSolution(int dist[], int n){
    	int V =nodes.size();
        System.out.print("Vertex  ");
        for (int j = 0; j < V; j++) System.out.print(nodes.get(j).getName()+" ");
        System.out.print("\n\t");
        for (int j = 0; j < V; j++) System.out.print(dist[j]+",\t");
        System.out.println();
    }
    int minDistance(int[] dist,Boolean sptSet[]){
    	int V =nodes.size();
        int min = Integer.MAX_VALUE, min_index=-1;
        for (int v=0; v < V; v++) {
        	if(sptSet[v]==false && dist[v] <= min) {
        		min = dist[v];
                min_index = v;
        	}
        }
        return min_index;
    }
	public int[] Djkstra(int src) {
		int V = nodes.size();
        int dist[] = new int[V];
        int prev[] = new int[V];
        
        Boolean sptSet[] = new Boolean[V];
 
        for (int i = 0; i < V; i++){
            dist[i] = Integer.MAX_VALUE;
            sptSet[i] = false;
            prev[i]=0;
        }

        dist[src] = 0;

        for (int count = 0; count < V-1; count++){
            int u = minDistance(dist,sptSet);
            Node uNode = nodes.get(u);
            //System.out.println(u+" "+uNode.getName()+", ");
            sptSet[u] = true;
            List <Node> nodeLocal = uNode.getNodes();
            for (int v=0; v < nodeLocal.size();v++) {
            	int id=uNode.getID(v);
            	//System.out.print(v+" "+id+", ");
            	int distance = uNode.getDist(v);
            	
                if (!sptSet[id] && dist[u] != Integer.MAX_VALUE &&
                        dist[u]+distance< dist[id]) {
                	dist[id] = dist[u] + distance;
                	prev[id] = u;
                }
            }
            //System.out.println();
        }
        printSolution(dist, V);
        return prev;
	}
	public void displayRoute(int[] prev,int src,int target) {
        System.out.println("droga od "+src+" do "+target);
        List <Integer> a = new ArrayList<>();
        int i=target;
        while(i!=src) {
        	a.add(i);
        	i = prev[i];
        }
        System.out.print(src+" ");
        for(int j=a.size()-1;j>=0;j--) {
        	System.out.print(" > " +a.get(j));
        }
        System.out.println();
	}
	public static void main(String[] args) {
		Graph graf = new Graph();
		graf.displayNodes();
		graf.addNode("punkt0");
		graf.addNode("punkt1");
		graf.addNode("punkt2");
		graf.addNode("punkt3");
		graf.addNode("punkt4");
		graf.addNode("punkt5");
		graf.connectNode(0, 1, 100);
		graf.connectNode(1, 2, 50);
		graf.connectNode(2, 3, 50);
		graf.connectNode(3, 4, 50);
		graf.connectNode(4, 5, 50);
		graf.connectNode(1, 5, 50);
		graf.displayNodes();
		int[] prev = graf.Djkstra(0);
		graf.displayRoute(prev, 0, 4);
		graf.displayRoute(prev, 0, 1);
	}

}
