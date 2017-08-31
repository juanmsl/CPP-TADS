# ifndef __NODE_KD_TREE_H__
# define __NODE_KD_TREE_H__

# include <vector>
# include <algorithm>

template<int Dimension>
class NodeKDTree {
	protected:
		std::vector<double> point;
		NodeKDTree* left;
		NodeKDTree* right;
		
	public:
		// CONSTRUCTOR Y DESTRUCTOR
		NodeKDTree(std::vector<std::vector<double>>& points, const int begin, const int end, const int& level);
		virtual ~NodeKDTree();

		// METODOS DE ACCESO
		void orderVector(std::vector<std::vector<double>>& points, const int begin, const int end);
		std::vector<double> findNearby(std::vector<double>& point, const int& level);
		double distance(const std::vector<double>& A, const std::vector<double>& B);
};

# include "NodeKDTree.hxx"

# endif
