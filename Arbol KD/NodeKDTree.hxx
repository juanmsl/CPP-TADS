# include "NodeKDTree.h"

int N;

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/
template<int Dimension>
NodeKDTree<Dimension>::NodeKDTree(std::vector<std::vector<double>>& points, const int begin, const int end, const int& level) {
	
	if(begin == end) {
		this->left = NULL;
		this->right = NULL;
		this->point = points[begin];
	} else if(end - begin == 1) {
		this->left = NULL;
		this->point = points[begin];
		this->right = new NodeKDTree(points, end, end, level + 1);
	} else {
		N = level % Dimension;
		orderVector(points, begin, end);

		int mediana = begin + end >> 1;

		this->point = points[mediana];

		this->left = new NodeKDTree(points, begin, mediana, level + 1);
		this->right = new NodeKDTree(points, mediana+1, end, level + 1);	
	}
}

template<int Dimension>
NodeKDTree<Dimension>::~NodeKDTree() {
	if(this->left != NULL){
		delete this->left;
	}
	if(this->right != NULL){
		delete this->right;
	}
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/
bool functionCompare(std::vector<double> a, std::vector<double> b) {
	return a[N] < b[N];
}

template<int Dimension>
void NodeKDTree<Dimension>::orderVector(std::vector<std::vector<double>>& points, const int begin, const int end) {
	std::sort(points.begin() + begin, points.begin() + end, functionCompare);
}

template<int Dimension>
std::vector<double> NodeKDTree<Dimension>::findNearby(std::vector<double>& point, const int& level) {
	N = level % Dimension;
	if(this->point[N] < point[N]) {
		if(this->right != NULL) {
			std::vector<double> returnPoint = this->right->findNearby(point, level + 1);
			double distanceReturn = this->distance(returnPoint, point);
			double miDistance = this->distance(this->point, point);
			if(distanceReturn < miDistance) return returnPoint;
			else return this->point;
		} else {
			return this->point;
		}
	} else {
		if(this->left != NULL) {
			std::vector<double> returnPoint = this->left->findNearby(point, level + 1);
			double distanceReturn = this->distance(returnPoint, point);
			double miDistance = this->distance(this->point, point);
			if(distanceReturn < miDistance) return returnPoint;
			else return this->point;
		} else {
			return this->point;
		}
	}
}

template<int Dimension>
double NodeKDTree<Dimension>::distance(const std::vector<double>& A, const std::vector<double>& B) {
	int dis = 0;
	for(int i = 0; i < Dimension; i++) {
		dis += (A[i] - B[i]) * (A[i] - B[i]);
	}
	return dis;
}