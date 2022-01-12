#include <cstddef>
#include <cstdio>
#include <new>

struct Bucket {
    const static size_t data_size{ 4096 };
    std::byte data[data_size];
};

struct LargeBucket {
    const static size_t data_size{ 1048576 };
    std::byte data[data_size];
};

struct Heap {
    void* allocate(size_t bytes) {
        if (bytes > LargeBucket::data_size) throw std::bad_alloc();

        if (bytes > Bucket::data_size) {
            for (size_t i = 0; i < n_heap_containers; i++) {
                if (!largebucket_used[i]) {
                    largebucket_used[i] = true;
                    return largebuckets[i].data;
                }
            }
        } else {
            for (size_t i = 0; i < n_heap_containers; i++) {
                if (!bucket_used[i]) {
                    bucket_used[i] = true;
                    return buckets[i].data;
                }
            }
        }
        throw std::bad_alloc{};
    }

    void free(void* p) {
        for (size_t i = 0; i < n_heap_containers; i++) {
            if (buckets[i].data == p) {
                bucket_used[i] = false;
                return;
            }
            if (largebuckets[i].data == p) {
                largebucket_used[i] = false;
                return;
            }
        }
    }

    static const size_t n_heap_containers{ 10 };
    Bucket buckets[n_heap_containers]{};
    bool bucket_used[n_heap_containers]{};
    LargeBucket largebuckets[n_heap_containers]{};
    bool largebucket_used[n_heap_containers]{};
};

Heap heap;

void* operator new(size_t n_bytes) {
    return heap.allocate(n_bytes);
}

void operator delete(void* p) {
    return heap.free(p);
}

int main() {
    printf("Buckets: %p\n", heap.buckets);
    printf("LargeBuckets: %p\n", heap.largebuckets);
    auto breakfast = new unsigned int{ 0xC0FFEE };
    auto dinner = new unsigned int{ 0xDEADBEEF };
    auto aa = new char[50000];
    for (size_t i = 0; i < 5000; i++) aa[i] = 'A';

    auto bb = new char[1048576];
    for (size_t i = 0; i < 5000; i++) aa[i] = 'B';

    printf("Breakfast: %p 0x%x\n", breakfast, *breakfast);
    printf("Dinner: %p 0x%x\n", dinner, *dinner);
    printf("AA: %p 0x%x\n", aa, *aa);
    printf("BB: %p 0x%x\n", bb, *bb);

    delete breakfast;
    delete dinner;
    delete aa;
    delete bb;

    try {
        while (true) {
            new char;
            printf("Allocated a char\n");
        }
    } catch (const std::bad_alloc&) {
        printf("std::bad_alloc caught\n");
    }
}
