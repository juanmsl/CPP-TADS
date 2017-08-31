# ifndef __NODE_HUFFMAN_TREE_H__
# define __NODE_HUFFMAN_TREE_H__

# include <string>
# include <stdexcept>

class NodeHuffmanTree {
	protected:
		char character;
		int frequency;
		NodeHuffmanTree* left;
		NodeHuffmanTree* right;
		bool is_Caracter;

	public:
		// CONSTRUCTOR Y DESTRUCTOR
		NodeHuffmanTree(const char& character, const int& frequency, NodeHuffmanTree* left, NodeHuffmanTree* right, const bool& is_Caracter);
		NodeHuffmanTree(NodeHuffmanTree* root);
		~NodeHuffmanTree();

		// METODOS ENCAPSULADORES
		const char& getCharacter() const;
		const int& getFrequency() const;
		const bool& isCaracter() const;

		// METODOS DE ACCESO
		std::string getCodeOf(const char& character);
		const char& decode(std::string& code);
};

# endif