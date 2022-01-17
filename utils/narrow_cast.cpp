#include <cstdio>
#include <optional>
#include <stdexcept>

template <typename To, typename From>
std::optional<To> narrow_cast(From value) {
    const auto converted = static_cast<To>(value);
    const auto backwards = static_cast<From>(converted);
    if (value != backwards) return std::nullopt;
    return converted;
}

int main() {
    int perfect{ 496 };
    const auto perfect_short = narrow_cast<short>(perfect);
    printf("perfect_short: %d\n", perfect_short.value());

    int cyclic{ 142857 };
    const auto cyclic_short = narrow_cast<short>(cyclic);
    printf("cyclic_short has value: %d\n", cyclic_short.has_value());
}
