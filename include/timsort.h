#ifndef TIMSORT_TIMSORT_H
#define TIMSORT_TIMSORT_H

#include <vector>
#include <algorithm>
#include <cmath>

#include "utils.h"
#include "inplace_merge.h"
#include "timsort_params.h"
#include "run.h"

template<class RandomAccessIterator, class Compare>
void sortRuns(const RandomAccessIterator &first, const RandomAccessIterator &last, const size_t &blockSize, Compare comp) {
    RandomAccessIterator i, j, min;
    for (i = first; i + blockSize != last; i += blockSize) {
        min = i;
        for (j = i + blockSize; j != last; j += blockSize)
            if (comp(*j, *min) || (!comp(*j, *min) && !comp(*min, *j) && !comp(*(j + blockSize), *(min + blockSize))))
                min = j;
        swapRuns(Run<RandomAccessIterator>(i, blockSize), Run<RandomAccessIterator>(min, blockSize));
    }
}

template <class RandomAccessIterator, class Compare>
void tryToMergeRuns(std::vector<Run<RandomAccessIterator>> &runs, Compare comp, const ITimSortParams& Params) {

    Run<RandomAccessIterator> X, Y, Z;
    EWhatMerge WhatMerge;

    X = pop(runs);
    Y = pop(runs);
    while (!runs.empty()) {
        Z = pop(runs);
        WhatMerge = Params.whatMerge(X.getSize(), Y.getSize(), Z.getSize());
        if (WhatMerge == WM_MergeXY) {
            inPlaceMergeRuns(Y, X, comp, Params);
            X = Y;
            Y = Z;
        } else if (WhatMerge == WM_MergeYZ) {
            inPlaceMergeRuns(Z, Y, comp, Params);
            Y = Z;
        } else if (WhatMerge == WM_NoMerge) {
            runs.push_back(Z);
            break;
        }
    }

    if (Params.needMerge(X.getSize(), Y.getSize())) {
        inPlaceMergeRuns(Y, X, comp, Params);
        runs.push_back(Y);
    } else {
        runs.push_back(Y);
        runs.push_back(X);
    }

}

template <class RandomAccessIterator, class Compare>
void calcRuns(std::vector<Run<RandomAccessIterator>> &runs, const RandomAccessIterator &first, const RandomAccessIterator &last, Compare comp, const ITimSortParams& Params) {
    size_t minRunLength = Params.minRun(last - first);
    for (RandomAccessIterator it = first; it != last; ) {
        size_t runLength = 1;
        RandomAccessIterator runBegin = it;
        bool less = (it + 1 != last && comp(*it, *(it + 1)));
        while (it != last - 1 && (comp(*it, *(it + 1)) ^ !less))
            ++runLength, ++it;
        ++it;
        if (!less)
            std::reverse(runBegin, it);
        if (runLength <= minRunLength) {
            //RandomAccessIterator sortBegin = it;
            while (it != last && it != (runBegin + minRunLength))
                ++runLength, ++it;
            insertionSort(runBegin, it, comp);
        }
        runs.push_back(Run<RandomAccessIterator>(runBegin, runLength));
        if (runs.size() > 1)
            tryToMergeRuns(runs, comp, Params);
    }

    Run<RandomAccessIterator> X, Y;
    while (runs.size() > 1) {
        X = pop(runs);
        Y = pop(runs);
        inPlaceMergeRuns(Y, X, comp, Params);
        runs.push_back(Y);
    }
}

template <class RandomAccessIterator, class Compare>
void timSort(const RandomAccessIterator &first, const RandomAccessIterator &last, Compare comp, const ITimSortParams &Params = DefaultTimSortParams) {
    std::vector<Run<RandomAccessIterator>> runs;
    calcRuns(runs, first, last, comp, Params);
}

template <class RandomAccessIterator>
void timSort(RandomAccessIterator first, RandomAccessIterator last, const ITimSortParams &Params = DefaultTimSortParams) {
    timSort(first, last, std::less<class std::iterator_traits<RandomAccessIterator>::value_type>(), Params);
}

#endif //TIMSORT_TIMSORT_H
