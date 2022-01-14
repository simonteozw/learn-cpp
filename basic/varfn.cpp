#include <cstdio>
#include <cstdint>
#include <cstdarg>

int sum(size_t n, ...) {
    // va_list declares local var representing variadic arguments
    va_list args;
    va_start(args, n);
    int result{};

    while (n--) {
        auto next_elem = va_arg(args, int);
        result += next_elem;
    }
    va_end(args);
    return result;
}

template <typename T>
constexpr T sum2(T x) { return x; }

template <typename T, typename... Args>
constexpr T sum2(T x, Args... args) { return x + sum2(args...); }

template <typename... T>
constexpr auto sum3(T... args) { return (... + args); }

int main() {
    printf("The answer is %d\n", sum(6, 2, 4, 6, 8, 10, 12));
    printf("The answer is %d\n", sum2(2, 4, 6, 8, 10, 12));
    printf("The answer is %d\n", sum3(2, 4, 6, 8, 10, 12));
}