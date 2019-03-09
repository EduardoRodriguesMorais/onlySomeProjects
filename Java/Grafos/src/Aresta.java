
public class Aresta {
	private Vertice destino; 
	private Vertice origem;
	private int peso;
	private boolean escolhida; // Algoritmo kruskal
	
	public Aresta(Vertice destino) {
		this.destino = destino;
	}
	
	
	
	public Vertice getOrigem() {
		return origem;
	}



	public void setOrigem(Vertice origem) {
		this.origem = origem;
	}



	public int getPeso() {
		return peso;
	}



	public void setPeso(int peso) {
		this.peso = peso;
	}



	public boolean isEscolhida() {
		return escolhida;
	}



	public void setEscolhida(boolean escolhida) {
		this.escolhida = escolhida;
	}



	public void setDestino(Vertice destino) {
		this.destino = destino;
	}



	public Vertice getDestino() {
		return this.destino;
	}
}
