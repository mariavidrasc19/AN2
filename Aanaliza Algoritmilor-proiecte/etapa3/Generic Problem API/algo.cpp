#include "algo.h"
#include <cstdio>
#include <errno.h>
class node  
{  
    public: 
    int data;  
    node* left, *right;  
};  
  
/* functia de gasire a celui mai mic stramos comun 
intre 2 noduri porneste de la presupunerea ca 
nodurile exista deja*/
node *lca_recursive(node* root, int n1, int n2)  
{  
    if (root == NULL) return NULL;  
  
    // Dacă atât n1 cât și n2 sunt mai mari decât
    // rădăcină, atunci LCA se află în dreapta  
    if (root->data < n1 && root->data < n2)  
        return lca_recursive(root->right, n1, n2);  
  
    // Dacă ambele n1 și n2 sunt mai mici
    // decât rădăcină, atunci LCA se află în stânga
    if (root->data > n1 && root->data > n2)  
        return lca_recursive(root->left, n1, n2);  
  
    return root;  
}  
  
/* construieste un nod in arbore */
node* newNode(int data) {  
    node* Node = new node(); 
    Node->data = data;  
    Node->left = Node->right = NULL;  
    return(Node);  
}

// cauta un nod in arbore si il returneaza
node * search(node* root, int val) {
	if (root->data == val) {
		return root;
	} else if (val > root->data){
		// se apeleaza recursiv in nodul din dreapta
		node * nod = search(root->right, val);
		return nod;
	} else if (val < root->data){
		// se apeleaza recursiv in nodul din stanga
		node * nod = search(root->left, val);
		return nod;
	}
	return NULL;
} 

std::vector<int> lca(const std::vector<std::vector<int>>& input, const std::vector< std::pair<int, int> >& queries) {
    // TODO
	// se ia mai intai nodul root care este primul nod citit in input
	Node* root = newNode(input[0][0]);
	// se pune al doilea rand in arbore
	if (input[0][1] > root->data) {
		root->right = newNode(input[0][1]);
	} else {
		root->left = newNode(input[0][1]);
	}
	for (unsigned int i = 1; i < input.size(); ++i) {
		// se apeleaza functia search() pentru a cauta primul nod din pair si
		// a-l pune pe cel de-al doilea in arbore
		node* nod = search(root, input[i][0]);
		if (nod->data > input[i][1]) {
			nod->left = newNode(input[i][1]);
		} else if (nod->data < input[i][1]) {
			nod->right = newNode(input[i][1]);
		}
	}
	// se creeaza un vector ce va avea nodurile returnate
	std::vector<int> roots;
	roots.resize(queries.size());
	for (unsigned int i = 0; i < queries.size(); ++i) {
		// se apeleaza findLCA() pentru a gasi LCA pt 2 noduri
		node* nod = lca_recursive(root, queries[i].first, queries[i].second);
		roots[i] = nod->data;
	}
    return roots;
}

