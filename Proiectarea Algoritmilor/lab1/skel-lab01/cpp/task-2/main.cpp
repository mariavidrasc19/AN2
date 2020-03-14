#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(compute_sqrt());
    }

private:
    double n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    double cautare_sqrt(float jos, float sus) {
        if (abs(((sus + jos)/2)*((sus + jos)/2) - n) <= 0.0001) {
            return (sus + jos)/2;
        }
        if (((sus + jos)/2)*((sus + jos)/2) < n) {
            return cautare_sqrt((sus + jos)/2, sus);
        }
        if (((sus + jos)/2)*((sus + jos)/2) > n) {
            return cautare_sqrt(jos, (sus + jos)/2);
        }
    }

    double compute_sqrt() {
        /*
        TODO: Calculati sqrt(n) cu o precizie de 0.001
        Precizie de 10^-x = |rezultatul vostru - rezultatul corect| <= 10^-x
        */
       if (n < 0) {
           return 0.0;
       }        
       if (n < 1) {
           return cautare_sqrt(0, 1);
       } else {
           return cautare_sqrt(0, n);
       }
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
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
