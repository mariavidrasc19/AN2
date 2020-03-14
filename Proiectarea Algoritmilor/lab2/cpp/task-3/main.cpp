#include <bits/stdc++.h>
using namespace std;

struct Homework {
    int deadline;
    int score;

    Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    vector<Homework> hws;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, deadline, score; i < n; i++) {
            fin >> deadline >> score;
            hws.push_back(Homework(deadline, score));
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Aflati punctajul maxim pe care il puteti obtine planificand
        optim temele.
        */
       std::sort(hws.begin(), hws.end());
        int max_ddl = INT_MIN;
        for (size_t i = 0; i < hws.size(); i++) {
            if (hws[i].deadline > max_ddl) {
                max_ddl = hws[i].deadline;
            }
        }
        std::vector<bool> weeks(max_ddl, false);
        int score = 0;
        for (size_t i = 0; i < hws.size(); i++) {
            int deadline = hws[i].deadline;
            while (deadline > 0) {
                if (weeks[deadline - 1] == false) {
                    score += hws[i].score;
                    weeks[deadline - 1] = true;
                    break;
                }
                deadline--;
            }
        }
        return score;
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
