#include <unordered_set>

struct PrimeNumberIterator {
    bool operator!=(int x) const {
        return x >= current;
    }

    PrimeNumberIterator& operator++() {
        int next = current + 1;
        while (!is_prime(next)) next++;
        current = next;
        seen_primes.insert(current);

        return *this;
    }

    int operator*() const {
        return current;
    }
private:
    std::unordered_set<int> seen_primes { 2 };
    int current { 2 };

    bool is_prime(int x) {
        // printf("is_prime %d current: % d num_primes: %lu\n", x, current, seen_primes.size());
        for (auto it : seen_primes) {
            if (x % it == 0) return false;
        }
        return true;
    }
};

struct PrimeNumberRange {
    explicit PrimeNumberRange(int max) : max{ max } {}
    PrimeNumberIterator begin() {
        return PrimeNumberIterator{};
    }
    int end() const {
        return max;
    }
private:
    int max;
};