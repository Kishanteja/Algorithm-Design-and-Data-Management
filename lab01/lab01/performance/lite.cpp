#include <iostream>
#include <vector>
#include "rdtsc.h"

typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef unsigned long long ticks;

using namespace std;

int test_array(size_t N) {
    int* array = new int[N];
    for (size_t i = 0; i < N; ++i) {
        array[i] = i;
    }
    int sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += array[i];
    }
    delete[] array;
    return sum;
}

int test_array_pre_allocated(int* bigarray, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        bigarray[i] = i;
    }
    int sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += bigarray[i];
    }
    return sum;
}

int test_local(size_t N) {
    vector<int> bigarray;
    for (size_t i = 0; i < N; ++i) {
        bigarray.push_back(i);
    }
    int sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += bigarray[i];
    }
    return sum;
}

int test_local_reserve(size_t N) {
    vector<int> bigarray;
    bigarray.reserve(N);
    for (size_t i = 0; i < N; ++i) {
        bigarray.push_back(i);
    }
    int sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += bigarray[i];
    }
    return sum;
}

int test_local_iter(size_t N) {
    vector<int> bigarray(N);
    for (size_t i = 0; i < N; ++i) {
        bigarray[i] = i;
    }
    int sum = 0;
    for (const int& v : bigarray) {
        sum += v;
    }
    return sum;
}

int test_static(size_t N) {
    static vector<int> bigarray;
    bigarray.resize(N);
    for (size_t i = 0; i < N; ++i) {
        bigarray[i] = i;
    }
    int sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += bigarray[i];
    }
    return sum;
}

int main() {
    ClockCounter time;
    const size_t NM = 32 * 1024 * 1024;
    size_t N = 2;

    int* pre_allocated_array = new int[NM];

    for (unsigned idx = 0; idx < 5; ++idx) {
        const size_t M = NM / N;

        std::cout << "N: " << N << "\n";

        // Test local array
        time.start();
        int sum = 0;
        for (unsigned int k = 0; k < M; ++k) {
            sum += test_array(N);
        }
        double t = static_cast<double>(time.stop());
        std::cout << "Local array: " << t / (2 * N * M) << " ticks per access, sum: " << sum << "\n";

        // Test pre-allocated array
        time.start();
        sum = 0;
        for (unsigned int k = 0; k < M; ++k) {
            sum += test_array_pre_allocated(pre_allocated_array, N);
        }
        t = static_cast<double>(time.stop());
        std::cout << "Pre-allocated array: " << t / (2 * N * M) << " ticks per access, sum: " << sum << "\n";

        // Test local vector
        time.start();
        sum = 0;
        for (unsigned int k = 0; k < M; ++k) {
            sum += test_local(N);
        }
        t = static_cast<double>(time.stop());
        std::cout << "Local vector: " << t / (2 * N * M) << " ticks per access, sum: " << sum << "\n";

        // Test local vector with reserve
        time.start();
        sum = 0;
        for (unsigned int k = 0; k < M; ++k) {
            sum += test_local_reserve(N);
        }
        t = static_cast<double>(time.stop());
        std::cout << "Local vector with reserve: " << t / (2 * N * M) << " ticks per access, sum: " << sum << "\n";

        // Test local vector with iterator
        time.start();
        sum = 0;
        for (unsigned int k = 0; k < M; ++k) {
            sum += test_local_iter(N);
        }
        t = static_cast<double>(time.stop());
        std::cout << "Local vector with iterator: " << t / (2 * N * M) << " ticks per access, sum: " << sum << "\n";

        // Test static vector
        time.start();
        sum = 0;
        for (unsigned int k = 0; k < M; ++k) {
            sum += test_static(N);
        }
        t = static_cast<double>(time.stop());
        std::cout << "Static vector: " << t / (2 * N * M) << " ticks per access, sum: " << sum << "\n";

        N = N * 64;
    }

    delete[] pre_allocated_array;

    return 0;
}
