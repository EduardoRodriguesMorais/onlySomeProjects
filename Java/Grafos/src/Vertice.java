import java.util.ArrayList;

public class Vertice {
	public static char branco = 'B'; // Nada
	public static char cinza = 'C'; // Adicionado na fila
	public static char preto = 'P'; // Já incluído (todos os vértices visitados)
	private char rotulo; 
	private ArrayList <Aresta> arestas;
	private boolean visitado;
	private char cor; 
	private int custo; // Algoritmo Prim
	private Vertice pai; // Algoritmo Prim e kruskal
	private int disjunto; // Algoritmo kruskal
	
	
	public Vertice(char rotulo) {
		this.setRotulo(rotulo);
		this.setPai(null);
		this.setVisitado(false);
		this.arestas = new ArrayList<Aresta>();
	}
	
	public void setCor(char cor) { this.cor = cor; }
	
	
	
	public char getCor() {
		return cor;
	}

	public int getCusto() {
		return custo;
	}



	public void setCusto(int custo) {
		this.custo = custo;
	}



	public int getDisjunto() {
		return disjunto;
	}



	public void setDisjunto(int disjunto) {
		this.disjunto = disjunto;
	}



	public static char getBranco() {
		return branco;
	}



	public static void setBranco(char branco) {
		Vertice.branco = branco;
	}



	public static char getCinza() {
		return cinza;
	}



	public static void setCinza(char cinza) {
		Vertice.cinza = cinza;
	}



	public static char getPreto() {
		return preto;
	}



	public static void setPreto(char preto) {
		Vertice.preto = preto;
	}



	public void apontar(Vertice verticeDestino) {
		this.arestas.add(new Aresta(verticeDestino));
	}
	
	public char getRotulo() {
		return rotulo;
	}
	public void setRotulo(char rotulo) {
		this.rotulo = rotulo;
	}
	public ArrayList<Aresta> getArestas() {
		return arestas;
	}
	public void setArestas(ArrayList<Aresta> arestas) {
		this.arestas = arestas;
	}
	public boolean isVisitado() {
		return visitado;
	}
	public void setVisitado(boolean visitado) {
		this.visitado = visitado;
	}
	public Vertice getPai() {
		return pai;
	}
	public void setPai(Vertice pai) {
		this.pai = pai;
	}
}
