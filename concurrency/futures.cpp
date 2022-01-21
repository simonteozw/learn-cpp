#include <future>
#include <string>

using namespace std;

int main() {
    using namespace literals::string_literals;
    auto the_future = async([] { return "female"s; });
    printf("The future is valid: %d\n", the_future.valid());
    if (the_future.valid()) printf("%s\n", the_future.get().c_str());

    future<bool> default_future;
    printf("The future is valid: %d\n", default_future.valid());
}