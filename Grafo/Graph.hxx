# include "Graph.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/
template<class V, class C>
Graph<V, C>::Graph(const bool& directed) {
	this->directed = directed;
}

template<class V, class C>
Graph<V, C>::~Graph() {

}

/*************************************************************

					METODOS MODIFICADORES

*************************************************************/
template<class V, class C>
void Graph<V, C>::insertVertex(const V& vertex) {
	this->vertices.push_back(vertex);
}
# include <iostream>
template<class V, class C>
void Graph<V, C>::insertEdge(const long& a, const long& b, const C& cost) {
	if(!edgeExist(a, b)) {
		this->adjacencyMatrix[a][b] = cost;
		if(!this->directed) {
			this->adjacencyMatrix[b][a] = cost;
		}
		return;
	}
	throw std::domain_error("\nERROR: The edge already exists.\n\n");
}

template<class V, class C>
bool Graph<V, C>::deleteVetex(const long& vertex) {
	if(vertex < this->vertices.size()) {
		this->vertices.erase(this->vertices.begin() + vertex);
		typename AdjacencyMatrix::iterator row = this->adjacencyMatrix.find(vertex);
		if(row != this->adjacencyMatrix.end()) this->adjacencyMatrix.erase(row);
		for(row = this->adjacencyMatrix.begin(); row != this->adjacencyMatrix.end(); row++) {
			typename Neighbors::iterator column = row->second.find(vertex);
			if(column != row->second.end()) {
				row->second.erase(column);
			}
		}
		return true;
	}
	return false;
}

