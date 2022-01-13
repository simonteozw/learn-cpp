// Explore templates, type aliasing, and type casting in c++
#include <cstdio>
#include <stdexcept>

template <typename To, typename From>
struct NarrowCaster {
    To cast(From val) const {
        const auto converted = static_cast<To>(val);
        const auto backwards = static_cast<From>(converted);

        if (val != backwards) throw std::runtime_error{ "Narrowed!" };

        return converted;
    }
};

template <typename From>
using short_caster = NarrowCaster<short, From>;

int main() {
    try {
        const short_caster<int> caster;
        const auto cyclic_short = caster.cast(142857);
        printf("cyclic short %d\n", cyclic_short);
    } catch (const std::runtime_error& e) {
        printf("Exception: %s\n", e.what());
    }
}