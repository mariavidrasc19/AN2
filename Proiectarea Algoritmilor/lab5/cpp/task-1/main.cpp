#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, k;

    void read_input() {
        ifstream fin("in");
        fin >> n >> k;
        fin.close();
    }

    bool check(std::vector<int> &solution) {
        return true;
    }

    void back(std::vector<int> &domain,  std::vector<int> &solution, vector<vector<int> > &result) {
    if (solution.size() == k) {
        if(check(solution)) {
            result.push_back(solution);
        }
        return;
    }
 
        for (unsigned int i = 0; i < domain.size(); ++i) {
            int tmp = domain[i];
 
            solution.push_back(domain[i]);
            domain.erase(domain.begin() + i);
 
            back(domain, solution, result);
            domain.insert(domain.begin() + i, tmp);
            solution.pop_back();
        }
    }

    vector<vector<int> > get_result() {
        vector<int> domain;
        for (int i = 0; i < n; i++) {
            domain.push_back(i + 1);
        }
        vector<int> solution;
        vector<vector<int> > all;
        back(domain, solution, all);

        return all;
    }

    void print_output(vector<vector<int> > result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (int i = 0; i < (int)result.size(); i++) {
            for (int j = 0; j < (int)result[i].size(); j++) {
                fout << result[i][j] <<
                    (j + 1 != result[i].size() ? ' ' : '\n');
            }
        }
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
