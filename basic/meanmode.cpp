#include <cstdio>
#include <utility>
#include <unordered_map>
#include <cstddef>
#include <concepts>

// template <typename T>
// concept Averageable = require(T a) {
//     { a + a } noexcept -> std::same_as<T>;
//     { a / size_t(1) } ->std::same_as<T>;
// };

template <typename T>
T mode(T* values, size_t length) {
    int freq = 0;
    T ans;
    std::unordered_map<T, int> m;
    for (size_t i = 0; i < length; i++) m[values[i]]++;
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->second > freq) {
            freq = it->second;
            ans = it->first;
        }
    }

    return ans;
}

template <typename T>
T mean(const T* values, size_t length) {
    T ans{};
    for (size_t i = 0; i < length; i++) ans += values[i];
    return ans / length;
}

int main() {
    double arr1[] = {1.0, 1.0, 2.0, 3.0};
    int arr2[] = {1,1,1,1,1,2,3,3,3,3,3,3,3,3,3,3,3,4};
    char arr3[] = {'a', 'a', 'b', 'b', 'b', 'c'};
    printf("arr1: %f\narr2: %d\narr3: %c\n", mode(arr1, 4), mode(arr2, 18), mode(arr3, 6));
    printf("arr1 mean: %f, arr2 mean: %d", mean(arr1, 4), mean(arr2, 11));
}