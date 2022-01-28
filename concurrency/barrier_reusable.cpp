// taken from Barrier problem, Little Book of Semaphores Chapter 3
#include <future>
#include <mutex>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <iostream>
#include <vector>

int count = 0;
std::mutex lock;
boost::interprocess::interprocess_semaphore barrier(0);

void barrier_reusable(int n) {
    std::vector<std::future<void> > threads;
    auto fn = [&] {
        printf("Rendezvous\n");
        lock.lock();
        count++;

        if (count == n) barrier.post();
        lock.unlock();

        barrier.wait();
        barrier.post();
        printf("In critical point\n");

        lock.lock();
        count--;

         // put checks within mutex so that threads cannot be interrupted after changing counter and before checking it
        if (count == 0) barrier.wait();
        lock.unlock();
    };

    for (size_t i = 0; i < n; i++) {
        std::future<void> temp = std::async(std::launch::async, fn);
        threads.push_back(std::move(temp));
    }

    for (size_t i = 0; i < n; i++) threads[i].get();

    printf("\n");
}

int main() {
    int n, total = 5;
    for (int i = 0; i < total; i++) {
        std::cin >> n;
        barrier_reusable(n);
    }
}