#include <bits/stdc++.h>
using namespace std;

const int kNmax = 2e5 + 10;

// Strctura de date descrisa aici https://infoarena.ro/problema/disjoint.
class DisjointSet {
 private:
    vector<int> parent, size;

 public:
    // Se initializeaza n paduri
    DisjointSet(int n)
    : parent(n + 1),
    size(n + 1) {
        for (int i = 1; i <= n; ++i) {
            // fiecare padure contine un nod initial
            parent[i] = i;
            size[i] = 1;
        }
    }

    // returneaza radacina arborelui din care face parte node
    int find_root(int node) {
        if (node == parent[node]) {
            return node;
        }
        return parent[node] = find_root(parent[node]);
    }

    // reuneste arborii lui root1 si root2 intr-un singur arbore
    void merge_forests(int root1, int root2) {
        if (size[root1] <= size[root2]) {
            size[root2] += size[root1];
            parent[root1] = root2;
        } else {
            size[root1] += size[root2];
            parent[root2] = root1;
        }
    }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    int m;

    typedef tuple<int, int, int> edge;
    vector<edge> edges;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            edges.push_back({x, y, w});
        }
        fin.close();
    }

    int get_result() {

        DisjointSet disjoint(n);
        int result = 0;
        sort(edges.begin(), edges.end(), [](tuple<int, int, int>& t1, tuple<int, int, int>& t2) {return get<2>(t1) < get<2>(t2);});

        for (auto &it : edges) {
            tuple<int, int, int> t = it;
            int first = get<0>(t);
            int second = get<1>(t);
            int cost = get<2>(t);           
            int x =disjoint.find_root(first);
            int y = disjoint.find_root(second);

            if(x != y){
                result = result + cost;
                disjoint.merge_forests(x, y);     
            }
        }
        
        return result;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << "\n";
        fout.close();
    }
};

// Please always keep this simple main function!
int main() {
    // Allocate a Task object on heap in order to be able to
    // declare huge static-allocated data structures inside the class.
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
