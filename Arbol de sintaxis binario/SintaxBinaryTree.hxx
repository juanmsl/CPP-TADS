# include "SintaxBinaryTree.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/

SintaxBinaryTree::SintaxBinaryTree() {
	this->root = NULL;
}

SintaxBinaryTree::~SintaxBinaryTree() {
	if(this->isNotEmpty()) {
		delete this->root;
	}
}

/*************************************************************

					METODOS ENCAPSULADORES

*************************************************************/

std::vector<std::string> SintaxBinaryTree::getPostOrder() {
	std::vector<std::string> vector;
	if(this->isNotEmpty()) {
		this->root->getPostOrder(vector);
	}
	return vector;
}

std::vector<std::string> SintaxBinaryTree::getPreOrder() {
	std::vector<std::string> vector;
	if(this->isNotEmpty()) {
		this->root->getPreOrder(vector);
	}
	return vector;
}

std::vector<std::string> SintaxBinaryTree::getInOrder() {
	std::vector<std::string> vector;
	if(this->isNotEmpty()) {
		this->root->getInOrder(vector);
	}
	return vector;
}

/*************************************************************

					METODOS MODIFICADORES

*************************************************************/

bool SintaxBinaryTree::build(const std::string& data) {

	clear();

	std::stringstream ss(data);
	std::string s;
	std::queue<std::string> opp;
    while (getline(ss, s, ' ')) {
        opp.push(s);
    }

	this->root = new NodeSintaxBinaryTree(opp);
  
	if(!opp.empty())
		throw std::logic_error("ERROR: Build - Extra tokens");

    return true;
}

double SintaxBinaryTree::evaluate() {
	if(this->isNotEmpty()) return this->root->evaluate();
}

double SintaxBinaryTree::reduce() {
	if(this->isNotEmpty()) return this->root->reduce();
}

void SintaxBinaryTree::clear() {
	delete this->root;
	this->root = NULL;
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/

bool SintaxBinaryTree::isEmpty()  const {
	return this->root == NULL;
}

bool SintaxBinaryTree::isNotEmpty()  const {
	return this->root != NULL;
}

void SintaxBinaryTree::printPreOrder(std::ostream& out) const {
	if(this->isNotEmpty()) {
		this->root->printPreOrder(out);
	}
}

void SintaxBinaryTree::printPostOrder(std::ostream& out) const {
	if(this->isNotEmpty()) {
		this->root->printPostOrder(out);
	}
}

void SintaxBinaryTree::printInOrder(std::ostream& out) const {
	if(this->isNotEmpty()) {
		this->root->printInOrder(out);
	}
}

void SintaxBinaryTree::printLevels(std::ostream& out) {
	if(this->isNotEmpty()) {
		std::queue<NodeSintaxBinaryTree*> queue;
		std::queue<int> levels;
		levels.push(0);
		queue.push(this->root);
		int ant = 0;
		out<<"Nivel 0: ";
		while(!queue.empty()) {
			NodeSintaxBinaryTree* sub = queue.front();
			int level = levels.front();
			levels.pop();
			queue.pop();
			if(level > ant) {
				out<<"\nNivel "<<level<<": ";
				ant = level;
			}
			out<<"["<<sub->getToken()<<"] ";
			if(sub->getLeft() != NULL) {
				queue.push(sub->getLeft());
				levels.push(level+1);
			}
			if(sub->getRight() != NULL) {
				queue.push(sub->getRight());
				levels.push(level+1);
			}
		}
	} else {
		out<<"Arbol esta vacio";
	}
}