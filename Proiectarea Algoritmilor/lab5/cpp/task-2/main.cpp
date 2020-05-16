#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    void BKT(int nr, vector<vector<int> >& all, vector<int>& solution) {
        all.push_back(solution);

        if (nr == n) {
            return;
        }

        for (int i = (nr > 0 ? solution[nr - 1] + 1 : 1); i <= n; ++i) {
            solution.push_back(i);
            BKT(nr + 1, all, solution);
            solution.pop_back();
        }
    }

	vector<vector<int> > get_result() {
		vector<vector<int> > all;
		vector<int> solution;
        int number = 0;

		BKT(number, all, solution);

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
