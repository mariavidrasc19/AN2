#include <bits/stdc++.h>
using namespace std;

const int kNmax = 2e5 + 10;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    int m;
    vector<pair<int, int> > adj[kNmax];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }
        fin.close();
    }

    int get_result() {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> lista;
        vector<int> distances(n + 1, kNmax);

        int result = 0;
        pair<int, int> nod;
        vector<bool> visited(n + 1, false);
        lista.push({0, 1});

        while (!lista.empty()){
            nod = lista.top();
            lista.pop();

            if (!visited[nod.second]){
                visited[nod.second] = true;
                result = result + nod.first;
                for(auto &it : adj[nod.second]){
                    if (!visited[it.first]) {
                        if (distances[it.first] > it.second){
                            distances[it.first] = it.second;
                            lista.push({distances[it.first], it.first});
                        }
                    }
                }
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
