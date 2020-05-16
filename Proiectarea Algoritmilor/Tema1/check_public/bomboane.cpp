#include <bits/stdc++.h>
using namespace std;

const int kMod = 1e9 + 7;

class Bomboane {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int N;
    int M;
    vector<pair<int, int>> intervale;

    // functia de citire
    void read_input() {
        ifstream fin("bomboane.in");
        fin >> N >> M;
        for (int i = 0; i < N; i++) {
            int x, y;
            fin >> x >> y;
            pair<int, int> a(x, y);
            intervale.push_back(a);
        }
        fin.close();
    }

    // functie care intoarce rezultatul dorit
    int get_result() {
        int sum = 0;
        for (int i = 0; i < N; i++) {
            sum += intervale[i].second;
        }
        // verificam criteriile de baza pe care trebuie
        // sa le indeplineasca inputul
        if (sum < M) {
            return 0;
        } else if (sum == M) {
            return 1;
        }

        // reducem toate intervalele pentru a incepe de la 0
        // scadem desigur din totalul de bomboane pe cele care
        // trebuiesc obligatoriu date
        for (int i = 0; i < N; i++) {
            if (intervale[i].first > 0) {
               M -= intervale[i].first;
               intervale[i].second -= intervale[i].first;
               intervale[i].first = 0;
            }
        }
        // matricea dp va avea nr de copii + 1 linii
        // si numar de bomboane + 1 coloane
        vector<vector<int>> dp;
        dp.resize(N + 1);
        dp[0].resize(M + 1);

        // initializam matricea dp
        // pe coloana cu 0 copii vom avea de dat bomboanele,
        // indiferent de nr lor, intr-un singur fel = 1;
        for (int i = 1; i <= N; i++) {
            dp[i].resize(M + 1);
            dp[i][0] = 1;
        }

        // pentru fiecare numar de bomboane, atunci cand vom imparti
        // la un copil pe prima coloana imparim intr-un fel:
        // 1, daca poate stoca nr de bomboane
        // 0, daca nu
        for (int i = 0; i <= M; i++) {
            if (i <= intervale[0].second) {
                dp[1][i] = 1;
            } else {
                dp[1][i] = 0;
            }
        }

        // vom completa matricea pana la final in functie de vecinele lor
        // egale pe coloana si pe linie
        for (int i = 2; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                int max = intervale[i-1].second;
                if (j < max) {
                    max = j;
                }
                for (int k = 0; k <= max; k++) {
                    dp[i][j] = (1LL * (dp[i][j] + dp[i-1][j - k])) % kMod;
                }
            }
        }

        // rezultatul este ultimul element al matricei
        return dp[N][M];
    }

    // functia de afisare al rezultatului
    void print_output(int result) {
        ofstream fout("bomboane.out");
        fout << result;
        fout << "\n";
        fout.close();
    }
};

int main() {
    Bomboane *bomboane = new Bomboane();
    // functia solve v-a realiza intreg procesul de rezolvare
    bomboane->solve();
    delete bomboane;
    return 0;
}
