#include <future>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
struct ThreadsafeQueue {
    void push(T elem) {
        std::scoped_lock<std::mutex> lock{ m };
        q.push(elem);
        cv.notify_all();
    }

    T front() {
        std::lock_guard<std::mutex> guard{ m };
        if (q.empty()) throw std::runtime_error( "Queue is empty" );
        return q.front();
    }

    T wait_and_pop() {
        size_t s = 0;
        {
            std::lock_guard<std::mutex> guard{ m };
            s = q.size();
        }
        std::unique_lock<std::mutex> lock{ m };
        if (s == 0) cv.wait(lock, [&] { return q.size() > 0; });
        T res = q.front();
        q.pop();

        return res;
    }

private:
    std::mutex m;
    std::queue<T> q;
    std::condition_variable cv;
};

int main() {
    ThreadsafeQueue<int> tsq;
    auto push_nums = std::async(std::launch::async, [&] {
        for (int i = 0; i < 10; i++) tsq.push(i);
    });

    auto print_nums = std::async(std::launch::async, [&] {
        for (int i = 0; i < 10; i++) printf("Print nums: %d\n", tsq.front());
    });

    auto pop_nums = std::async(std::launch::async, [&] {
        for (int i = 0; i < 10; i++) printf("Pop nums: %d\n", tsq.wait_and_pop());
    });

    push_nums.get();
    print_nums.get();
    pop_nums.get();
}