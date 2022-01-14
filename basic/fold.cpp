#include <cstdio>

template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial) {
    for (size_t i = 0; i < length; i++) initial = function(initial, input[i]);
    return initial;
}

template <typename Fn, typename In>
constexpr bool all(Fn function, In* input, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (!function(input[i])) return false;
    }
    return true;
}

int main() {
    int data[]{ 101, 200, 300, 400, 500 };
    size_t data_len = 5;
    auto sum = fold([](auto x, auto y) { return x + y; }, data, data_len, 0);
    printf("Sum: %d\n", sum);

    auto all_gt100 = all([](auto x) { return x > 100; }, data, data_len);
    if(all_gt100) printf("All elements greater than 100.\n");
}