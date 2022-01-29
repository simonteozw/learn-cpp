// Same as Reader reader but when writer arrvies no more readers can enter
#include <future>
#include "Lightswitch.h"
#include <iostream>

struct DB {
    void write(std::string str) {
        turnstile.lock();
        roomEmpty.lock();
        turnstile.unlock();

        doc += str;
        roomEmpty.unlock();
    }

    // This pattern is known as LightSwitch
    std::string read() {
        turnstile.lock();
        turnstile.unlock();

        readSwitch.lock(roomEmpty);

        std::string res = doc;

        readSwitch.unlock(roomEmpty);

        return doc;
    }

private:
    std::mutex turnstile, roomEmpty;
    std::string doc;
    Lightswitch readSwitch;
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