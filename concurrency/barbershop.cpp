#include <mutex>
#include <thread>
#include <random>
#include <chrono>
#include <vector>
#include <future>

#define N 4

int myrand(int min, int max) {
  static std::mt19937 rnd(std::time(nullptr));
  return std::uniform_int_distribution<>(min,max)(rnd);
}

void barbershop() {
    int customers = 0;
    std::mutex m, customer, barber, customerDone, barberDone;
    customer.lock();
    barber.lock();
    customerDone.lock();
    barberDone.lock();
    std::vector<std::future<void>> customerGroup;

    auto getHaircut = [] (int i) {
        int duration = myrand(1000, 2000);
        printf("Customer %d is getting haircut\n", i);
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    };

    auto cutHair = [] {
        int duration = myrand(1000, 2000);
        // printf("Barber is cutting hair\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    };

    auto customerFn = [&] (int i) {
        while (true) {
            m.lock();
            if (customers == N) {
                m.unlock();
                printf("Customer %d is will come back later\n", i);
                int duration = myrand(1000, 2000);
                std::this_thread::sleep_for(std::chrono::milliseconds(duration));
                continue;
            }
            customers++;
            m.unlock();

            customer.unlock(); // signal customer is here
            barber.lock(); // wait for barber
            getHaircut(i);
            customerDone.unlock(); // signal customer is done
            barberDone.lock(); // wait for barer to be done

            m.lock();
            customers--;
            m.unlock();
        }
    };

    auto barberFn = [&] {
        while (true) {
            customer.lock(); // wait for customer
            barber.unlock(); // signal barber is ready
            cutHair();
            customerDone.lock(); // wait for customer to be done
            barberDone.unlock(); // signal barber is done
        }
    };

    auto theBarber = std::async(std::launch::async, barberFn);

    for (int i = 0; i < 2 * N; i++) {
        customerGroup.push_back(std::async(std::launch::async, customerFn, i));
    }

    theBarber.get();
    for (int i = 0; i < N; i++) customerGroup[i].get();
}

int main() {
    barbershop();
}