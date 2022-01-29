#include <future>
#include <mutex>
#include <iostream>

struct DB {
    void write(std::string str) {
        roomEmpty.lock();
        doc += str;
        roomEmpty.unlock();
    }

    // This pattern is known as LightSwitch
    std::string read() {
        m.lock();
        readers++;
        if (readers == 1) roomEmpty.lock(); // first in lock
        m.unlock();

        std::string res = doc;

        m.lock();
        readers--;
        if (readers == 0) roomEmpty.unlock(); // last out unlock
        m.unlock();

        return doc;
    }

private:
    std::mutex m, roomEmpty;
    std::string doc;
    int readers;
};

int main() {
    DB db;
    std::future<void> arr[10];

    auto reader = [&] {
        std::string read = db.read();
        std::cout << read << std::endl;
    };

    auto writer = [&] {
        db.write("I am writing. ");
    };

    for (size_t i = 0; i < 10; i++) {
        std::future<void> temp;
        if (i % 2 == 0) temp = std::async(std::launch::async, writer);
        else temp = std::async(std::launch::async, reader);

        arr[i] = std::move(temp);
    }

    for (size_t i = 0; i < 10; i++) arr[i].get();
}