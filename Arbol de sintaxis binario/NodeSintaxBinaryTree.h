# ifndef __NODE_SINTAX_BINARY_TREE_H__
# define __NODE_SINTAX_BINARY_TREE_H__

# include <iostream>
# include <string>
# include <vector>
# include <queue>
# include <stdexcept>

std::string ADD = "+";
std::string MINUS = "-";
std::string MULTIPLY = "*";
std::string DIVIDED = "/";
std::string EXPONENTIAL = "^";

class NodeSintaxBinaryTree {
	protected:
		std::string token;
		NodeSintaxBinaryTree* left;
		NodeSintaxBinaryTree* right;
		
	public:
		// CONSTRUCTOR Y DESTRUCTOR
		NodeSintaxBinaryTree(std::queue<std::string>& tokens);
		virtual ~NodeSintaxBinaryTree();
		
		// METODOS ENCAPSULADORES
		std::string& getToken();
		void setToken(const std::string& token);
		NodeSintaxBinaryTree* getLeft();
		void setLeft(NodeSintaxBinaryTree* left);
		NodeSintaxBinaryTree* getRight();
		void setRight(NodeSintaxBinaryTree* right);
		void getPostOrder(std::vector<std::string>& vector);
		void getPreOrder(std::vector<std::string>& vector);
		void getInOrder(std::vector<std::string>& vector);

		// METODOS MODIFICADORES
		double evaluate();
		bool verify();
		double reduce();

		// METODOS DE ACCESO
		void printPreOrder(std::ostream& out) const;
		void printPostOrder(std::ostream& out) const;
		void printInOrder(std::ostream& out) const;

		// METODOS DE APOYO
		bool isNumber(const std::string& line);
		bool isOperator(const std::string& line);
};

# include "NodeSintaxBinaryTree.hxx"

# endif
