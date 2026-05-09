#include <iostream>
#include <bitset>
#include <vector>
#include <array>

void problem49();
void check_permutations(int p);

const int size = 10000;
std::bitset<size> prime_sieve;


void init_sieve() {
    prime_sieve.set();
    prime_sieve[0] = false;
    prime_sieve[1] = false;
    for (int i=2; i*i<size; i++) {
        if (prime_sieve[i]) {
            for (int j=i*i; j<size; j += i) {
                prime_sieve[j] = false;
            }
        }
    }
}

void problem49() {
    for (int i=1000; i<size; i++) {
        if (!prime_sieve[i]) continue;

        check_permutations(i);
    }
}

void permutation_generator(std::array<int, 4>& pdig, int si, std::vector<int>& pperm) {
    if (si == 3 && pdig[0]>0) {
        const int p = pdig[0]*1000 + pdig[1]*100 + pdig[2]*10 + pdig[3];

        bool contains = false;
        for(int val : pperm) if(val == p) contains = true;
        if(!contains && prime_sieve[p]) pperm.push_back(p);
    }

    for (int k=si; k<4; k++) {
        std::swap(pdig[si], pdig[k]);

        permutation_generator(pdig, si+1, pperm);

        std::swap(pdig[si], pdig[k]);
    }
}

void find_equidistant_progression(std::vector<int>& prog) {
    int n = prog.size();
    for (int i=0; i<n-2; i++) {
        for (int j=i+1; j<n-1; j++) {
            for (int k=j+1 ; k<n; k++) {
                if (prog[j] - prog[i] == prog[k] - prog[j]) {
                    std::cout << prog[i] <<" "<< prog[j] << " " << prog[k] << std::endl;
                }
            }
        }
    }
}

void check_permutations(const int p) {
    std::array<int, 4> pdig;
    pdig[0] = p / 1000 % 10;
    pdig[1] = p / 100 % 10;
    pdig[2] = p / 10 % 10;
    pdig[3] = p % 10;
    std::vector<int> pperm;
    permutation_generator(pdig, 0, pperm);
    if (pperm.size() < 3) return;
    std::sort(pperm.begin(), pperm.end());

    find_equidistant_progression(pperm);

    // std::cout << "Prime " << p << std::endl;
    // for (int value : pperm) {
    //     std::cout << value << " ";
    // }
    // std::cout << std::endl;
}

int main() {
    init_sieve();
    problem49();
    return 0;
}
