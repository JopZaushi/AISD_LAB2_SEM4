#include <iostream>
using namespace std;
#include "HuffmanAlgorithm.h"

int main() {
	HuffmanAlgorithm<char, int> a;
	a.tree_huffman_coding();
	cout << endl;
	a.tree_huffman_decoding();
	cout << endl;

	return 0;
}