#include <future>
#include <iostream>

using namespace std;

void goat_rodeo() {
    const size_t iterations{ 1'000'000 };
    int tin_cans_available{};

    auto eat_cans = async(launch::async, [&] {
        for (size_t i = 0; i < iterations; i++) tin_cans_available--;
    });

    auto deposit_cans = async(launch::async, [&] {
        for (size_t i = 0; i < iterations; i++) tin_cans_available++;
    });

    eat_cans.get();
    deposit_cans.get();

    // if deposit_cans decrements, result is also unpredictable
    // if deposit_cans doesn't exist, result is always -1'000'000

    cout << "Tin cans: " << tin_cans_available << "\n";
}

int main() {
    goat_rodeo();
    goat_rodeo();
    goat_rodeo();
}