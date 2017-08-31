# include "HuffmanTree.h"
/*************************************************************

					CONSTRUCTOR Y DESTRUCTOR

*************************************************************/
HuffmanTree::HuffmanTree() {
	this->root = NULL;
}

HuffmanTree::~HuffmanTree() {
	if (this->root != NULL) delete this->root;
}

/*************************************************************

					METODOS DE CLASE

*************************************************************/
void HuffmanTree::encoudeFile(const std::string& input_file, const std::string& output_file) {
	std::ifstream input(input_file.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
	if(input.is_open()) {
		int size = input.tellg();
		char *charBuffer = new char [size];
		input.seekg (0, std::ios::beg);
		input.read (charBuffer, size);
		input.close();

		init();
		getFrequencies(size, charBuffer);
		buildTree();
		getCodes();
		encoude(size, charBuffer, output_file);
		delete [] charBuffer;
	} else {
		throw std::domain_error("\nERROR: Cannot open the input file\n\n");
	}

}

void HuffmanTree::encoudeText(const std::string& text, const std::string& output_file) {
	init();
	getFrequencies(text.length(), text.c_str());
	buildTree();
	getCodes();
	encoude(text.length(), text.c_str(), output_file);
}

void HuffmanTree::decodeToFile(const std::string& input_file, const std::string& output_file) {
	std::ofstream output(output_file.c_str(), std::ios::out|std::ios::binary);
	if(output.is_open()) {
		std::string result = decode(input_file);
		while(result.length() > 0) {
			char c = this->root->decode(result);
			output << c;
		}
		output.close();
	} else {
		throw std::domain_error("\nERROR: Cannot open the output file\n\n");
	}
}

const std::string HuffmanTree::decodeToText(const std::string& input_file) {
	std::stringstream output;
	std::string result = decode(input_file);
	while(result.length() > 0) {
		char c = this->root->decode(result);
		output << c;
	}
	return output.str();
}

/*************************************************************

					METODOS ENCAPSULADORES

*************************************************************/
const std::string HuffmanTree::getCodeOf(const char& character) const {
	Histogram::const_iterator it;
	it = this->histogram.find(character);
	if(it != this->histogram.end()) {
		std::pair<int, std::string> a = it->second;
		return a.second;
	}
}

void HuffmanTree::printTable(std::ostream& out) {
	out<<"\n  Char - Freq -   Code    \n";
	Histogram::iterator it = this->histogram.begin();
	for(; it != this->histogram.end(); it++) {
		out <<" "<<std::setw(5)<<std::left<<(int)it->first<<" - "<<std::setw(4)<<std::left<<it->second.first<<" - "<<std::setw(10)<<std::left<<it->second.second<<"\n";
	}
	out<<"\n";
}

/*************************************************************

					METODOS DE CONSTRUCCION DEL ARBOL

*************************************************************/
void HuffmanTree::init() {
	if (this->root != NULL) delete this->root;
	this->histogram.clear();
}

void HuffmanTree::getFrequencies(const int& size, const char *charBuffer) {
	for(int  i=0; i < size; i++) {
		if(this->histogram.find(charBuffer[i]) == this->histogram.end()){
			this->histogram[charBuffer[i]].first = 1;
		} else {
			this->histogram[charBuffer[i]].first++;
		}
	}
}

bool functionCompare(NodeHuffmanTree *a, NodeHuffmanTree *b) {
	return a->getFrequency() < b->getFrequency();
}

void HuffmanTree::buildTree() {
	std::vector<NodeHuffmanTree*> vectorTree;

	// CREATE THE VECTOR TREE
	Histogram::iterator it = this->histogram.begin();
	for(; it != this->histogram.end(); it++) {
		NodeHuffmanTree *pointer = new NodeHuffmanTree(it->first, it->second.first, NULL, NULL, true);
		vectorTree.push_back(pointer);
	}

	// CREATE THE TREE OVER VECTOR
	while(vectorTree.size() > 1) {
		// SORTING THE VECTOR FOR FREQUENCIES
		std::sort(vectorTree.begin(), vectorTree.end(), functionCompare);
		// COMBINE THE TWO FIRST NODES OF VECTOR
		NodeHuffmanTree *a = vectorTree[0];
		NodeHuffmanTree *b = vectorTree[1];
		vectorTree.erase(vectorTree.begin());
		vectorTree.erase(vectorTree.begin());
		int value = a->getFrequency() + b->getFrequency();
		NodeHuffmanTree *root = new NodeHuffmanTree(0, value, b, a, false);
		vectorTree.push_back(root);
	}

	this->root = vectorTree[0];
}

void HuffmanTree::getCodes() {
	Histogram::iterator it = this->histogram.begin();
	for(; it != this->histogram.end(); it++) {
		it->second.second = this->root->getCodeOf(it->first);
	}
}

void HuffmanTree::encoude(const int& size, const char *charBuffer, const std::string& output_file) {
	std::ofstream output(output_file.c_str(), std::ios::out|std::ios::binary);
	if(output.is_open()) {
		int histogramSize = histogram.size();
		output.write((char*)&histogramSize, sizeof(histogramSize));

		// SAVING THE HISTOGRAM
		Histogram::iterator it = this->histogram.begin();
		for(; it != this->histogram.end(); it++) {
			output.write((char*)&it->first, sizeof(it->first));
			output.write((char*)&it->second.first, sizeof(it->second.first));
		}

		// GETTING THE BINARY CODE
		std::string binary = "";
		for(int  i = 0; i < size; i++) {
			binary += getCodeOf(charBuffer[i]);
		}

		// CONVERT THE BINARY CODE TO 
		int diff = 8 - binary.size() % 8, tam = (binary.size() + diff) / 8;
		char *result = new char[tam];
		for(int i = 0, j = 0; i < binary.size(); i+=8, j++) {
			char value = 0;
			for(int j = 0; j < 8; j++) {
				if(binary[i+j] == '1') {
					value |= (1 << j);
				}
			}
			result[j] = value;
		}

		int resultSize = sizeof(result) * tam;
		output.write((char*)&diff, sizeof(diff));
		output.write((char*)&tam, sizeof(tam));
		output.write(result, tam);
		output.close();
		delete []result;
	} else {
		throw std::domain_error("\nERROR: Cannot open the output file\n\n");
	}
}

std::string HuffmanTree::decode(const std::string& input_file) {
	std::ifstream input(input_file.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
	if(input.is_open()) {
		int fileSize = input.tellg();
		input.seekg (0, std::ios::beg);
		init();
		int histogramSize;
		input.read((char*)&histogramSize, sizeof(histogramSize));
		for(int i = 0; i < histogramSize; i++) {
			char character;
			int frequency;
			input.read((char*)&character, sizeof(character));
			input.read((char*)&frequency, sizeof(frequency));
			histogram[character].first = frequency;
		}
		buildTree();
		getCodes();

		int size, diff;
		input.read((char*)&diff, sizeof(diff));
		input.read((char*)&size, sizeof(size));
		
		char *codeBuffer = new char[size];
		input.read(codeBuffer, size);
		input.close();

		std::string result = "", code(codeBuffer);
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < 8; j++) {
				if(codeBuffer[i] & (1 << j)) {
					result += "1";
				} else {
					result += "0";
				}
			}
		}
		result = std::string(result, 0, result.size() - diff);

		delete [] codeBuffer;
		return result;
	} else {
		throw std::domain_error("\nERROR: Cannot open the input file\n\n");
	}
}