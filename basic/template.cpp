#include <cstdio>
#include <utility>

template <typename T>
struct SimpleUniquePointer {
    SimpleUniquePointer() = default;
    SimpleUniquePointer(T* ptr) : ptr{ ptr } {}
    ~SimpleUniquePointer() {
        if (ptr) delete ptr;
    }
    SimpleUniquePointer(const SimpleUniquePointer&) = delete;
    SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;
    SimpleUniquePointer(SimpleUniquePointer&& other) noexcept : ptr{ other.ptr } {
        printf("Move constructor being called\n");
        other.ptr = nullptr;
    }
    SimpleUniquePointer& operator=(SimpleUniquePointer&& other) noexcept {
        if (ptr) delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }
    T* get() {
        return ptr;
    }
private:
    T* ptr;
};

struct Tracer {
    Tracer(const char* name) : name{ name } {
        printf("%s constructed\n", name);
    }
    ~Tracer() {
        printf("%s destructed\n", name);
    }
private:
    const char* const name;
};

void consumer(SimpleUniquePointer<Tracer> consumer_ptr) {
    printf("(cons) consumer_ptr: 0x%p\n", consumer_ptr.get());
}

int main() {
    auto ptr_a = SimpleUniquePointer(new Tracer{ "ptr_a" });
    printf("(main) ptr_a: 0x%p\n", ptr_a.get());
    consumer(std::move(ptr_a));
    printf("(main) ptr_a: 0x%p\n", ptr_a.get());
}