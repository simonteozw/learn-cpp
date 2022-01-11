#include <cstdio>
#include<unistd.h>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <sys/time.h>

struct TimerClass {
    TimerClass() {
        gettimeofday(&construction_time, NULL);
        name = new char[10];
        name[0] = 0;
    }

    ~TimerClass() {
        timeval destruction_time;
        gettimeofday(&destruction_time, NULL);
        if (construction_time.tv_sec != timeval{0}.tv_sec) printf("Object Duration of %s: %ld\n", name, destruction_time.tv_sec - construction_time.tv_sec);
        delete[] name;
    }

    // copy constructor
    TimerClass(const TimerClass& other) : construction_time{ other.construction_time }, name{ new char[10] } {
        std::strncpy(name, other.name, 10);
    }

    // move constructor
    TimerClass(TimerClass&& other) noexcept : construction_time{ other.construction_time }, name{ other.name } {
        other.name = nullptr;
        other.construction_time = timeval{0};
    }

    // copy assigment operator
    TimerClass& operator=(const TimerClass& other) {
        if (this == &other) return *this;
        const auto new_name = new char[10];
        delete[] name;
        name= new_name;
        std::strncpy(name, other.name, 10);
        return *this;
    }

    // move assigment operator
    TimerClass& operator=(TimerClass&& other) {
        if (this == &other) return *this;
        delete[] name;
        name = other.name;
        construction_time = other.construction_time;
        other.name = nullptr;
        other.construction_time = timeval{0};
        return *this;
    }

    bool set_name(const char* x) {
        const int x_len = strlen(x);
        if (x_len > 10) return false;
        std::strncpy(name, x, 9);
        name[9] = 0;
        return true;
    }

private:
    timeval construction_time;
    char* name;
};

int main() {
    TimerClass t1;
    t1.set_name("ace");
    TimerClass t2(t1);
    t2.set_name("bob");
    TimerClass t3;
    t3 = t2;
    t3.set_name("cat");
    TimerClass t4;
    t4 = std::move(t3);
    t4.set_name("don");
    TimerClass t5(std::move(t4));
    t5.set_name("eko");
    sleep(3);
    printf("\n");
}