Maria Vidrasc 324CA
Etapa 2:

LCA(Lowest Common Ancestor):


Arhiva contine fisierele:

* algo.h
* algo.cpp
* algo1.cpp
* tester.cpp
* folder in: testele in
* folder out: testele out
* Makefile :
-rulati: make + <parametrii pentru algoritmi>
    Parametrii:
    --BST: build_algo1
    --RMQ: build_algo2
-apoi rulati: ./tester

    RMQ(Range Minimum Query):

    Range Minimum Query (Interogarea minima a intervalului) este utilizat
pe tablouri pentru a găsi poziția unui element cu valoarea minimă între 
doi indici specificați. 
    Timpul de preprocesare al unui segment de arbore este O (n), pe când 
timpul pentru interogarea minimă a intervalului este O (Logn). 
Spațiul suplimentar necesar este O (n) pentru a stoca arborele de segmente.
    
    Reducand LCA la RMQ:
    Ideea rezolvarii RMQ este de a traversa arborele pornind de la rădăcină 
printr-un tur Euler (traversarea drumului intre doua noduri fara a ridica 
creionul de pe foaie), care este de tip DFS cu caracteristici de traversare preordine.
    Să ne imaginam: nodul nostru este nodul la cel mai mic nivel și singurul 
nod la acest nivel dintre toate nodurile care apar între apariții 
consecutive (oricare) din u și v în turul Euler din T.

    Pentru implementarea RMQ avem nevoie de trei tablouri:
1. Nodurile vizitate în ordine in turul Euler din arbore.
2. Nivelul fiecărui nod vizitat în turul Euler din arbore.
3. Indexul primei apariții a unui nod în turul Euler din arbore

    Algoritm de implementare:
    Facem un tur Euler pe arbore și completam tablourile de noduri vizitate, 
nivele și prima apariție.
    Utilizând primul tablou de apariție, obținem indicii corespunzători celor
două noduri care vor fi colțurile intervalului din tabloul de nivel care este 
alimentat cu algoritmul RMQ pentru valoarea minimă.
Odată ce algoritmul returnează indicele nivelului minim din interval, îl utilizăm 
pentru a determina LCA folosind tabloul traversat DFS.

    Observatie:
Presupunem că nodurile interogate sunt prezente în arbore.
De asemenea, am presupus că dacă în arbore există noduri V, tastele (sau datele) 
acestor noduri sunt cuprinse între 1 și V.

    Complexitatea in timp:
Turul Euler: numărul de noduri este V. Pentru un copac, E = V-1. Turul Euler (DFS) 
va lua O (V + E) care este O (2 * V) care poate fi scris ca O (V).
Segment Construcția arborelui: O (n) unde n = V + E = 2 * V - 1.
Interval Interogare minimă: O (jurnal (n));

    În general, această metodă durează O (n) timp pentru preprocesare, dar durează O (Log n) 
timp pentru interogare. Prin urmare, poate fi util atunci când avem un singur arbore pe 
care dorim să efectuăm un număr mare de interogări LCA (Rețineți că LCA este util pentru 
a găsi cea mai scurtă cale între două noduri din Arbore binar).

    Complexitate spatiala:
Matricea turistică Euler: O(n) unde n = 2 * V - 1
Matrice niveluri noduri: O(n)
Matricea de întâmplare: O(V)
Arborele segmentului: O(n)
În general: O(n)

    O altă observație este că elementele adiacente din tabloul de nivel diferă cu 1. 
    Aceasta poate fi folosită pentru a converti o problemă RMQ într-o problemă LCA.


    Binary Search:

    Dacă ni se oferă un BST în care fiecare nod are indicatorul părinte, atunci LCA 
poate fi determinat cu ușurință parcurgând cu indicatorul părinte și prin tipărirea 
primului nod intersectant.

    Putem rezolva această problemă folosind proprietăți BST. Putem traversa recursiv 
BST de la root. Ideea principală a soluției este că, în timp ce parcurgem de sus în jos, 
primul nod n pe care îl întâlnim cu valoare între n1 și n2, adică n1 mai mic decat n2 sau la fel 
ca unul dintre n1 sau n2, este LCA al n1 și n2 (presupunând că n1 < n2). Așadar, traversam 
BST în mod recursiv, dacă valoarea nodului este mai mare decât n1 și n2, atunci LCA-ul 
nostru se află în partea stângă a nodului, dacă este mai mic decât atât n1 cât și n2, 
LCA se află în partea dreaptă. În caz contrar, rădăcina este LCA (presupunând că atât 
n1 cât și n2 sunt prezente în BST).

Complexitatea spatiala:
In general: O(n)

