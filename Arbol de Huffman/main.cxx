# include <iostream>
# include "HuffmanTree.h"

int main(int argv, char *args[]) {

	try {
		HuffmanTree h;
		h.encoudeFile("Prueba_1.txt", "PruebaBinario_1");
		h.decodeToFile("PruebaBinario_1", "PruebaSalida_1.txt");

		h.encoudeFile("Prueba_2.txt", "PruebaBinario_2");
		h.decodeToFile("PruebaBinario_2", "PruebaSalida_2.txt");
	} catch(std::exception& me) {
		std::cerr<<me.what();
	}
	

	return 0;
}