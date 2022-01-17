#include <random>

int main() {
    std::mt19937_64 mt_engine{ 102787 };
    std::uniform_int_distribution<int> int_d{ 32, 126 };

    char* password = new char[10];

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) password[j] = (char) int_d(mt_engine);

        printf("%s\n", password);
    }

}