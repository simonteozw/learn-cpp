#include <future>
#include <mutex>
#include <random>
#include <boost/circular_buffer.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <iostream>
#include <unistd.h>
#include <vector>

unsigned int microsecond = 1000000;
std::mt19937_64 mt_engine{ 102787 };
std::uniform_int_distribution<int> int_d{ 1, 10 };

int getEvent() {
    int res = int_d(mt_engine);
    // add in random wait times
    usleep(res * 1000);

    return res;
}

int main() {
    boost::circular_buffer<int> buffer(10); // 10 events at most
    boost::interprocess::interprocess_semaphore items(0), spaces(10);
    std::mutex m;
    std::vector<std::future<void>> threads;

    auto producer = [&] {
        int event = getEvent();
        spaces.wait();
        m.lock();
        buffer.push_back(event);
        std::cout << "Event " << event << " produced\n";
        m.unlock();
        items.post();
    };

    auto consumer = [&] {
        items.wait();
        m.lock();
        int event = buffer.front();
        buffer.pop_front();
        std::cout << "Event " << event << " consumed\n";
        m.unlock();
        spaces.post();
         // event processing code
    };

    for (size_t i = 0; i < 10; i++) {
        std::future<void> temp;
        if (i % 2 == 0) temp = std::async(std::launch::async, producer);
        else temp = std::async(std::launch::async, consumer);

        threads.push_back(std::move(temp));
    }

    for (size_t i = 0; i < 10; i++) {
        threads[i].get();
    }
}