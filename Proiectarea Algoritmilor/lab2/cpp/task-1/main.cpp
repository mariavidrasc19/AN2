#include <bits/stdc++.h>
using namespace std;

struct Object {
    int weight;
    int price;

    Object(int _weight, int _price) : weight(_weight), price(_price) {}

    bool operator< (const Object &b) const{
        double rap1 = 1.0 * this->price/this->weight;
        double rap2 = 1.0 * b.price/b.weight;
        if (rap1 >= rap2) {
            return true; 
        }
        return false;
    }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, w;
    vector<Object> objs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> w;
        for (int i = 0, weight, price; i < n; i++) {
            fin >> weight >> price;
            objs.push_back(Object(weight, price));
        }
        fin.close();
    }

    double get_result() {
        std::sort(objs.begin(), objs.end());
        int i = 0;
        double profit = 0.0;
        while (w != 0) {
            if (objs[i].weight == w) {
                profit += objs[i].price;
                w = 0;
            } else if (objs[i].weight > w) {
                profit += (1.0 * w / objs[i].weight) * objs[i].price;
                w = 0;
            } else {
                profit += objs[i].price;
                w -= objs[i].weight;
            }
            i ++;
        }
        
        
        return profit;
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
