# ifndef __N_ARY_TREE__
# define __N_ARY_TREE__

# include <vector>
# include <string>
# include <sstream>
# include <fstream>
# include "NodeNaryTree.h"

class NaryTree {
	protected:
		NodeNaryTree* root;
	public:
		// CONSTRUCTOR Y DESTRUCTOR
		NaryTree(std::vector<int>& datas);
		NaryTree();
		~NaryTree();

		// METODOS MODIFICADORES
		bool insert(const int& data, const int& node);

		// METODOS DE ACCESO
		bool isEmpty() const;
		bool isNotEmpty() const;
		void printAsPNG(const std::string& fileName);
		int globalOrder();
		int height();
		int weight();
		int width();
		int antecesorClosest(const int& a, const int& b);
};

# endif