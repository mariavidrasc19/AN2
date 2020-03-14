// binary tree
#include <bits/stdc++.h> 
using namespace std; 
  
class node  
{  
    public: 
    int data;  
    node* left, *right;  
};  
  
/* functia de gasire a celui mai mic stramos comun 
intre 2 noduri porneste de la presupunerea ca 
nodurile exista deja*/
node *lca(node* root, int n1, int n2)  
{  
    if (root == NULL) return NULL;  
  
    // If both n1 and n2 are smaller 
    // than root, then LCA lies in left  
    if (root->data > n1 && root->data > n2)  
        return lca(root->left, n1, n2);  
  
    // If both n1 and n2 are greater than  
    // root, then LCA lies in right  
    if (root->data < n1 && root->data < n2)  
        return lca(root->right, n1, n2);  
  
    return root;  
}  
  
/* construieste un nod in arbore */
node* newNode(int data)  
{  
    node* Node = new node(); 
    Node->data = data;  
    Node->left = Node->right = NULL;  
    return(Node);  
}  

int main() {  
    // aici am construit arborele 
    struct node *root        = newNode(20); 
    root->left               = newNode(8); 
    root->right              = newNode(22); 
    root->left->left         = newNode(4); 
    root->left->right        = newNode(12); 
    root->left->right->left  = newNode(10); 
    root->left->right->right = newNode(14); 
  
    int n1 = 10, n2 = 14; 
    struct node *t = lca(root, n1, n2); 
    printf("LCA of %d and %d is %d \n", n1, n2, t->data); 
  
    n1 = 14, n2 = 8; 
    t = lca(root, n1, n2); 
    printf("LCA of %d and %d is %d \n", n1, n2, t->data); 
  
    n1 = 10, n2 = 22; 
    t = lca(root, n1, n2); 
    printf("LCA of %d and %d is %d \n", n1, n2, t->data); 
  
    getchar(); 
    return 0; 
}