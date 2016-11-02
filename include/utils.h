#ifndef TIMSORT_UTILS_H
#define TIMSORT_UTILS_H

template <class T>
T pop(std::vector<T> &arr) {
    T val = arr.back();
    arr.pop_back();
    return val;
}

size_t sizeAbs(const size_t &x) {
    return x > 0 ? x : -x;
}

size_t roundUp(size_t a, size_t b) {
    return a / b + (a % b ? 1 : 0);
}

template <class RandomAccessIterator, class Compare>
void insertionSort(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator sortBegin, Compare comp) {
    RandomAccessIterator i, j, x;
    for (i = sortBegin; i != last; ++i) {
        x = std::upper_bound(first, i, *i, comp);
        j = i;
        while (j != x) {
            std::iter_swap(j - 1, j);
            --j;
        }
    }
}

#endif //TIMSORT_UTILS_H