template<class V, class C>
bool Graph<V, C>::deleteEdge(const long& a, const long& b) {
	if(edgeExist(a, b)) {
		typename AdjacencyMatrix::iterator row = this->adjacencyMatrix.find(a);
		typename Neighbors::iterator column = row->second.find(b);
		row->second.erase(column);
		return true;
	}
	return false;
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/
template<class V, class C>
const bool Graph<V, C>::edgeExist(const long& a, const long& b) const {
	typename AdjacencyMatrix::const_iterator row = this->adjacencyMatrix.find(a);
	if(row != this->adjacencyMatrix.end()){
		typename Neighbors::const_iterator column = row->second.find(b);
		return column != row->second.end();
	}
	return false;
}

template<class V, class C>
const C& Graph<V, C>::getCost(const long& a, const long& b) {
	if(edgeExist(a, b)) {
		return this->adjacencyMatrix[a][b];
	}
	throw std::domain_error("\nERROR: The edge isn't exists.\n\n");
}

template<class V, class C>
const long Graph<V, C>::getIndexOf(const V& vertex) {
	typename std::vector<V>::iterator it = std::find(this->vertices.begin(), this->vertices.end(), vertex);
	if(it != this->vertices.end()){
		return (long) std::distance(this->vertices.begin(), it);
	}
	throw std::domain_error("\nERROR: The vertex isn't exists.\n\n");
}

template<class V, class C>
const V& Graph<V, C>::getNode(const long& index) {
	if(index < this->vertices.size()) {
		return this->vertices[index];
	}
	throw std::domain_error("\nERROR: The vertex isn't exists.\n\n");
}

template<class V, class C>
const int Graph<V, C>::getNumberOfVertices() const {
	return this->vertices.size();
}

/*************************************************************

					METODOS DE RECORRIDOS

*************************************************************/
template<class V, class C>
std::vector<long> Graph<V, C>::getNeighborsOf(const long& index) {
	std::vector<long> vertices;
	for(long i = 0; i < this->vertices.size(); i++) {
		if(edgeExist(index, i)) {
			vertices.push_back(i);
		}
	}
	return vertices;
}

template<class V, class C>
std::vector<long> Graph<V, C>::getNeighborhoodOf(const long& index, const int& level) {
	std::vector<long> vertices;
	std::queue<long> q;
	std::queue<int> levels;
	std::map<long, bool> marcados;
	q.push(index);
	levels.push(level);

	while(!q.empty()) {
		long vertice = q.front();
		int l = levels.front();
		q.pop();
		levels.pop();
		if(marcados[vertice]) continue;

		marcados[vertice] = true;
		vertices.push_back(vertice);
		for(int i = 0; i < this->vertices.size(); i++) {
			if(edgeExist(vertice, i)) { 
				if(l > 0) {
					q.push(i);
					levels.push(l -1);
				}
			}
		}
	}
	return vertices;
}

template<class V, class C>
void Graph<V, C>::printAsPNG(const std::string& fileName) {
	std::stringstream str;
	str << "digraph g{\n";

	for(long i = 0; i < this->vertices.size(); i++) {
		str	<< "\"" << i <<"\" [label=\""<< this->vertices[i] <<"\"]" <<"\n";
	}
	for(long i = 0; i < this->vertices.size(); i++) {
		for(long j = 0; j < this->vertices.size(); j++) {
			if(edgeExist(i, j)) {
				str	<< "\"" << i <<"\"->\""<< j << "\""<< "[shape=box,label=" << this->adjacencyMatrix[i][j] << "]" <<"\n";
			}
		}
	}
	str << "}";

	std::ofstream s(std::string(fileName + ".dot").c_str());
	s<<str.str();
	std::stringstream sal;
	s.close();
	sal << "dot " << fileName + ".dot -Tpng > ";
	sal << fileName;
	std::system(sal.str().c_str());
	std::remove(std::string(fileName + ".dot").c_str());
	system(fileName.c_str());
}

/*************************************************************

					METODOS DE BUSQUEDA DE CAMINOS CORTOS

*************************************************************/
template<class V, class C>
typename Graph<V, C>::AdjacencyMatrix Graph<V, C>::floyd() {
	long vSize = this->vertices.size();
	AdjacencyMatrix D;
	for(long i = 0; i < vSize; i++) {
		for(long j = 0; j < vSize; j++) {
			if(i == j) D[i][j] = 0;
			else D[i][j] = INF;
		}
	}
	for(long i = 0; i < vSize; i++) {
		for(long j = 0; j < vSize; j++) {
			if(edgeExist(i, j)) {
				D[i][j] = adjacencyMatrix[i][j];
			}
		}
	}
	for(long k = 0 ; k < vSize; k++) {
		for(long i = 0 ; i < vSize; i++) {
			for(long j = 0 ; j < vSize; j++) {
				if(D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}

	return D;
}

template<class V, class C>
std::vector<std::vector<long>> Graph<V, C>::dijkstra(const long& index) {
	std::vector<long> mst(this->vertices.size(), -1);
	std::vector<AuxDisktra> q;
	std::vector<bool> marcados(this->vertices.size(), false);

	AuxDisktra seed;
	seed.index = index;
	seed.parent = index;
	seed.cost = 0;
	q.push_back(seed);

	while(!q.empty()) {
		seed = q.front();
		std::pop_heap(q.begin(), q.end());
		q.pop_back();

		if(marcados[seed.index]) continue;
		marcados[seed.index] = true;
		mst[seed.index] = seed.parent;

		for(long i = 0; i < this->vertices.size(); i++) {
			if(edgeExist(seed.index, i)) {
				AuxDisktra child;
				child.index = i;
				child.parent = seed.index;
				child.cost = seed.cost + adjacencyMatrix[seed.index][i];
				q.push_back(child);
				std::make_heap(q.begin(), q.end());
			}
		}
	}

	std::vector<std::vector<long>> paths;
	for(int i = 0; i < this->vertices.size(); i++) {
		std::vector<long> path = getShortestPathTo(mst, i);
		paths.push_back(path);
	}
	return paths;
}

template<class V, class C>
std::vector<std::vector<long>> Graph<V, C>::prim(const long& index) {
	std::vector<long> mst(this->vertices.size(), -1);
	std::vector<bool> Vnew(this->vertices.size(), false);

	int numMarcados = 1;
	mst[index] = index;
	Vnew[index] = true;

	while(numMarcados < this->vertices.size()) {
		int min = INF, ii = -1, ij = -1;
		for(int i = 0; i < Vnew.size(); i++) {
			if(Vnew[i]) {
				for(int j = 0; j < this->vertices.size(); j++) {
					if(edgeExist(i, j) && !Vnew[j]) {
						if(adjacencyMatrix[i][j] < min) {
							min = adjacencyMatrix[i][j];
							ii = i;
							ij = j;
						}
					}
				}
			}
		}

		if(ii == -1 && ij == -1) break;
		Vnew[ij] = true;
		mst[ij] = ii;
		numMarcados++;
	}

	std::vector<std::vector<long>> paths;
	for(int i = 0; i < this->vertices.size(); i++) {
		std::vector<long> path = getShortestPathTo(mst, i);
		paths.push_back(path);
	}
	return paths;
}

template<class V, class C>
std::vector<std::vector<long>> Graph<V, C>::kruskal() {
	std::vector<long> mst(this->vertices.size(), -1);
	std::vector<AuxEdge> q;

	for(int i = 0; i < this->vertices.size(); i++) {
		mst[i] = i;
		for(int j = 0; j < this->vertices.size(); j++) {
			if(edgeExist(i, j)) {
				AuxEdge aux;
				aux.parent = i;
				aux.index = j;
				aux.cost = this->adjacencyMatrix[i][j];
				q.push_back(aux);
				std::make_heap(q.begin(), q.end());
			}
		}
	}

	while(q.size() > 0) {
		AuxEdge edge = q.front();
		std::pop_heap(q.begin(), q.end());
		q.pop_back();

		long a = findRoot(mst, edge.parent);
		long b = findRoot(mst, edge.index);
		if(a != b) {
			mst[edge.index] = edge.parent;
		}
	}

	std::vector<std::vector<long>> paths;
	for(int i = 0; i < this->vertices.size(); i++) {
		std::vector<long> path = getShortestPathTo(mst, i);
		paths.push_back(path);
	}
	return paths;
}

template<class V, class C>
std::vector<long> Graph<V, C>::getShortestPathTo(const std::vector<long>& mst, const long& index) {
	std::vector<long> path;
	long i = index;
	while(mst[i] != i && mst[i] > -1) {
		path.insert(path.begin(), i);
		i = mst[i];
	}
	if(mst[i] == i) path.insert(path.begin(), i);
	return path;
}

template<class V, class C>
long Graph<V, C>::findRoot(const std::vector<long>& mst, const long& index) {
	long i = index;
	while(mst[i] != i && mst[i] != -1) {
		i = mst[i];
	}
	return i;
}