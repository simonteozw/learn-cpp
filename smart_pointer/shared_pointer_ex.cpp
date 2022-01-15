#include <cstdio>
#include <memory>

using FileGuard = std::shared_ptr<FILE>;

struct Hal {
    Hal(std::shared_ptr<FILE> file) : file{ file } {
        fprintf(file.get(), "HELLO DAVE\n123456\n");
    }
    ~Hal() {
        fprintf(file.get(), "Stop, Dave\n");
    }
    void write_status() {
        fprintf(file.get(), "I'm completely operational\n");
    }
    std::shared_ptr<FILE> file;
};

void say_hello(FileGuard file) {
    fprintf(file.get(), "HELLO SIMON\n123456\n");
}

auto my_deleter = [](int* x) {
    printf("Deleting an int at %p\n", x);
    delete x;
};

int main() {
    auto file = fopen("HAL9000", "w");
    if (!file) return errno;

    FileGuard file_guard{ file, fclose };
    Hal h1{ file_guard };
    h1.write_status();

    Hal h2{ file_guard };
    h2.write_status();

    Hal h3{ file_guard };
    h3.write_status();

    std::shared_ptr<int> my_up{ new int };
    return 0;
}