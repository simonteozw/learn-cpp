// taken from Barrier problem, Little Book of Semaphores Chapter 3
#include <future>
#include <mutex>
#include <condition_variable>
#include <semaphore.h>
#include <iostream>
#include <vector>

void barrier(int n) {
    std::vector<std::future<void> > threads;
    int count = 0, temp;
    std::mutex lock, barrier; // should be using counting_semaphore but c++20 is giving many problems
    barrier.lock();

    auto fn = [&] {
        printf("Rendezvous\n");
        lock.lock();
        count++;

        if (count == n) barrier.unlock();
        lock.unlock();

        barrier.lock();
        barrier.unlock();
        printf("In critical point\n");
    };

    for (size_t i = 0; i < n; i++) {
        std::future<void> temp = std::async(std::launch::async, fn);
        threads.push_back(std::move(temp));
    }

    for (size_t i = 0; i < n; i++) threads[i].get();

    printf("\n");
}

int main() {
    int n;
    std::cin >> n;
    barrier(n);
}