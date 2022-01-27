// taken from Rendezvous problem, Little Book of Semaphores Chapter 3
#include <future>
#include <mutex>
#include <condition_variable>

void rendezvous() {
    // ensure that A1 is before B2 and B1 is before A2
    std::mutex A1Done, B1Done;

    A1Done.lock();
    B1Done.lock();

    auto threadA = std::async(std::launch::async, [&] {
        printf("Statement A1\n");
        A1Done.unlock();

        B1Done.lock();
        printf("Statement A2\n");
        B1Done.unlock();
    });

    std::future<void> threadB = std::async(std::launch::async, [&] {
        printf("Statement B1\n");
        B1Done.unlock();

        A1Done.lock();
        printf("Statement B2\n");
        A1Done.unlock();
    });

    threadA.get();
    threadB.get();

    printf("\n");
}

int main() {
    rendezvous();
    rendezvous();
    rendezvous();
    rendezvous();
    rendezvous();
}