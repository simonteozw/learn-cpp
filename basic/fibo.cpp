#include "fibo.h"
#include "prime.h"
#include <cstdio>

int main() {
    for (const auto i : FibonacciRange{ 5000 }) {
        printf("%d ", i);
    }
    printf("\n");

    FibonacciRange range{ 5000 };
    const auto end = range.end();
    for (auto x = range.begin(); x != range.end(); ++x) {
        const auto i = *x;
        printf("%d ", i);
    }
    printf("\n");

    for (const auto i : PrimeNumberRange{ 5000 }) {
        printf("%d ", i);
    }
}