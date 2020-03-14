/* Program care face LCA folosind RMQ */
#include "algo.h"
#include <cstdio>
#include <errno.h>
#include<bits/stdc++.h> 
#define V 1024
  
int euler[2*V - 1];
int level[2*V - 1];
int firstOccurrence[V+1];
int ind;
  
// nod pentru arbore binar 
struct Node 
{ 
    int key; 
    struct Node *left, *right; 
}; 
  
// creeaza un nod cu o valoare data ca parametru
Node * newNode(int k) 
{ 
    Node *temp = new Node; 
    temp->key = k; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
  
// logaritm de x in baza 2 
int Log2(int x) 
{ 
    int ans = 0 ; 
    while (x>>=1) ans++; 
    return ans ; 
} 
  
/*  O funcție recursivă pentru a obține valoarea minimă într-un interval dat
     de indici de matrice. Următorii sunt parametrii pentru această funcție.
  
    st -> Pointer pentru segmentul arborelui
    index -> Indexul nodului curent din arborele de segment. Inițial
              0 este trecut deoarece root este întotdeauna la index 0
    ss & se -> Indici de început și de încheiere a segmentului reprezentat
                  după nodul curent, adică st [index]
    qs & qe -> Indici de început și de încheiere a intervalului de interogare*/
int RMQUtil(int index, int ss, int se, int qs, int qe, int *st) 
{ 
    // Dacă segmentul acestui nod este o parte a intervalului dat, 
    // atunci se intoarce la minimul segmentului
    if (qs <= ss && qe >= se) 
        return st[index]; 
  
    // Dacă segmentul acestui nod este în afara intervalului dat 
    else if (se < qs || ss > qe) 
        return -1; 
  
    // Dacă o parte a acestui segment se suprapune cu intervalul dat
    int mid = (ss + se)/2; 
  
    int q1 = RMQUtil(2*index+1, ss, mid, qs, qe, st); 
    int q2 = RMQUtil(2*index+2, mid+1, se, qs, qe, st); 
  
    if (q1==-1) return q2; 
  
    else if (q2==-1) return q1; 
  
    return (level[q1] < level[q2]) ? q1 : q2; 
} 
  
// Întoarce minimum de elemente din intervalul Qs(începutul interogării) la
// qe (sfârșitul interogării). Folosește în principal RMQUtil ()
int RMQ(int *st, int n, int qs, int qe) 
{ 
    // Verificați dacă există valori eronate de intrare 
    if (qs < 0 || qe > n-1 || qs > qe) 
    { 
        printf("Invalid Input"); 
        return -1; 
    } 
  
    return RMQUtil(0, 0, n-1, qs, qe, st); 
} 
  
// O funcție recursivă care construiește arborele de segmente.
// si este indexul nodului curent din arborele segmentului st
void constructSTUtil(int si, int ss, int se, int arr[], int *st) 
{ 
    // Dacă există un element, stocați-l în nodul curent din
    // arborele segmentului și revenirea 
    if (ss == se)st[si] = ss; 
  
    else
    { 
        int mid = (ss + se)/2; 
        constructSTUtil(si*2+1, ss, mid, arr, st); 
        constructSTUtil(si*2+2, mid+1, se, arr, st); 
  
        if (arr[st[2*si+1]] < arr[st[2*si+2]]) 
            st[si] = st[2*si+1]; 
        else
            st[si] = st[2*si+2]; 
    } 
} 
  
/* Funcția de constructie a arborelui. Această funcție apelează constructSTUtil()*/
int *constructST(int arr[], int n) 
{ 
    int x = Log2(n)+1;
    int max_size = 2*(1<<x) - 1;  //  2*pow(2,x) -1 
  
    int *st = new int[max_size]; 
    constructSTUtil(0, 0, n-1, arr, st);
    return st; 
} 
  
// Versiunea recursivă a "Euler tour" din T
void eulerTour(Node *root, int l) 
{ 
    /* dacă nodul trecut există */
    if (root) 
    { 
        euler[ind] = root->key; 
        level[ind] = l;         
        ind++;                  
  
        /* dacă este nevăzut, se marcheaza prima apariție */
        if (firstOccurrence[root->key] == -1) 
            firstOccurrence[root->key] = ind-1; 
  
        /* turul a lăsat subtree dacă există, și remarcă euler
           și vectori de nivel pentru părinte la întoarcere*/
        if (root->left) 
        { 
            eulerTour(root->left, l+1); 
            euler[ind]=root->key; 
            level[ind] = l; 
            ind++; 
        } 
  
        /* dacă există, precum și comentariu
           și tablouri de nivel pentru părinte la întoarcere */
        if (root->right) 
        { 
            eulerTour(root->right, l+1); 
            euler[ind]=root->key; 
            level[ind] = l; 
            ind++; 
        } 
    } 
} 
  
// Returnează LCA a nodurilor n1, n2 (presupunând că sunt
// prezente în copac)
int findLCA(Node *root, int u, int v) 
{ 
    /* Marcheaza toate nodurile nevizitate. Rețineți că dimensiunea de
        firstOcurrence este 1 ca valori ale nodului care variază de la
        1 la 9 sunt utilizate ca indici */
    memset(firstOccurrence, -1, sizeof(int)*(V+1)); 
    ind = 0; 
    eulerTour(root, 0); 
  
    int *st = constructST(level, 2*V-1); 
  
    /* Dacă v înaintea u în turul Euler. Pentru ca RMQ să funcționeze, mai întâi
       parametrul „u” trebuie să fie mai mic decât al doilea „v” */
    if (firstOccurrence[u]>firstOccurrence[v]) 
       std::swap(u, v); 
  
    // Pornirea și sfârșitul indexurilor intervalului de interogare
    int qs = firstOccurrence[u]; 
    int qe = firstOccurrence[v]; 
  
    int index = RMQ(st, 2*V-1, qs, qe); 
  
    /* returneaza nodul LCA */
    return euler[index]; 
} 

// cauta un nod in arbore si il returneaza
Node * search(Node* root, int val) {
	if (root == NULL){
		return NULL;
	}
	if (root->key == val) {
		return root;
	} else {
		Node * nod = search(root->left, val);
		if (nod == NULL) {
			nod = search(root->right, val);
			return nod;
		}
		return nod;
	}
	return NULL;
} 

std::vector<int> lca(const std::vector<std::vector<int>>& input, const std::vector< std::pair<int, int> >& queries) {
    // TODO
    // se ia mai intai nodul root care este primul nod citit in input
	Node* root = newNode(input[0][0]);
	// se pune al doilea rand in arbore
	root->left = newNode(input[0][1]);
	for (unsigned int i = 1; i < input.size(); ++i) {
		// se apeleaza functia search() pentru a cauta primul nod din pair si
		// a-l pune pe cel de-al doilea in arbore
		Node* nod = search(root, input[i][0]);
		if (nod->left == NULL) {
			nod->left = newNode(input[i][1]);
		} else {
			nod->right = newNode(input[i][1]);
		}
	}
	// se creeaza un vector ce va avea nodurile returnate
	std::vector<int> roots;
	roots.resize(queries.size());
	for (unsigned int i = 0; i < queries.size(); ++i) {
		// se apeleaza findLCA() pentru a gasi LCA pt 2 noduri
		int nod = findLCA(root, queries[i].first, queries[i].second);
		roots[i] = nod;
	}
    return roots;
}

