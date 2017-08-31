# include "KDTree.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/
template<int Dimension>
KDTree<Dimension>::KDTree(std::vector<std::vector<double>>& points) {
	this->root = new NodeKDTree<Dimension>(points, 0, points.size(), 0);
}

template<int Dimension>
KDTree<Dimension>::~KDTree() {
	delete this->root;
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/
template<int Dimension>
std::vector<double> KDTree<Dimension>::findNearby(std::vector<double>& point) {
	if(this->root != NULL) {
		return this->root->findNearby(point, 0);
	}
}