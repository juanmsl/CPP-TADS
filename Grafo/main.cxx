# include <iostream>
# include <iomanip>
# include "Graph.h"

int begin, end, n;
void execute(Graph<int, int>& g);
void grafo0();
void grafo1();
void grafo2();
void grafo3();
void grafo4();

int main() {

	grafo0();
	system("pause & cls");
	grafo1();
	system("pause & cls");
	grafo2();
	system("pause & cls");
	//grafo3();
	grafo4();

	return 0;
}

template<class V, class C>
void execute(Graph<V, C>& g) {
	std::cout<<"Neighbors:\n";
	for(V i = begin; i <= end; i++){
		std::vector<long> indices = g.getNeighborsOf(g.getIndexOf(i));
		std::cout<<"Neighbors of "<<i<<": ";
		for(auto c : indices) {
			std::cout<<g.getNode(c)<<" ";
		}
		std::cout<<"\n";
	}
	std::cout<<"\nNeighborhood to 2:\n";
	for(V i = begin; i <= end; i++){
		std::vector<long> indices = g.getNeighborhoodOf(g.getIndexOf(i), 2);
		std::cout<<"Neighborhood to 2 of "<<i<<": ";
		for(auto c : indices) {
			std::cout<<g.getNode(c)<<" ";
		}
		std::cout<<"\n";
	}
	std::cout<<"\nDikstra (MST):\n";
	for(V i = begin; i <= end; i++){
		std::vector<long> indices = g.dikstra(g.getIndexOf(i));
		std::cout<<"MST of "<<i<<": ";
		for(auto c : indices) {
			std::cout<<c<<" ";
		}
		std::cout<<"\n";
	}
	std::cout<<"\nDikstra (Paths):\n";
	for(V i = begin; i <= end; i++){
		std::vector<long> indices = g.dikstra(g.getIndexOf(i));
		std::stack<long> path = g.getShortestPathTo(indices, g.getIndexOf(n));
		std::cout<<"Shortest path from "<<i<<" to "<<n<<" : ";
		if(path.empty()) {
			std::cout<<"No path";
		} else {
			while(!path.empty()) {
				long c = path.top();
				path.pop();
				std::cout<<g.getNode(c)<<" ";
			}
		}
		std::cout<<"\n";
	}
	std::cout<<"\nFloyd Warshal:\n";
	g.floyd();
	std::cout<<"\nPrim (MST):\n";
	for(V i = begin; i <= end; i++){
		std::vector<long> indices = g.prim(g.getIndexOf(i));
		std::cout<<"MST of "<<i<<": ";
		for(auto c : indices) {
			std::cout<<c<<" ";
		}
		std::cout<<"\n";
	}
	std::cout<<"\nPrim (Paths):\n";
	for(V i = begin; i <= end; i++){
		std::vector<long> indices = g.prim(g.getIndexOf(i));
		std::stack<long> path = g.getShortestPathTo(indices, g.getIndexOf(n));
		std::cout<<"Shortest path from "<<i<<" to "<<n<<" : ";
		if(path.empty()) {
			std::cout<<"No path";
		} else {
			while(!path.empty()) {
				long c = path.top();
				path.pop();
				std::cout<<g.getNode(c)<<" ";
			}
		}
		std::cout<<"\n";
	}
}

void grafo0() {
	begin = 0; end = 5, n = 3;

	Graph<int, int> g(false);
	for(int i = begin; i <= end; i++) {
		g.insertVertex(i);
	}

	g.insertEdge(g.getIndexOf(0), g.getIndexOf(1), 3);
	g.insertEdge(g.getIndexOf(0), g.getIndexOf(4), 1);
	g.insertEdge(g.getIndexOf(0), g.getIndexOf(3), 6);
	g.insertEdge(g.getIndexOf(1), g.getIndexOf(4), 5);
	g.insertEdge(g.getIndexOf(1), g.getIndexOf(2), 3);
	g.insertEdge(g.getIndexOf(2), g.getIndexOf(5), 6);
	g.insertEdge(g.getIndexOf(3), g.getIndexOf(4), 5);
	g.insertEdge(g.getIndexOf(3), g.getIndexOf(5), 2);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(2), 6);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(5), 4);

	execute<int, int>(g);
}

void grafo1() {
	begin = 1; end = 5, n =1;

	Graph<int, int> g;
	for(int i = begin; i <= end; i++) {
		g.insertVertex(i);
	}

	g.insertEdge(g.getIndexOf(1), g.getIndexOf(3), 6);
	g.insertEdge(g.getIndexOf(1), g.getIndexOf(4), 3);
	g.insertEdge(g.getIndexOf(2), g.getIndexOf(1), 3);
	g.insertEdge(g.getIndexOf(3), g.getIndexOf(4), 2);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(3), 1);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(2), 1);
	g.insertEdge(g.getIndexOf(5), g.getIndexOf(2), 4);
	g.insertEdge(g.getIndexOf(5), g.getIndexOf(4), 2);

	execute<int, int>(g);
}

