#ifndef TIMSORT_TEST_H
#define TIMSORT_TEST_H

#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>

double t1, t2, t3;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

template <class RandomAccessIterator, class Compare>
void sortAndCheck(RandomAccessIterator first, RandomAccessIterator last, Compare comp, std::string message) {

    typedef typename std::iterator_traits<RandomAccessIterator>::value_type T;

    T* first1 = new T[last - first];
    std::copy(first, last, first1);

    t1 = clock();
    timSort(first, last, comp);
    t2 = clock();
    std::sort(first1, first1 + (last - first), comp);
    t3 = clock();

    t1 = (t2 - t1) / CLOCKS_PER_SEC;
    t2 = (t3 - t2) / CLOCKS_PER_SEC;

    bool f = true;
    for (size_t i = 0; i < last - first && f; ++i) {
        if (*(first + i) != first1[i]) {
            f ^= true;
        }
    }

    std::cout << message << '\n';
    std::cout << "Sorted correctly: " << (f ? "True" : "False") << '\n';
    std::cout << "TimSort time: " << t1 << '\n';
    std::cout << "std::sort time: " << t2 << '\n';
    std::cout << '\n';

    delete[] first1;
};

template <class RandomAccessIterator>
void fillRandomIntegers(RandomAccessIterator first1, RandomAccessIterator first2, int mod = (int)1e9) {
    std::minstd_rand0 generator(seed);
    while (first1 < first2)
        *(first1++) = generator() % mod;
};

int* createIntDynamicArray(const size_t &n) {
    int* arr = new int[n];
    return arr;
}

void deleteDynamicArray(int *arr) {
    delete[] arr;
}

void testRandomArrays() {
    const int sizes[] = {1, 2, 5, 10, 25, 50, 100000};
    const int sizesCnt = 7;
    for (int i = 0; i < sizesCnt; ++i) {
        int *arr = createIntDynamicArray(sizes[i]);
        fillRandomIntegers(arr, arr + sizes[i]);
        sortAndCheck(arr, arr + sizes[i], std::less<int>(), "Random Integer Array (" + std::to_string(sizes[i]) + " elements)");
        deleteDynamicArray(arr);
    }
}

void testPartiallySortedArrays() {
    const size_t sizes[] = {20, 40, 80, 128, 1024};
    const size_t cnt1 = 5;
    const size_t numberOfPartisiallySortedArrays[] = {2, 4, 10, 100, 1000, 10000};
    const size_t cnt2 = 6;
    for (size_t i = 0; i < cnt1; ++i) {
        for (size_t j = 0; j < cnt2; ++j) {
            int *arr = createIntDynamicArray(sizes[i] * numberOfPartisiallySortedArrays[j]);
            fillRandomIntegers(arr, arr + sizes[i] * numberOfPartisiallySortedArrays[j]);
            for (size_t z = 0; z < numberOfPartisiallySortedArrays[j]; ++z) {
                std::sort(arr + sizes[i] * (z), arr + sizes[i] * (z + 1));
            }
            sortAndCheck(arr, arr + sizes[i] * numberOfPartisiallySortedArrays[j], std::less<int>(), "Partially Sorted Integer Array ("
                        + std::to_string(numberOfPartisiallySortedArrays[j]) + " blocks of " + std::to_string(sizes[i]) + " elements)");
            deleteDynamicArray(arr);
        }
    }
}

void testStrings() {
    std::minstd_rand0 generator(seed);
    const size_t TRIES = 10;
    for (size_t z = 0; z < TRIES; ++z) {
        const size_t MAXN = (size_t) 1e5;
        std::vector<std::string> arr(MAXN);
        for (size_t i = 0; i < MAXN; ++i) {
            int len = generator() % 10;
            std::string str;
            for (size_t j = 0; j < len; ++j)
                str += (char) (generator() % 80);
            arr[i] = str;
        }
        sortAndCheck(arr.begin(), arr.end(), std::less<std::string>(), std::to_string(MAXN) + " strings");
    }
}

void testAll() {
    testRandomArrays();
    testPartiallySortedArrays();
    testStrings();
}

#endif //TIMSORT_TEST_H
