import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class Grafo {
	public static void main(String[] args) {
		ArrayList<Vertice> lista = new ArrayList<Vertice>();
		Vertice a = new Vertice('A');
		Vertice b = new Vertice('B');
		Vertice c = new Vertice('C');
		Vertice d = new Vertice('D');
		lista.add(a);
		lista.add(b);
		lista.add(c);
		lista.add(d);
		a.apontar(b);
		a.apontar(c);
		c.apontar(b);
		b.apontar(d);
		
		bfs(a);
		for(Vertice v : lista) {
			String pai = v.getPai()==null?"NULL":String.valueOf(v.getPai().getRotulo());
			System.out.println("Vertice: "+v.getRotulo()+" Visitado: "+v.isVisitado()+" Pai: "+pai);
		}
		
		dfs(lista);
		prim(a);
		kruskal(lista);
		
	}
	 
	public static void bfs (Vertice vertice) {
		Queue <Vertice> fila = new LinkedList<Vertice>();
		Vertice cara;
		vertice.setVisitado(true);
		fila.add(vertice);
		while(!fila.isEmpty()) {
			cara = fila.remove();
			for(Aresta aresta :cara.getArestas()) {
				if(!aresta.getDestino().isVisitado()) {
					fila.add(aresta.getDestino());
					aresta.getDestino().setVisitado(true);
					aresta.getDestino().setPai(cara);
				}
			}
		}
	}
	
	
	
	public static void dfs(ArrayList<Vertice> vertice){
		Stack<Vertice> pilha = new Stack<Vertice>();
		for(Vertice v: vertice) {
			if(!v.isVisitado()) {
				v.setVisitado(true);
				v.setPai(v);
				pilha.add(v);
				while(!pilha.isEmpty()) {
					Vertice cara = pilha.pop();
					System.out.println(" "+cara.getClass());
					for(Aresta aresta: cara.getArestas()) {
						if(!aresta.getDestino().isVisitado()) {
							aresta.getDestino().setVisitado(true);
							aresta.getDestino().setPai(cara);
							pilha.push(cara);
						}
					}
				}
			}
		}
	}
	
	public static void prim(Vertice vertice) {
		 Queue<Vertice> fila = new LinkedList<Vertice>();
		 Vertice cara;
		 vertice.setCor(Vertice.preto);
		 vertice.setCusto(0);
		 fila.add(vertice);
		 while (!fila.isEmpty()) {
			 cara = fila.remove();
			 for (Aresta aresta : cara.getArestas()) {
				 if (aresta.getDestino().getCor() != Vertice.preto) {
					 if (aresta.getDestino().getCor() == Vertice.branco) {
						 fila.add(aresta.getDestino());
						 aresta.getDestino().setCor(Vertice.cinza);
						 }
						 if (aresta.getPeso() < aresta.getDestino().getCusto()) {
							 aresta.getDestino().setCusto(aresta.getPeso());
							 aresta.getDestino().setPai(cara);
						 }
					 }
				 }
				 cara.setCor(Vertice.preto);
			 }
		}

	public static void kruskal(List<Vertice> listaAdj) {
		 List<Aresta> listaArestas = new ArrayList<Aresta>();
		 Vertice origem, destino;
		 for (Vertice v : listaAdj)
			 for (Aresta a : v.getArestas()) {
				 listaArestas.add(a);
				 a.setEscolhida(false);
			  }
		     Collections.sort(listaArestas);
			 for (Aresta a : listaArestas) {
				 origem = a.getOrigem();
				 destino = a.getDestino();
				 while (origem.getDisjunto() == 0)
					 origem = origem.getPai();
				 while (destino.getDisjunto() == 0)
					 destino = destino.getPai();
				 if (origem.getDisjunto() == -1) {
					 destino.setDisjunto(destino.getDisjunto() + origem.getDisjunto());
					 origem.setDisjunto(0);
					 origem.setPai(destino);
					 a.setEscolhida(true);
				 }
				 else {
					 if (destino.getDisjunto() == -1) {
						 origem.setDisjunto(origem.getDisjunto() + destino.getDisjunto());
						 destino.setDisjunto(0);
						 destino.setPai(origem);
						 a.setEscolhida(true);
					 }
				 }
			 }
		}

}

