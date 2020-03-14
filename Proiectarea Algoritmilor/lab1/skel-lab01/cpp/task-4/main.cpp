#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(fast_pow(base, exponent, mod));
    }

private:
    int base, exponent, mod;

    void read_input() {
        ifstream fin("in");
        fin >> base >> exponent >> mod;
        fin.close();
    }

    int fast_pow(int base, int exponent, int mod) {
        // TODO: Calculati (base ^ exponent) % mod in O(log exponent)
        if (exponent == 1) {
            return base % mod;
        }
        if (exponent % 2  == 0) {
            return (1LL * fast_pow(base, exponent/2, mod) * fast_pow(base, exponent/2, mod)) %mod;
        } else {
            return (1LL * base * ((1LL * fast_pow(base, (exponent-1)/2, mod)  * fast_pow(base, exponent/2, mod))%mod)) % mod;
        }
        return 0;
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
