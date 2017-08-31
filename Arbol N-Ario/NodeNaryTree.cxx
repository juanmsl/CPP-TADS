# include "NodeNaryTree.h"

// CONSTRUCTOR Y DESTRUCTOR
NodeNaryTree::NodeNaryTree(std::vector<int>& datas) {
	int childs = datas[0];
	this->data = datas[1];
	
	datas.erase(datas.begin());
	datas.erase(datas.begin());

	for(int i = 0; i < childs; i++) {
		this->nodes.push_back(new NodeNaryTree(datas));
	}
}

NodeNaryTree::NodeNaryTree(const int& data) {
	this->data = data;
}

NodeNaryTree::~NodeNaryTree() {
	for(int i = 0; i < this->nodes.size(); i++) {
		delete this->nodes[i];
	}
}


// METODOS MODIFICADORES
bool NodeNaryTree::insert(const int& data, const int& node) {
	if(this->data == node) {
		this->nodes.push_back(new NodeNaryTree(data));
		return true;
	}

	bool Inserto = false;
	for(int i = 0; i < this->nodes.size() && !Inserto; i++) {
		Inserto = this->nodes[i]->insert(data, node);
	}

	return Inserto;
}


// METODOS DE ACCESO
const std::string NodeNaryTree::printAsPNG(int& ID) {
	std::stringstream str;

	int MyID = ID;
	str	<< "\"" << MyID <<"\" [label=\""<<this->data<<"\"]" <<"\n";
	
	for(int i = 0; i < this->nodes.size(); i++) {
		ID++;
		str	<< "\"" << ID <<"\" [label=\""<<this->nodes[i]->data<<"\"]" <<"\n";
		str	<< "\"" << MyID <<"\"->\""<< ID << "\"\n";
		str << this->nodes[i]->printAsPNG(ID);
	}

	return str.str();
}

int NodeNaryTree::globalOrder() {
	int orderMayor = this->nodes.size(), order;
	for(int i = 0; i < this->nodes.size(); i++) {
		order = this->nodes[i]->nodes.size();
		if(order > orderMayor) orderMayor = order;
		order = this->nodes[i]->globalOrder();
		if(order > orderMayor) orderMayor = order;
	}
	return orderMayor;
}

int NodeNaryTree::height() {
	int H = 0, h;
	for(int i = 0; i < this->nodes.size(); i++) {
		h = this->nodes[i]->height();
		if(h > H) {
			H = h;
		}
	}
	return H + 1;
}

int NodeNaryTree::weight() {
	int w = 1;
	for(int i = 0; i < this->nodes.size(); i++) {
		w += this->nodes[i]->weight();
	}
	return w;
}

int NodeNaryTree::width() {
	std::queue<NodeNaryTree*> q;
	std::queue<int> n;
	q.push(this);
	n.push(0);
	int ant = 0, MAYOR = 0, M = 0;
	while(!q.empty()) {
		NodeNaryTree* node = q.front();
		int level = n.front();
		q.pop();
		n.pop();

		if(ant < level) {
			ant = level;
			if(M > MAYOR) {
				MAYOR = M;
			}
			M = 0;
		}
		if(level == ant) {
			M++;
		}

		for(int i = 0; i < node->nodes.size(); i++) {
			q.push(node->nodes[i]);
			n.push(level+1);
		}
	}
	if(M > MAYOR) {
		MAYOR = M;
	}
	return MAYOR;
}

int NodeNaryTree::antecesorClosest(const int& a, const int& b) {
	std::vector<int> pathA = findPathOf(a);
	std::vector<int> pathB = findPathOf(b);

	int indice = -1;

	for(int i = 0; i < pathA.size() && i < pathB.size(); i++) {
		if(pathA[i] == pathB[i]) {
			indice = i;
		}
	}

	return pathA[indice];
}

std::vector<int> NodeNaryTree::findPathOf(const int& data) {
	std::vector<int> path;

	if(this->data == data) {
		path.push_back(this->data);
		return path;
	}

	for(int i = 0; i< this->nodes.size(); i++) {
		std::vector<int> p = this->nodes[i]->findPathOf(data);
		if(p.size() != 0) {
			p.insert(p.begin(), this->data);
			return p;
		}
	}

	return path;
}