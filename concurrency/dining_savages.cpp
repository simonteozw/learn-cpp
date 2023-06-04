#include <mutex>
#include <thread>
#include <random>
#include <chrono>

#define M 10

int main() {
    int servings = 0;
    std::mutex lock, emptyPot, fullPot;
    emptyPot.lock();
    fullPot.lock();

    auto cook = [&] {
        while (true) {
            emptyPot.lock();
            servings = M;
            printf("Cook has refilled the pot\n");
            fullPot.unlock();
        }
    };

    auto eater = [&] {
        while (true) {
            lock.lock();
            if (servings == 0) {
                emptyPot.unlock();
                fullPot.lock();
            }
            servings--;
            printf("Eater has taken 1 serving\n");
            lock.unlock();
            printf("Eater is eating\n");
        }
    };

    std::thread chef([&] { cook(); });
    std::thread eater1([&] { eater(); });
    std::thread eater2([&] { eater(); });
    std::thread eater3([&] { eater(); });
    std::thread eater4([&] { eater(); });
    std::thread eater5([&] { eater(); });
    std::thread eater6([&] { eater(); });
    std::thread eater7([&] { eater(); });
    std::thread eater8([&] { eater(); });
    std::thread eater9([&] { eater(); });
    std::thread eater10([&] { eater(); });

    chef.join();
    eater1.join();
    eater2.join();
    eater3.join();
    eater4.join();
    eater5.join();
    eater6.join();
    eater7.join();
    eater8.join();
    eater9.join();
    eater10.join();
}