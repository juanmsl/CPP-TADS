# include <iostream>
# include <vector>
# include <string>
# include "NaryTree.h"

int main() {

	std::vector<int> datas;

	datas.push_back(4);  datas.push_back(1);
	datas.push_back(3);  datas.push_back(2);
	datas.push_back(2);  datas.push_back(6);
	datas.push_back(0);  datas.push_back(17);
	datas.push_back(0);  datas.push_back(18);
	datas.push_back(0);  datas.push_back(7);
	datas.push_back(3);  datas.push_back(8);
	datas.push_back(0);  datas.push_back(19);
	datas.push_back(0);  datas.push_back(20);
	datas.push_back(0);  datas.push_back(21);
	datas.push_back(2);  datas.push_back(3);
	datas.push_back(0);  datas.push_back(9);
	datas.push_back(0);  datas.push_back(10);
	datas.push_back(2);  datas.push_back(4);
	datas.push_back(0);  datas.push_back(11);
	datas.push_back(2);  datas.push_back(12);
	datas.push_back(0);  datas.push_back(22);
	datas.push_back(0);  datas.push_back(23);
	datas.push_back(4);  datas.push_back(5);
	datas.push_back(0);  datas.push_back(13);
	datas.push_back(0);  datas.push_back(14);
	datas.push_back(4);  datas.push_back(15);
	datas.push_back(0);  datas.push_back(24);
	datas.push_back(0);  datas.push_back(25);
	datas.push_back(0);  datas.push_back(26);
	datas.push_back(0);  datas.push_back(27);
	datas.push_back(3);  datas.push_back(16);
	datas.push_back(0);  datas.push_back(28);
	datas.push_back(0);  datas.push_back(29);
	datas.push_back(0);  datas.push_back(30);

	NaryTree arbol(datas);
	arbol.printAsPNG("Arbol.png");

	std::cout<<"Orden global: "<<arbol.globalOrder()<<"\n";
	std::cout<<"Altura: "<<arbol.height()<<"\n";
	std::cout<<"Peso: "<<arbol.weight()<<"\n";
	std::cout<<"Ancho: "<<arbol.width()<<"\n";
	std::cout<<"Antecesor entre 9 y 23: "<<arbol.antecesorClosest(9, 23)<<"\n";
	std::cout<<"Antecesor entre 13 y 27: "<<arbol.antecesorClosest(13, 27)<<"\n";
	std::cout<<"Antecesor entre 22 y 23: "<<arbol.antecesorClosest(22, 23)<<"\n";

	return 0;
}