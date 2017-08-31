# ifndef __NODE_N_ARY_TREE__
# define __NODE_N_ARY_TREE__

# include <vector>
# include <queue>
# include <string>
# include <sstream>

class NodeNaryTree {
	protected:
		int data;
		std::vector<NodeNaryTree*> nodes;
	public:
		// CONSTRUCTOR Y DESTRUCTOR
		NodeNaryTree(std::vector<int>& datas);
		NodeNaryTree(const int& data);
		~NodeNaryTree();

		// METODOS MODIFICADORES
		bool insert(const int& data, const int& node);

		// METODOS DE ACCESO
		const std::string printAsPNG(int& ID);
		int globalOrder();
		int height();
		int weight();
		int width();
		int antecesorClosest(const int& a, const int& b);
		std::vector<int> findPathOf(const int& data);
};

# endif