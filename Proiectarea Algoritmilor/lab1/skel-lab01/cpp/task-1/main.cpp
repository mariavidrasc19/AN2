#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, x;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, e; i < n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin >> x;
        fin.close();
    }

    int cautare_binara_a_el(int jos, int sus) {
        if(x == v[jos]) {
            return jos;
        } else {
            if (x > v[(sus + jos)/2]) {
                return cautare_binara_a_el((sus + jos)/2, sus);
            }
            if (x > v[(sus + jos)/2]) {
                return cautare_binara_a_el(jos, (sus + jos)/2);
            }
        }
        return -1;
    }

    int find_first() {
        /*
        TODO: Cautati prima pozitie pe care se afla valoarea x
        In cazul in care x nu apare in sir, returnati -1
        */
        int pozitie = cautare_binara_a_el(0, n - 1);
        while (v[pozitie] == v[pozitie - 1]) {
            pozitie --;
        }
        return pozitie;
    }

    int find_last() {
        /*
        TODO: Cautati ultima pozitie pe care se afla valoarea x
        In cazul in care x nu apare in sir, returnati -1
        */
       int pozitie = cautare_binara_a_el(0, n - 1);
        while (v[pozitie] == v[pozitie + 1]) {
            pozitie ++;
        }
        return pozitie;
    }

    int get_result() {
        // TODO: Calculati numarul de aparitii ale lui x in vectorul v
        int prima = find_first();
        int ultima = find_last();
        return ultima - prima + 1;
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
