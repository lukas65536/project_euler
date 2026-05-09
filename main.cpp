#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <algorithm>

template<typename T>
struct random_var_X{
    std::vector<double> probabilities;
    std::vector<T> values;
};

template<typename T>
double mean(random_var_X<T>& x) {
    double mu = 0.0;
    for (int i=0; i<x.values.size(); i++) {
        mu += x.values[i] * x.probabilities[i];
    }
    return mu;
}

template<typename T>
double standard_deviation(random_var_X<T>& x, const double mu) {
    double sigma = 0.0;
    for (int i=0; i<x.values.size(); i++) {
        sigma += x.values[i] * x.values[i] * x.probabilities[i];
    }
    return std::pow(sigma - mu*mu, 0.5);
}

template<typename T>
double skew(random_var_X<T>& x, double sigma, double mu) {
    double skew = 0.0;
    for (int i=0; i<x.values.size(); i++) {
        skew += std::pow((x.values[i] - mu) / sigma, 3.0) * x.probabilities[i];
    }
    return skew;
}

/* X_0 = 0, X_1 = 1
 * X_t =
 * if X_{t-2} = 0 then 0
 * else +-|X_{t-2}|
 * !! note !!
 * this walk grows like max |X_m| = fibonacci(m) = BigO(phi^n)
 * so if m=50 the max |X_m| = 12_586_269_025 = F_m
 *
 * P(X=x) = #{ways to get x}/#{all}
 *
 * test with long long
 *
 */
struct Entry {
    long long current;
    long long prev_mag;
    double w;
};

void iterate_random_walk_v2(int depth, long long prev1, long long prev2, double w) {
    std::vector<Entry> current_states;
    current_states.push_back({prev1, prev2, w});
    current_states.reserve(100000);

    for (int u=0; u<depth; u++) {
        std::vector<Entry> next_states;
        next_states.reserve(current_states.size());

        for (const auto& entry : current_states) {
            if (entry.prev_mag == 0) {
                next_states.push_back({entry.current, std::abs(entry.current), entry.w});
            } else {
                long long next_mag = std::abs(entry.current);
                next_states.push_back({entry.current + entry.prev_mag, next_mag, 0.5*entry.w});
                next_states.push_back({entry.current - entry.prev_mag, next_mag, 0.5*entry.w});
            }

        }
        std::sort(next_states.begin(), next_states.end(), [](const Entry& a, const Entry& b) {
            if (a.current != b.current) return a.current < b.current;
            return a.prev_mag < b.prev_mag;
        });

        if (next_states.empty()) continue;
        int j = 0;
        for (int i = 1; i < next_states.size(); ++i) {
            if (next_states[i].current == next_states[j].current &&
                next_states[i].prev_mag == next_states[j].prev_mag) {
                next_states[j].w += next_states[i].w;
                } else {
                    j++;
                    next_states[j] = next_states[i];
                }
        }
        next_states.resize(j + 1);
        current_states = std::move(next_states);

    }
    std::cout << "iter done, " << current_states.size() << " states" << std::endl;

    random_var_X<long long> x;
    for (const auto& entry : current_states) {
        x.values.push_back(entry.current);
        x.probabilities.push_back(entry.w);
    }
    double mu = mean(x);
    double sigma = standard_deviation(x, mu);
    double skew_ = skew(x, sigma, mu);
    std::cout << "Skew " << std::setprecision(10) <<skew_ << std::endl;
}

void random_walk(int length) {
    iterate_random_walk_v2(length-1, 1, 0, 1.0);
}

double m1[51], m2[51], m3[51];
void solution(int depth) {
    m1[0] = m2[0] = m3[0] = 0;
    m1[1] = m2[1] = m3[1] = 1;
    m1[2] = m2[2] = m3[2] = 1;

    for (int i=3; i<=depth; i++) {
        m1[i] = m1[i-1];
        m2[i] = m2[i-1] + m2[i-2];
        m3[i] = m3[i-1] + 3.0*m3[i-2];
    }
    int n = depth;
    double skew = std::pow(m2[n] - 1,-1.5) * (m3[n] - 3*m2[n] + 2); // m1[n]=1 for n>0
    std::cout << "Skew " << std::setprecision(15) <<skew << std::endl;
}


int main() {
    // Read the notes on why this works!
    solution(50);
    //random_walk(3);
    // for (const auto& [key, val] : distribution) {
    //      std::cout << key << " " << val <<std::endl;
    // }
    // std::cout << total;
    return 0;
}