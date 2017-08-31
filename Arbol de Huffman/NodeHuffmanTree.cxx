# include "NodeHuffmanTree.h"

/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/
NodeHuffmanTree::NodeHuffmanTree(const char& character, const int& frequency, NodeHuffmanTree* left, NodeHuffmanTree* right, const bool& is_Caracter) {
	this->character = character;
	this->frequency = frequency;
	this->left = left;
	this->right = right;
	this->is_Caracter = is_Caracter;
}

NodeHuffmanTree::NodeHuffmanTree(NodeHuffmanTree* root) {
	this->character = root->character;
	this->frequency = root->frequency;
	this->left = root->left;
	this->right = root->right;
	this->is_Caracter = root->is_Caracter;
	root->left = NULL;
	root->right = NULL;
}

NodeHuffmanTree::~NodeHuffmanTree() {
	if(this->left != NULL) {
		delete this->left;
	}
	if(this->right != NULL) {
		delete this->right;
	}
}

/*************************************************************

					METODOS ENCAPSULADORES

*************************************************************/
const char& NodeHuffmanTree::getCharacter() const {
	return this->character;
}

const int& NodeHuffmanTree::getFrequency() const {
	return this->frequency;
}

const bool& NodeHuffmanTree::isCaracter() const {
	return this->is_Caracter;
}

/*************************************************************

					METODOS DE ACCESO

*************************************************************/
std::string NodeHuffmanTree::getCodeOf(const char& character) {
	std::string res = "";
	if(this->left->isCaracter()) {
		if(this->left->character == character) return "0";
	} else {
		res = this->left->getCodeOf(character);
		if(res != "") return "0" + res;
	}

	if(this->right->isCaracter()) {
		if(this->right->character == character) return "1";
		else return "";
	} else {
		res = this->right->getCodeOf(character);
		if(res != "") return "1" + res;
		else return res;
	}
}

const char& NodeHuffmanTree::decode(std::string& code) {
	if(code.length() >= 0) {
		if(this->isCaracter()) {
			return this->character;
		} else if(code.length() > 0) {
			char c = code[0];
			code.erase(0, 1);

			if(c == '0') {
				return this->left->decode(code);
			} else if(c == '1') {
				return this->right->decode(code);
			} else {
				throw std::logic_error(std::string(std::string("\nERROR: Binary exprecion malformed. [") + std::to_string((int)c) + std::string("]\n\n")).c_str());
			}
		} else {
			throw std::logic_error("\nERROR: Missing binary tokens.\n\n");
		}
	}
}