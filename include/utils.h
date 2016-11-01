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
void insertionSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    RandomAccessIterator i, j;
    for (i = first + 1; i < last; ++i) {
        j =  i - 1;
        while (j >= first && !comp(*j, *(j + 1))) {
            std::iter_swap(j, j + 1);
            --j;
        }
    }
}

#endif //TIMSORT_UTILS_H