void grafo2() {
	begin = 0; end = 7, n = 6;
	Graph<int, int> g;
	for(int i = begin; i <= end; i++) {
		g.insertVertex(i);
	}

	g.insertEdge(g.getIndexOf(0), g.getIndexOf(1), 5);
	g.insertEdge(g.getIndexOf(0), g.getIndexOf(7), 8);
	g.insertEdge(g.getIndexOf(0), g.getIndexOf(4), 9);
	g.insertEdge(g.getIndexOf(1), g.getIndexOf(2), 12);
	g.insertEdge(g.getIndexOf(1), g.getIndexOf(3), 15);
	g.insertEdge(g.getIndexOf(1), g.getIndexOf(7), 4);
	g.insertEdge(g.getIndexOf(2), g.getIndexOf(3), 3);
	g.insertEdge(g.getIndexOf(2), g.getIndexOf(6), 11);
	g.insertEdge(g.getIndexOf(3), g.getIndexOf(6), 9);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(7), 5);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(5), 4);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(6), 20);
	g.insertEdge(g.getIndexOf(5), g.getIndexOf(2), 1);
	g.insertEdge(g.getIndexOf(5), g.getIndexOf(6), 13);
	g.insertEdge(g.getIndexOf(7), g.getIndexOf(2), 7);
	g.insertEdge(g.getIndexOf(7), g.getIndexOf(5), 6);

	execute<int, int>(g);
}

void grafo3() {
	begin = 'a'; end = 'i', n = 'f';
	Graph<char, int> g(false);
	for(int i = begin; i <= end; i++) {
		g.insertVertex(i);
	}

	g.insertEdge(g.getIndexOf('a'), g.getIndexOf('b'), 4);
	g.insertEdge(g.getIndexOf('a'), g.getIndexOf('h'), 8);
	g.insertEdge(g.getIndexOf('b'), g.getIndexOf('h'), 11);
	g.insertEdge(g.getIndexOf('b'), g.getIndexOf('c'), 8);
	g.insertEdge(g.getIndexOf('h'), g.getIndexOf('i'), 7);
	g.insertEdge(g.getIndexOf('h'), g.getIndexOf('g'), 1);
	g.insertEdge(g.getIndexOf('i'), g.getIndexOf('g'), 6);
	g.insertEdge(g.getIndexOf('i'), g.getIndexOf('c'), 2);
	g.insertEdge(g.getIndexOf('c'), g.getIndexOf('f'), 4);
	g.insertEdge(g.getIndexOf('c'), g.getIndexOf('d'), 7);
	g.insertEdge(g.getIndexOf('d'), g.getIndexOf('f'), 14);
	g.insertEdge(g.getIndexOf('d'), g.getIndexOf('e'), 9);
	g.insertEdge(g.getIndexOf('e'), g.getIndexOf('f'), 10);
	g.insertEdge(g.getIndexOf('g'), g.getIndexOf('f'), 2);

	execute<char, int>(g);
}

void grafo4() {
	begin = 1; end = 12, n = 8;
	Graph<int, int> g;
	for(int i = begin; i <= end; i++) {
		g.insertVertex(i);
	}

	g.insertEdge(g.getIndexOf(1), g.getIndexOf(7), 1);
	g.insertEdge(g.getIndexOf(1), g.getIndexOf(2), 3);
	g.insertEdge(g.getIndexOf(2), g.getIndexOf(12), 3);
	g.insertEdge(g.getIndexOf(2), g.getIndexOf(3), 2);
	g.insertEdge(g.getIndexOf(3), g.getIndexOf(5), 2);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(1), 2);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(5), 4);
	g.insertEdge(g.getIndexOf(4), g.getIndexOf(7), 2);
	g.insertEdge(g.getIndexOf(6), g.getIndexOf(4), 5);
	g.insertEdge(g.getIndexOf(6), g.getIndexOf(5), 3);
	g.insertEdge(g.getIndexOf(7), g.getIndexOf(6), 2);
	g.insertEdge(g.getIndexOf(7), g.getIndexOf(11), 5);
	g.insertEdge(g.getIndexOf(8), g.getIndexOf(9), 3);
	g.insertEdge(g.getIndexOf(8), g.getIndexOf(10), 5);
	g.insertEdge(g.getIndexOf(9), g.getIndexOf(6), 11);
	g.insertEdge(g.getIndexOf(9), g.getIndexOf(3), 7);
	g.insertEdge(g.getIndexOf(10), g.getIndexOf(12), 8);
	g.insertEdge(g.getIndexOf(11), g.getIndexOf(9), 10);
	g.insertEdge(g.getIndexOf(12), g.getIndexOf(3), 9);
	g.insertEdge(g.getIndexOf(12), g.getIndexOf(8), 2);

	execute<int, int>(g);
}