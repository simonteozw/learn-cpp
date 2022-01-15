#include <cstdio>
#include <memory>

using FileGuard = std::unique_ptr<FILE, int(*)(FILE*)>;

void say_hello(FileGuard file) {
    fprintf(file.get(), "HELLO SIMON");
}

auto my_deleter = [](int* x) {
    printf("Deleting an int at %p\n", x);
    delete x;
};

int main() {
    auto file = fopen("HAL9000", "w");
    if (!file) return errno;

    FileGuard file_guard{ file, fclose };
    say_hello(std::move(file_guard));

    std::unique_ptr<int, decltype(my_deleter)> my_up{
        new int,
        my_deleter
    };
    return 0;
}