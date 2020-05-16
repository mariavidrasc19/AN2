#include <bits/stdc++.h>
using namespace std;

const int kMod = 1e9 + 7;

class Bani {
 public:
    // functia de citire
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int instructiune;
    int N;

    void read_input() {
        std::ifstream fin("bani.in");
        fin >> instructiune;
        fin >> N;
        fin.close();
    }

    // functie recursiva ce calculeaza in complexitate logaritmica
    // baza la puterea exponent
    int exponentiere(int baza, int exp) {
        if (exp == 0) {
            return 1;
        } else {
            if (exp % 2 == 0) {
                int a = exponentiere(baza, exp/2);
                return (1LL * a * a) % kMod;
            } else {
                int a = exponentiere(baza, exp/2);
                return (((1LL * a * a) % kMod) * baza) % kMod;
            }
        }
    }

    // functie care intoarce rezultatul dorit
    int get_result() {
        int rezultat = 1;
        // pentru instructiunea 1 apelam functia exponentiere
        if (instructiune == 1) {
            rezultat = (1LL * 5 * exponentiere(2, N - 1) % kMod) % kMod;
        } else {
            // pentru instructiunea 2 am realizat un vector care retine
            // numarul de variante pt fiecare baconta, la final facand
            // suma posibilitatilor
            std::vector<int> money;
            money = {1, 1, 1, 1, 1};
            for (int i = 2; i <= N; i++) {
                std::vector<int> new_money;
                new_money = {0, 0, 0, 0, 0};

                new_money[0] = ((money[1] + money[2])%kMod + money[4])%kMod;
                new_money[1] = (money[0] + money[3])%kMod;
                new_money[2] = ((money[0] + money[2])%kMod + money[3])%kMod;
                new_money[3] = (money[1] + money[4])%kMod;
                new_money[4] = money[3];

                money = new_money;
            }
            // realizez %kMod la fiecare operatie
            rezultat = (((money[0] + money[1])%kMod + (money[2] + money[3])
                %kMod)%kMod + money[4]) % kMod;
        }
       return rezultat;
    }

    // functia de afisare al rezultatului
    void print_output(int result) {
        std::ofstream fout("bani.out");
        fout << result;
        fout.close();
    }
};

int main() {
    Bani *bani = new Bani();
    // functia solve v-a realiza intreg procesul de rezolvare
    bani->solve();
    delete bani;
    return 0;
}
