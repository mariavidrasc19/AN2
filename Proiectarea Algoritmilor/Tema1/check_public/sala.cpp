#include <bits/stdc++.h>
using namespace std;

const int kMod = 1e9 + 7;

class Sala {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int N;
    int M;
    vector<pair<int, int>> gantere;

    void read_input() {
        std::ifstream fin("sala.in");
        fin >> N;
        fin >> M;
        for (int i = 0; i < N; i++) {
            int x, y;
            fin >> x >> y;
            pair<int, int> a(x, y);
            gantere.push_back(a);
        }
        fin.close();
    }

    int get_result() {
        vector<pair<int, int>> alese;
        pair<int, int> max(0, 0);
        int suma = 0;
        sort(gantere.end(), gantere.begin());
        int min = gantere[0].first;

        for (int i = 1; i < gantere.size(); i++) {
            while (alese.size() < M) {
                if (gantere[i].first * gantere[i].second >
                    gantere[i - 1].first * gantere[i - 1].second) {
                    swap(gantere[i], gantere[i - 1]);
                }

                if (gantere[i - 1].first < min) {
                    min = gantere[i - 1].first;
                }

                suma += gantere[i-1].second;
                alese.push_back(gantere[i-1]);
            }
        }

        suma = suma * min;
        return suma;
    }

    void print_output(int result) {
        std::ofstream fout("sala.out");
        fout << result;
        fout << "\n";
        fout.close();
    }
};

int main() {
    Sala *sala = new Sala();
    sala->solve();
    delete sala;
    return 0;
}
