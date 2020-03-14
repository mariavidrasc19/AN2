int findLCA(Node *root, int u, int v) 
{ 
    /* Mark all nodes unvisited.  Note that the size of 
        firstOccurrence is 1 as node values which vary from 
        1 to 9 are used as indexes */
    memset(firstOccurrence, -1, sizeof(int)*(V+1)); 
  
    /* To start filling euler and level arrays from index 0 */
    ind = 0; 
  
    /* Start Euler tour with root node on level 0 */
    eulerTour(root, 0); 
  
    /* construct segment tree on level array */
    int *st = constructST(level, 2*V-1); 
  
    /* If v before u in Euler tour.  For RMQ to work, first 
       parameter 'u' must be smaller than second 'v' */
    if (firstOccurrence[u]>firstOccurrence[v]) 
       std::swap(u, v); 
  
    // Starting and ending indexes of query range 
    int qs = firstOccurrence[u]; 
    int qe = firstOccurrence[v]; 
  
    // query for index of LCA in tour 
    int index = RMQ(st, 2*V-1, qs, qe); 
  
    /* return LCA node */
    return euler[index]; 
} 