#include <set>
#include <chrono>
#include <array>
#include <vector>
#include <iostream>
#include <limits>
#include <future>
#include <sstream>
#include <string>

using namespace std;

struct Stopwatch {
    Stopwatch(chrono::nanoseconds& result)
        : result{ result },
        start{ chrono::high_resolution_clock::now() } {}
    ~Stopwatch() {
        result = chrono::high_resolution_clock::now() - start;
    }
private:
    chrono::nanoseconds& result;
    const chrono::time_point<std::chrono::high_resolution_clock> start;
};

template <typename T>
set<T> factorize(T x) {
    set<T> result{};
    for (T candidate{ 2 }; candidate <= x; candidate++) {
        if (x % candidate == 0) {
            result.insert(candidate);
            x /= candidate;
            candidate = 1;
        }
    }

    return result;
}

string factor_task(unsigned long long x) {
    chrono::nanoseconds elapsed_ns;
    set<unsigned long long> factors;
    {
        Stopwatch stopwatch{ elapsed_ns };
        factors = factorize(x);
    }
    const auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed_ns).count();
    stringstream ss;
    ss << elapsed_ms << " ms: Factoring " << x << "( ";
    for (auto factor : factors) ss << factor << " ";
    ss << ")\n";
    return ss.str();
}

array<unsigned long long, 6> numbers {
    9'699'690,
    179'426'549,
    1'000'000'007,
    4'294'967'291,
    4'294'967'296,
    1'307'674'368'000
};

int main() {
    chrono::nanoseconds elapsed_ns1;
    {
        Stopwatch stopwatch{ elapsed_ns1 };
        for (auto num : numbers) cout << factor_task(num);
    }
    const auto elapsed_ms1 = chrono::duration_cast<chrono::milliseconds>(elapsed_ns1).count();
    cout << elapsed_ms1 << "ms: total program time\n";

    chrono::nanoseconds elapsed_ns2;
    {
        Stopwatch stopwatch{ elapsed_ns2 };
        vector<future<string>> factor_tasks;
        for (auto number : numbers)
            factor_tasks.emplace_back(async(launch::async, factor_task, number));
        for (auto& task : factor_tasks)
            cout << task.get();
    }
    const auto elapsed_ms2 = chrono::duration_cast<chrono::milliseconds>(elapsed_ns2).count();
    cout << elapsed_ms2 << "ms: total program time\n";
}
