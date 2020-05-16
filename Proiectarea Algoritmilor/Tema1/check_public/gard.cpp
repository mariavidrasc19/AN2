#include <bits/stdc++.h>
using namespace std;

const int kMod = 1e9 + 7;

class Gard {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int N;
    vector<pair<int, int>> garduri;

    // functia de citire
    void read_input() {
        std::ifstream fin("gard.in");
        fin >> N;
        for (int i = 0; i < N; i++) {
            int x, y;
            fin >> x >> y;
            pair<int, int> a(x, y);
            garduri.push_back(a);
        }
        fin.close();
    }

    // functie care intoarce rezultatul dorit
    int get_result() {
       int nr = 0;
       pair<int, int> gard_max;
       // sortam gardurile de la mic la mare
       sort(garduri.begin(), garduri.end());

        // vom retine mereu gardul maxim fata de care le vom
        // compara pe celelalte
        gard_max.first = garduri[0].first;
        gard_max.second = garduri[0].second;

        for (int i = 1; i < N; i++) {
            // incrementam numarul de garduri de cate origasim unul
            // inclus in gardul max
            // altfel actualizam gardul max
            if (garduri[i].second > gard_max.second) {
                if (garduri[i].first == gard_max.first) {
                    nr = (1LL * nr + 1) % kMod;
                }
                gard_max.second = garduri[i].second;
                gard_max.first = garduri[i].first;
            } else {
                nr = (1LL * nr + 1) % kMod;
            }
        }
        return nr;
    }

    // functia de afisare al rezultatului
    void print_output(int result) {
        std::ofstream fout("gard.out");
        fout << result;
        fout << "\n";
        fout.close();
    }
};

int main() {
    Gard *gard = new Gard();
    // functia solve v-a realiza intreg procesul de rezolvare
    gard->solve();
    delete gard;
    return 0;
}
