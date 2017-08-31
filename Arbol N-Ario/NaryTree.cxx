# include "NaryTree.h"


// CONSTRUCTOR Y DESTRUCTOR
NaryTree::NaryTree(std::vector<int>& datas) {
	this->root = new NodeNaryTree(datas);
}

NaryTree::NaryTree() {
	this->root = NULL;
}

NaryTree::~NaryTree() {
	if(this->isNotEmpty()) {
		delete this->root;
	}
}


// METODOS MODIFICADORES
bool NaryTree::insert(const int& data, const int& node) {
	if(this->isNotEmpty()) {
		return this->root->insert(data, node);
	}
	return false;
}


// METODOS DE ACCESO
bool NaryTree::isEmpty() const {
	return this->root == NULL;
}

bool NaryTree::isNotEmpty() const {
	return this->root != NULL;
}

void NaryTree::printAsPNG(const std::string& fileName) {
	std::stringstream str;
	str << "digraph g{\n";
	if(this->root != NULL) {
		int ID = 1;
		str << this->root->printAsPNG(ID);
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

int NaryTree::globalOrder() {
	if(this->isNotEmpty()) {
		return this->root->globalOrder();
	}
}

int NaryTree::height() {
	if(this->isNotEmpty()) {
		return this->root->height() - 1;
	}
}

int NaryTree::weight() {
	if(this->isNotEmpty()) {
		return this->root->weight();
	}
}

int NaryTree::width() {
	if(this->isNotEmpty()) {
		return this->root->width();
	}
}

int NaryTree::antecesorClosest(const int& a, const int& b) {
	if(this->isNotEmpty()) {
		this->root->antecesorClosest(a, b);
	}
}