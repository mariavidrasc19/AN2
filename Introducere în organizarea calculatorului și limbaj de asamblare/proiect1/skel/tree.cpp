#include <iostream>
#include <queue>

class Node {
private:
	char data;
	Node* left;
	Node* right;
public:
	Node(char data) {
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
	~Node() { }
	char getData() {
		return this->data;
	}
	Node* getLeft() {
		return this->left;
	}
	void setLeft(Node* temp) {
		this->left = temp;
	}
	Node* getRight() {
		return this->right;
	}
	void setRight(Node* temp) {
		this->right = temp;
	}
};

class Tree {
private:
	Node* root;
public:
	Tree() {
		this->root = NULL;
	}
	~Tree() {
		std::queue<Node*> q;
		q.push(root);
		while(!q.empty()) {
			Node* x = q.front();
			q.pop();
			if (x->getLeft() != NULL) {
				q.push(x->getLeft());
			}
			if (x->getRight() != NULL) {
				q.push(x->getRight());
			}
			delete x;
		}
	}
	Node* getRoot() {
		return this->root;
	}
	Tree* insert(char data) {
		if (root == NULL) {
			root = new Node(data);
			return this;
		}
		Node* temp = new Node(data);
		std::queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			Node* x = q.front();
			q.pop();
			if (x->getLeft() == NULL) {
				x->setLeft(temp);
				return this;
			}
			if (x->getRight() == NULL) {
				x->setRight(temp);
				return this;
			}
			q.push(x->getLeft());
			q.push(x->getRight());
		}
		return this;
	}
	int calc(Node* x) {
		int data = x->getData();
		printf("%c ", data);	
		if (data == '+' || data == '-' || data == '*' || data == '/') {
			Node* left = x->getLeft();
			int a = calc(left);
			Node* right = x->getRight();
			int b = calc(right);
			return getVal(x->getData(), a, b);
		} else {
			return x->getData() - '0';
		}
	}
	int getVal(char symb, int a, int b) {
		switch (symb) {
			case '+':
				return a + b;
			case '-':
				return a - b;
			case '*':
				return a * b;
			case '/':
				return a / b;
			default:
				return 0;
		}
	}
	void print() {
		std::queue<Node*> q;
		q.push(root);
		while(!q.empty()) {
			Node* x = q.front();
			q.pop();
			if (x->getLeft() != NULL) {
				q.push(x->getLeft());
			}
			if (x->getRight() != NULL) {
				q.push(x->getRight());
			}
			std::cout << x->getData() << ' ';
		}
		std::cout << '\n';
	}
};

int main() {
	Tree* t = new Tree();
	t->insert('*')->insert('-')->insert('+')->insert('5')->insert('6')->insert('3')->insert('4');
	t->print();
	std::cout << t->calc(t->getRoot()) << '\n';
	delete t;
	return 0;
}