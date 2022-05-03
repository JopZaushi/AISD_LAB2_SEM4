#pragma once
#include <iostream>
#include "String.h"
#include "List.h"
using namespace std;

template <typename T1, typename T2>
class HuffmanAlgorithm {
private:
	class node {
	public:
		T1 key;
		T2 value;
		node* left = NULL, * right = NULL, * parent = NULL;
		node* next = NULL;//pointer to the next valueent
		node* next_clear = NULL;
	};
	
public:
	size_t size;
	node* tail_clear;
	node* head_clear;
	node* tail;
	node* head;//pointer to the begin
	node* root;//pointer to the begin
	String text;
	String codes;
	String encoded_text;
	String decoded_text;
	float volume_before = 0;
	float volume_after = 0;

	//Constructor without parameter
	HuffmanAlgorithm() {
		tail_clear = NULL;
		head_clear = NULL;
		root = NULL;
		tail = NULL;
		size = 0;
	}
	//Destructor 
	~HuffmanAlgorithm() {
		clear();
	}
	//From the entered string, the number of characters is counted and written to the List
	List<char, int> string_conversion() {
		cin >> text;
		int length_text = 0;
		List<char, int> list;
		List<char, int> table;
		while (length_text != text.length) {
			list.push_back(text[length_text], 1);
			length_text++;
		}
		while (length_text != 0) {
			int numb_simbol = 0;
			char simbol = list.at(length_text - 1)->key;
			for (int number = 0; number < length_text; number++) {
				if (simbol == list.at(number)->key) {
					numb_simbol++;
				}
			}
			for (int number = 0; number < length_text; number++) {
				if (simbol == list.at(number)->key) {
					list.remove(number);
					number--;
					length_text--;
				}
			}
			table.push_back(simbol, numb_simbol);

		}
		table.sorting();

		return table;
	}
	//Huffman coding
	void tree_huffman_coding(){
		List<char,int> list = string_conversion();
		int index = 0;
		//Adding Elements to the Huffman Structure
		while (list.get_size() != index) {
			node* current = new node;
			if (head == NULL) {
				current->value = list.at(index)->value;
				current->key = list.at(index)->key;
				head = current;
				tail = head;
				size++;
				index++;
			}
			else {
				current->value = list.at(index)->value;
				current->key = list.at(index)->key;
				tail->next = current;
				tail = current;
				size++;
				index++;
			}
		}
		cout << endl;
		//Tree creation
		if (list.size == 0) {
			throw out_of_range("No more valueents");
		}
		else {
			while (list.size != 1) {
				node* current = new node;
				if (list.at(0)->key != '\0') {
					current->left = new node;
					current->left = at(0);
					current->left->parent = current;
					new_node(current->left);
				}
				else {
					current->left = at(0);
					current->left->parent = current;
					new_node(current->left);
				}
				if (list.at(1)->key != '\0') {
					current->right = new node;
					current->right = at(1);
					current->right->parent = current;
					new_node(current->right);
				}
				else {
					current->right = at(1);
					current->right->parent = current;
					new_node(current->right);
				}
				current->value = list.at(0)->value + list.at(1)->value;
				
				if (list.size >= 3) {
					push_front(current);
					current->next = at(3);
					current->left->next = NULL;
					current->right->next = NULL;
					sorting();
				}
				list.pop_front();
				list.pop_front();
				list.push_front('\0', current->value);
				list.sorting();
				root = current;
			}
		
		}
		volume_before = root->value * 8;
		//size--;
		table();
	}
	//Huffman decoding
	void tree_huffman_decoding() {
		int index = 0;
		node* current = root;
		//The encoded string is read and iterates through the tree
		while (index != encoded_text.length) {
			if (current->left != NULL) {
				if (encoded_text[index] == '0') {
					current = current->left;
					index++;
				}
				else {
					current = current->right;
					index++;
				}
			}
			if (current->left == NULL) {
				decoded_text = decoded_text + current->key;
				current = root;
			}
			
		}
		
		cout << endl << "Decoded string:" << endl << decoded_text;
	}
	//Table with all data
	void table() {
		node* current = root;
		String code_left; char zero = '0', one = '1';
		List<char, int> table_codes;
		int number = 0;
		char space = ' ';
		codes = codes + space;
		//Table creation
		while (current->left != NULL) {
			code_left = code_left + zero;
			number++;
			current = current->left;
			if (current->left == NULL) {
				cout << "Char: " << current->key << " " << "Frequency: " << current->value << " " << "Code: " << code_left << endl;
				table_codes.push_back(current->key, current->value);
				codes = codes + code_left;
				codes = codes + space;
				volume_after = volume_after + current->value * code_left.length;
				current = current->parent->right;
				code_left[number - 1] = one;
				if (current->left == NULL) {
					cout << "Char: " << current->key << " " << "Frequency: " << current->value << " " << "Code: " << code_left << endl;
					table_codes.push_back(current->key, current->value);
					codes = codes + code_left;
					codes = codes + space;
					volume_after = volume_after + current->value * code_left.length;
					if (current->parent->parent->right != NULL && current->parent != current->parent->parent->right && current->parent->parent != root) {
						current = current->parent->parent->right;
						code_left.pop_last_simv();
						code_left.pop_last_simv();
						code_left = code_left + one;
						number--;
					}
					else {
						current = root;
						number = 0;
						break;
					}
				}
			}
		}
		String code_right;
		code_right = code_right + one;
		number = 1;
		current = current->right;
		while (current->left != NULL) {
			code_right = code_right + zero;
			number++;
			current = current->left;
			if (current->left == NULL) {
				cout << "Char: " << current->key << " " << "Frequency: " << current->value << " " << "Code: " << code_right << endl;
				table_codes.push_back(current->key, current->value);
				codes = codes + code_right;
				codes = codes + space;
				volume_after = volume_after + current->value * code_right.length;
				current = current->parent->right;
				code_right[number - 1] = one;
				if (current->left == NULL) {
					cout << "Char: " << current->key << " " << "Frequency: " << current->value << " " << "Code: " << code_right << endl;
					table_codes.push_back(current->key, current->value);
					codes = codes + code_right;
					codes = codes + space;
					volume_after = volume_after + current->value * code_right.length;
					if (current->parent->parent->right != NULL && current->parent != current->parent->parent->right) {
						current = current->parent->parent->right;
						code_right[number - 1] = one;
						code_right.pop_last_simv();
						number--;
					}
					else {
						current = root;
						number = 0;
						break;
					}
				}
			}
		}

		//Creating an Encoded Initial String
		float coefficient = volume_before / volume_after;
		cout << endl;
		cout << "The amount of memory of the original string: " << volume_before << endl;
		cout << "The amount of memory of the encoded string: " << volume_after << endl;
		cout << "Compression ratio: " << coefficient << endl;
		cout << endl;
		for (int i = 0; i < text.length; i++) {
			for (int j = 0; j < table_codes.size; j++) {
				if (text[i] == table_codes.at(j)->key) {
					int num_space = 0;
					int index = 0;
					while (num_space != j + 1) {
						if (codes[index] == space) {
							num_space++;
						}
						index++;
					}
					
					while (codes[index] != space) {
						encoded_text = encoded_text + codes[index];
						index++;
					}
				}
			}
		}
		cout << "Encoded string:" << endl << encoded_text;
	}
	//Function for clear
	void new_node(node* current) {
		if (head_clear == NULL) {
			head_clear = current;
			tail_clear = head_clear;
		}
		else {
			tail_clear->next_clear = current;
			tail_clear = current;
		}
	}
	//Destructor
	void clear() {
		node* current = head_clear;
		while (head_clear != NULL) {
			current = head_clear;
			head_clear = head_clear->next_clear;
			delete current;
			size--;
		}
		tail_clear = head_clear;
	}
	//////////////////////////
	//List Methods
	
