#include <mutex>

// once a thread arrives and attempts to enter the mutex
// there is a bound on the number of threads that can proceed ahead of it
struct NoStarveMutex {
    NoStarveMutex() {
        t2.lock();
    }

    void wait() {
        m.lock();
        room1++;
        m.unlock();

        t1.lock();
        room2++;

        m.lock();
        room1--;

        if (room1 == 0) t2.unlock();
        else t1.unlock();
        m.unlock();

        t2.lock();
        room2--;
    }

    void signal() {
        if (room2 == 0) t1.unlock();
        else t2.unlock();
    }

private:
    int room1, room2;
    std::mutex m, t1, t2;
};