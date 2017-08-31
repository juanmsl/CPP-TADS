# ifndef __KD_TREE_H__
# define __KD_TREE_H__

# include <vector>
# include "NodeKDTree.h"

template<int Dimension>
class KDTree {
	protected:
		NodeKDTree<Dimension>* root;
	
	public:
		// CONSTRUCTOR Y DESTRUCTOR
		KDTree(std::vector<std::vector<double>>& points);
		virtual ~KDTree();

		// METODOS DE ACCESO
		std::vector<double> findNearby(std::vector<double>& point);
};

# include "KDTree.hxx"

# endif
