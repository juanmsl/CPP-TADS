# ifndef __HUFFMAN_TREE_H__
# define __HUFFMAN_TREE_H__

# include <iostream>
# include <sstream>
# include <iomanip>
# include <fstream>
# include <vector>
# include <utility>
# include <algorithm>
# include <map>
# include <string.h>
# include "NodeHuffmanTree.h"

class HuffmanTree {
	protected:
		typedef std::map<char, std::pair<int, std::string>> Histogram; // MAP OF CHARS WITH THE PAIR (FREQUENCY, CODE)
		Histogram histogram; 
		NodeHuffmanTree* root;

	public:
		/*************************************************************
							CONSTRUCTOR Y DESTRUCTOR
		*************************************************************/
		HuffmanTree();
		~HuffmanTree();

		/*************************************************************
							METODOS DE CLASE
		*************************************************************/
		void encoudeFile(const std::string& input_file, const std::string& output_file);
		void encoudeText(const std::string& text, const std::string& output_file);
		void decodeToFile(const std::string& input_file, const std::string& output_file);
		const std::string decodeToText(const std::string& input_file);

	private:
		/*************************************************************
							METODOS ENCAPSULADORES
		*************************************************************/
		const std::string getCodeOf(const char& character) const;
		void printTable(std::ostream& out);
		/*************************************************************
							METODOS DE CONSTRUCCION DEL ARBOL
		*************************************************************/
		void init();
		void getFrequencies(const int& size, const char *charBuffer);
		void buildTree();
		void getCodes();
		void encoude(const int& size, const char *charBuffer, const std::string& output_file);
		std::string decode(const std::string& input_file);
};

# endif