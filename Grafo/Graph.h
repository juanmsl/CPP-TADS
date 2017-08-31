# ifndef __GRAPH_H__
# define __GRAPH_H__
# define forLoop(begin, size) for(int i = begin; i < size; i++)
# define INF 999999999

# include <vector>
# include <map>
# include <queue>
# include <stack>
# include <sstream>
# include <fstream>
# include <algorithm>

template<class V, class C>
class Graph {
	protected:
		struct AuxDisktra {
			long index;
			long parent;
			C cost;
			bool operator < (const AuxDisktra& other) {
				return this->cost > other.cost;
			}
		};
		struct AuxEdge {
			long parent;
			long index;
			C cost;
			bool operator < (const AuxEdge& other) {
				return this->cost > other.cost;
			}
		};
		typedef std::map<long, C> Neighbors;
		typedef std::map<long, Neighbors> AdjacencyMatrix;

		std::vector<V> vertices;
		AdjacencyMatrix adjacencyMatrix;
		bool directed;

	public:
		/*************************************************************
							CONSTRUCTOR Y DESTRUCTOR
		*************************************************************/
		Graph(const bool& directed = true);
		~Graph();

		/*************************************************************
							METODOS MODIFICADORES
		*************************************************************/
		void insertVertex(const V& vertex);
		void insertEdge(const long& a, const long& b, const C& cost);
		bool deleteVetex(const long& vertex);
		bool deleteEdge(const long& a, const long& b);

		/*************************************************************
							METODOS DE ACCESO
		*************************************************************/
		const bool edgeExist(const long& a, const long& b) const;
		const C& getCost(const long& a, const long& b);
		const long getIndexOf(const V& vertex);
		const V& getNode(const long& index);
		const int getNumberOfVertices() const;

		/*************************************************************
							METODOS DE RECORRIDOS
		*************************************************************/
		std::vector<long> getNeighborsOf(const long& index);
		std::vector<long> getNeighborhoodOf(const long& index, const int& level);
		void printAsPNG(const std::string& fileName);

		/*************************************************************
							METODOS DE BUSQUEDA DE CAMINOS CORTOS
		*************************************************************/
		AdjacencyMatrix floyd();
		std::vector<std::vector<long>> dijkstra(const long& index);
		std::vector<std::vector<long>> prim(const long& index);
		std::vector<std::vector<long>> kruskal();
		std::vector<long> getShortestPathTo(const std::vector<long>& mst, const long& index);
		long findRoot(const std::vector<long>& mst, const long& index);
};

# include "Graph.hxx"

# endif