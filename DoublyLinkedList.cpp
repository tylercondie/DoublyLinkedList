#include <iostream>
#include <iomanip>
using namespace std;

// debug function to print the address of ANY type of pointer
ostream& operator<<(ostream& os, void* ptr) {
	os << "0x" << setfill('0') << setw(8) << hex << (long)ptr;
	return os;
}

struct Node {
	char value;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(char value) {
		this->value = value;
	}

	// debug function to print a node
	friend ostream& operator<<(ostream& os, Node& node) {
		os << "  value: " << node.value;
		os << "  left: " << node.left;
		os << "  this: " << &node;
		os << "  right: " << node.right;
		os << endl;
		return os;
	}
};

struct DoublyLinkedList {
	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;

	// debug function to print a list
	friend ostream& operator<<(ostream& os, DoublyLinkedList& list) {
		os << "LIST  size: " << setw(8) << list.size << endl;
		os << "                              head: " << list.head << endl;
		for (Node* cur = list.head; cur != nullptr; cur = cur->right) {
			cout << *cur;
		}
		os << "LIST                          tail: " << list.tail << endl;
		return os;
	}
	// Adds a character to the back of a list
	void append(char v) {

		// Handles if list is empty
		if (isEmpty()) {
			head = new Node(v);
			tail = head;
			size++;
		}

		// Handles if list is not empty
		else {

			// Set left pointer
			Node* temp = new Node(v);
			temp->left = tail;

			// update tails right pointer
			tail->right = temp;

			// update tail
			tail = temp;
			size++;
		}
	}
	// Adds a character to the front of a list
	void prepend(char v) {

		// Handles if list is empty
		if (isEmpty()) {
			head = new Node(v);
			tail = head;
			size++;
		}

		// handles if list is not empty
		else {

			//Set right pointer
			Node* temp = new Node(v);
			temp->right = head;

			//update heads left pointer
			head->left = temp;

			//update head
			head = temp;
			size++;
		}
	}

	void insertAt(char v, int pos) {
		// case empty list:
		if (isEmpty()) append(v);
		else {
			// if pos is out of range, ignore pos, insert v as new tail
			if (pos < 0) {
				prepend(v);
				return;
			}
			if (pos >= size) {
				append(v);
				return;
			}
				
			if (pos == 0) {
				// case non empty and pos is new head
				prepend(v);
				return;
			}
			
			// case non empty and pos is in middle
			Node* temp = head;
			Node* newNode = new Node(v);
			

			for (int i = 0; i != pos; i++) {
				temp = temp->right;
			}
			temp->left->right = newNode;
			newNode->left = temp->left;
			temp->left = newNode;
			newNode->right = temp;
			size++;
				
		}
	}

	// helper function to get Node from pos
	Node* getNodeAt(int pos) {
		if (pos <= size - 1) {
			Node* temp = head;
			for (int i = 0; i < pos; i++) {
				temp = temp->right;
			}
			return temp;
		}
	}

	void remove(int pos) {
		if (pos < 0) return;
		if (pos >= size) return;

		// gets Node at pos and assigns to temp
		Node* temp = getNodeAt(pos);

		// delete the node at pos
		// if pos is the only node in the list
		if (size == 1) {
			head = nullptr;
			tail = head;
		}

		// if pos is the head
		else if (pos == 0) {
			head = head->right;
			head->left = nullptr;
		}

		// if pos is the tail
		else if (pos == size - 1) {
			tail = tail->left;
			tail->right = nullptr;
		}

		// if pos is in the middle
		else {
			temp->left->right = temp->right;
			temp->right->left = temp->left;

		}
		delete temp;
		size--;
		return;


	}

		
	

	int find(char v) {
		// return pos of first node containing value
		Node* temp = head;
		for (int i = 0; i < size; i++) {
			if (temp->value == v) {
				return i;
			}
			else {
				temp = temp->right;
			}
		}
		// -1 if not found
		return -1;
	}

	// return the value at pos
	char get(int pos) {
		if (pos < 0) return -1;
		if (pos >= size) return -1;

		Node* temp = head;
		if (pos == 0) {
			return temp->value;
		}
		else {
			for (int i = 0; i < pos; i++) {
				temp = temp->right;
			}
			return temp->value;
		}

		 
		
	}

	bool isEmpty() {
		// return true on an empty list
		if (size == 0) {
			return true;
		}
		return false;
	}

	void empty() {
		// resets everything to a list with no elements
		while (!isEmpty()) {
			remove(0);
		}
	}
};

int main() {
	// call your own functions calls to test them
	DoublyLinkedList test;
	
	test.append('c');
	test.append('a');
	test.append('b');
	test.append('d');
	cout << test.get(0);
	cout << test.get(1);
	cout << test.get(2);
	cout << test.get(3) << endl;
	system("pause");
	test.insertAt('l', 1);
	cout << test.get(0);
	cout << test.get(1);
	cout << test.get(2) << test.get(3) << test.get(4) << endl;
	system("pause");

	cout << test;
	system("pause");
	


}