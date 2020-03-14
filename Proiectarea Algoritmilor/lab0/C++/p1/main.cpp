#include <iostream>
#include <map>
#include <vector>
#include <queue>

#include "complex.h"

bool operator<(const Complex &a, const Complex &b)
{
    //TODO Intoarceti true daca a < b, fals altfel
    if (a.r < b.r) {
        return true;
    } else if (a.r == b.r) {
        if (a.i < b.i) {
            return true;
        }
    }
    return false;
    
}

std::vector<Complex> get_sorted(const std::vector<Complex> &v)
{
    std::vector<Complex> res;
    //TODO Folosind priority_queue, adaugati elementele din v în ordine descrescătoare.
    std::priority_queue<Complex, std::vector<Complex>, std::less<Complex> > prq; 
    for(unsigned int i = 0; i < v.size(); i ++) {
        prq.push(v[i]);
    }
    while(!prq.empty()) {
        Complex nr_complex = prq.top();
        prq.pop();
        res.push_back(nr_complex);
    }
    return res;
}

std::map<Complex, int> get_mapping(const std::vector<Complex> &v)
{
    std::map<Complex, int> res;
    //TODO Adăugati în map, pentru fiecare element din v, poziția sa în vectorul sortat.
    std::vector<Complex> v_sortat = get_sorted(v);
    for(unsigned int i = 0; i < v.size(); i ++) {
        res[v_sortat[i]] = i;
    }
    return res;
}

int main(void)
{
    std::vector<Complex> v;
    // Citeste date de test.
    v = read_data(".date.in");
    std::cout << "Vectorul initial" << std::endl;
    write_vector(v);

    // Verifica sortarea.
    std::vector<Complex> sorted = get_sorted(v);
    std::cout << "Vectorul sortat" << std::endl;
    write_vector(sorted);

    // Verifica maparea.
    std::cout << "Maparea" << std::endl;
    std::map<Complex, int> mapping = get_mapping(v);

    for (unsigned int i = 0; i < sorted.size(); i++)
    {
        std::cout << sorted[i] << " e pe pozitia "
                  << mapping[sorted[i]] << std::endl;
    }

    return 0;
}
