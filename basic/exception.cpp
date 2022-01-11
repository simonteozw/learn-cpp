#include <stdexcept>
#include <cstdio>

struct Groucho {
  void forget(int x) {
    if (x == 0xFACE) {
        throw std::runtime_error( "I'd be glad to make an exception." );
    }
    printf("Forgot 0x%x\n", x);
  }
};

int main() {
    Groucho g;
    try {
        g.forget(0xFACE);
        g.forget(0x1234);
        g.forget(0xABCD);
    } catch (const std::runtime_error& e) {
        printf("exception caught with message: %s\n", e.what());
    }
}