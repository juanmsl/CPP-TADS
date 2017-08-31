# include <iostream>
# include <fstream>
# include <vector>
# include "KDTree.h"

int main(int argv, char *args[]){
	
	std::ifstream input("entrada.txt");

	if(input.is_open()) {
		int N;
		double value;
		input>>N;

		std::vector<std::vector<double>> points;
		while(!input.eof()) {
			std::vector<double> point;
			for(int i = 0; i < N; i++) {
				input>>value;
				point.push_back(value);
			}
			points.push_back(point);
		}
		input.close();

    	const int NN = const_cast<const int&>(N);
		KDTree<3> arbol(points);

		double x, y, z;
		std::cout<<"x y z << ";
		while(std::cin>>x>>y>>z) {
			std::vector<double> p;
			p.push_back(x);
			p.push_back(y);
			p.push_back(z);
			std::vector<double> v = arbol.findNearby(p);

			std::cout<<"Closest point to ["<<x<<","<<y<<","<<z<<"] -> ["<<v[0]<<","<<v[1]<<","<<v[2]<<"]\n";
			std::cout<<"x y z << ";
		}
	}

	return 0;
}

