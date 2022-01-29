#include <mutex>

struct Lightswitch {
    void lock(std::mutex& other) {
        m.lock();
        counter++;
        if (counter == 1) other.lock();
        m.unlock();
    }

    void unlock(std::mutex& other) {
        m.lock();
        counter--;
        if (counter == 0) other.unlock();
        m.unlock();
    }

private:
    int counter;
    std::mutex m;
};