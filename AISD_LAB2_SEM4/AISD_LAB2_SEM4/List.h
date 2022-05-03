#pragma once
#include <iostream>
using namespace std;

template <typename S, typename T>
class List {

public:
	class node {
	public:
		S key = 0;
		T value = 0;
		node* next = NULL;//pointer to the next valueent
	};
	int size;
	node* head;//pointer to the begin
	node* tail;//pointer to the end

	//Constructor without parameter
	List() {
		//Empty list
		head = NULL;
		tail = NULL;
		size = 0;
	}
	//Destructor 
	~List() {
		//Releasing the memory
		node* current = head;
		head = NULL;
		while (head != NULL) {
			if (size == 0) break;
			current = head;
			head = head->next;
			delete current;
		}
		tail = head;
	}

	//Inserting an item at the end of a list
	void push_back(S key, T value) {
		node* current = new node;
		if (head == NULL) {
			current->value = value;
			current->key = key;
			head = current;
			tail = head;
			size++;
		}
		else {
			current->value = value;
			current->key = key;
			tail->next = current;
			tail = current;
			size++;
		}
	}

	//Inserting an item at the beginning of a list
	void push_front(S key, T value) {
		node* current = new node;
		if (head == NULL) {
			current->value = value;
			current->key = key;
			head = current;
			tail = head;
			size++;
		}
		else {
			current->next = head;
			current->value = value;
			current->key = key;
			tail = head;
			head = current;
			size++;
		}
	}

	//Deleting the first valueent
	void pop_front() {
		if (head == NULL) {//Checking an exception
			throw invalid_argument("List is empty");
		}
		else {
			node* current = head;
			head = head->next;
			delete current;
			size--;
			if (head == NULL)
				tail = head;
		}
	}

	//Removing an valueent from the middle of a list
	void remove(size_t index) {
		if (index > get_size() - 1) {//Checking an exception
			throw out_of_range("Out of range");
		}
		else {
			if ((head->next == NULL) || (index == 0)) {
				pop_front();
			}
			else {
				node* current = head;
				node* dopcurrent;
				for (int i = 0; i < index - 1; i++)
					current = current->next;
				dopcurrent = current->next;
				current->next = dopcurrent->next;
				delete dopcurrent;
				size--;
			}
		}
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

	void print() {
		node* current = head;
		while (current != NULL) {
			cout << current->key << " (" << current->value << ") ";
			current = current->next;
		}
		cout << endl;
	}
};