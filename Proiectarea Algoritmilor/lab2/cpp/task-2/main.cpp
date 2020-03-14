#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m;
    vector<int> dist;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 0, d; i < n; i++) {
            fin >> d;
            dist.push_back(d);
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Aflati numarul minim de opriri necesare pentru a ajunge
        la destinatie.
        */

       int benzina = m;
       int ultima = 0;
        int opriri = 0;
       for (int i = 1; i < n; i++)
       {
           if ((benzina == dist[i] - dist[ultima]) && (i == n-1)){
                return opriri;
           } else if(benzina <= dist[i] - dist[ultima]) {
               if (benzina >= dist[i - 1] - dist[ultima]){
                    ultima = i-1;
                    opriri++;
                }
           }else if (benzina > dist[i] - dist[ultima]) {
                if (ultima == n -1) {
                    return opriri;
                }
           }
       }
        return opriri;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
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