	//Inserting an item at the beginning of a list
	void push_front(node* value) {
		node* current = new node;
		if (head == NULL) {
			current = value;
			//current = key;
			head = current;
			tail = head;
			size++;
		}
		else {
			current = value;
			current->next = head;
			//current->key = key;
			tail = head;
			head = current;
			size++;
		}
	}

	void sorting() {
		node* number_current1, * extra_current1, * number_current2, * extra_head = NULL;

		for (node* number = head; number != NULL; ) {
			number_current1 = number;
			number = number->next;
			extra_current1 = extra_head;
			for (number_current2 = NULL; (extra_current1 != NULL) && (number_current1->value > extra_current1->value); ) {
				number_current2 = extra_current1;
				extra_current1 = extra_current1->next;
			}
			//всё норм в сортировке
			if (number_current2 == NULL) {
				number_current1->next = extra_head;
				extra_head = number_current1;
			}
			else {
				number_current1->next = extra_current1;
				number_current2->next = number_current1;
			}
		}
		if (extra_head != NULL)
			head = extra_head;
	}

	//Retrieving an valueent by index
	node* at(size_t index) {
		if (isEmpty() == true) {
			throw out_of_range("Out of range");
		}
		else {
			if (index > get_size() - 1) {//Checking an exception
				throw out_of_range("Out of range");
			}
			else {
				node* current = head;
				for (int i = 0; i < index; i++) {
					current = current->next;
				}
				return current;
			}
		}
	}

	//Getting the size of the list
	size_t get_size() {
		size_t size_list = 0;
		node* current = head;
		while (current != NULL) {
			current = current->next;
			size_list++;
		}
		return size_list;
	}

	//Checking for an empty list
	bool isEmpty() {
		bool empty = false;
		if (head == NULL) {
			empty = true;
		}
		return empty;
	}
};
