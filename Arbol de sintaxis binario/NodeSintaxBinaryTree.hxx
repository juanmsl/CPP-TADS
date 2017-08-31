# include "NodeSintaxBinaryTree.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/

NodeSintaxBinaryTree::NodeSintaxBinaryTree(std::queue<std::string>& tokens) {
	this->left = NULL;
	this->right = NULL;
	this->token = "";

	if(tokens.empty())
		throw std::logic_error("ERROR: Build - Malformed formula");

	std::string tok = tokens.front();
	tokens.pop();

	if(isOperator(tok)) {
		this->left = new NodeSintaxBinaryTree(tokens);
		this->right = new NodeSintaxBinaryTree(tokens);
	}/* else if(!isNumber(tok)) {
		throw std::domain_error("ERROR: Build - Invalid token '"+tok+"'");
	}*/

	this->token = tok;
}

NodeSintaxBinaryTree::~NodeSintaxBinaryTree() {
	if(this->left != NULL){
		delete this->left;
	}
	if(this->right != NULL){
		delete this->right;
	}
}

/*************************************************************

					METODOS ENCAPSULADORES

*************************************************************/

std::string& NodeSintaxBinaryTree::getToken() {
	return this->token;
}

void NodeSintaxBinaryTree::setToken(const std::string& token) {
	this->token = token;
}

NodeSintaxBinaryTree* NodeSintaxBinaryTree::getLeft() {
	return this->left;
}

void NodeSintaxBinaryTree::setLeft(NodeSintaxBinaryTree* left) {
	this->left = left;
}

NodeSintaxBinaryTree* NodeSintaxBinaryTree::getRight() {
	return this->right;
}

void NodeSintaxBinaryTree::setRight(NodeSintaxBinaryTree* right) {
	this->right = right;
}

void NodeSintaxBinaryTree::getPostOrder(std::vector<std::string>& vector) {
	if(this->left != NULL){
		this->left->getPostOrder(vector);
	}
	if(this->right != NULL){
		this->right->getPostOrder(vector);
	}
	vector.push_back(this->token);
}

void NodeSintaxBinaryTree::getPreOrder(std::vector<std::string>& vector) {
	vector.push_back(this->token);
	if(this->left != NULL){
		this->left->getPreOrder(vector);
	}
	if(this->right != NULL){
		this->right->getPreOrder(vector);
	}
}

void NodeSintaxBinaryTree::getInOrder(std::vector<std::string>& vector) {
	if(this->left != NULL){
		this->left->getInOrder(vector);
	}
	vector.push_back(this->token);
	if(this->right != NULL){
		this->right->getInOrder(vector);
	}
}

/*************************************************************

					METODOS MODIFICADORES

*************************************************************/

double NodeSintaxBinaryTree::evaluate() {
	if(isOperator(this->token)) {
		double v1 = (this->left != NULL) ? this->left->evaluate() : 0;
		double v2 = (this->right != NULL) ? this->right->evaluate() : 0;
		if(this->token == ADD) return v1 + v2;
		else if(this->token == MINUS) return v1 - v2;
		else if(this->token == MULTIPLY) return v1 * v2;
		else if(this->token == DIVIDED) 
			if(v2 != 0) return v1 / v2;
			else throw std::domain_error("ERROR: Evaluate - Division by zero");
	} else if(isNumber(this->token)) {
		return double(std::strtod(this->token.c_str(), NULL));
	}
}

double NodeSintaxBinaryTree::reduce() {
	double v1, v2;

	// EVALUANDO LA IZQUIERDA
	if(this->left != NULL) {
		v1 = this->left->reduce();
		delete this->left;
		this->left = NULL;
	} else if(isNumber(this->token)){
		double value = double(std::strtod(this->token.c_str(), NULL));
		return value;
	} else {
		throw "ERROR: Exprecion mal formada (falta un valor izquierdo a operar)";
	}

	// EVALUANDO LA DERECHA
	if(this->right != NULL) {
		v2 = this->right->reduce();
		delete this->right;
		this->right = NULL;
	} else if(isNumber(this->token)){
		double value = double(std::strtod(this->token.c_str(), NULL));
		return value;
	} else {
		throw "ERROR: Exprecion mal formada (falta un valor derecho a operar)";
	}

	// EVALUANDO LA OPERACION CON LAS EVALUACIONES PREVIAS
	if(isOperator(this->token)) {
		if(this->token == "/" && v2 == 0) throw "ERROR: Divicion por 0, indeterminado";
		switch(this->token[0]) {
			case '+': 
				this->token = std::to_string(v1 + v2);
				return v1 + v2;
				break;
			case '-': 
				this->token = std::to_string(v1 - v2);
				return v1 - v2;
				break;
			case '*': 
				this->token = std::to_string(v1 * v2);
				return v1 * v2;
				break;
			case '/': 
				this->token = std::to_string(v1 / v2);
				return v1 / v2;
				break;
		}
	} else {
		exit(-1);
	}
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/

void NodeSintaxBinaryTree::printPreOrder(std::ostream& out) const {
	out<<"["<<this->token<<"] ";
	if(this->left != NULL){
		this->left->printPreOrder(out);
	}
	if(this->right != NULL){
		this->right->printPreOrder(out);
	}
}

void NodeSintaxBinaryTree::printPostOrder(std::ostream& out) const {
	if(this->left != NULL){
		this->left->printPostOrder(out);
	}
	if(this->right != NULL){
		this->right->printPostOrder(out);
	}
	out<<"["<<this->token<<"] ";
}

void NodeSintaxBinaryTree::printInOrder(std::ostream& out) const {
	if(this->left != NULL || this->right != NULL){
		out<<"(";
		if(this->left != NULL){
			this->left->printInOrder(out);
		}
		out<<" "<<this->token<<" ";
		if(this->right != NULL){
			this->right->printInOrder(out);
		}
		out<<")";
	} else {
		out<<this->token;
	}
}

/*************************************************************

					METODOS DE APOYO

*************************************************************/

bool NodeSintaxBinaryTree::isNumber(const std::string& line) {
	int m = (line[0] == MINUS[0] || line[0] == ADD[0])?1:0, cont = 0;
	if(line.length() == 1 && (line[0] == MINUS[0] || line[0] == ADD[0] || line[0] == '.')) return false;
	for(int i = m; i<line.length(); i++) {
		if(line[i] == '.' && m < i) cont++;
		else if(line[i] == '.' && m >= i) return false;
		if(cont >= 2) return false;
		if(!isdigit(line[i]) && line[i] != '.') return false;
	}
	return true;
}

bool NodeSintaxBinaryTree::isOperator(const std::string& line) {
	if(line.length() == 1)
		return (line == ADD || line == MINUS || line == MULTIPLY || line == DIVIDED || line == EXPONENTIAL);
	return false;
}