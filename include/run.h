#ifndef TIMSORT_RUN_H
#define TIMSORT_RUN_H

template <class RandomAccessIterator>
class Run {
private:
    RandomAccessIterator begin;
    size_t size;
public:
    Run() : size(0) {}
    Run(RandomAccessIterator begin, RandomAccessIterator end) : begin(begin), size(end - begin) {}
    Run(RandomAccessIterator begin, size_t size) : begin(begin), size(size) {}
    ~Run() {}
    Run& operator =(const Run& another) {
        begin = another.begin;
        size = another.size;
        return *this;
    }
    RandomAccessIterator getBegin() const {
        return begin;
    }
    RandomAccessIterator getEnd() const {
        return begin + size;
    }
    void reverse() const {
        std::reverse(begin, begin + size);
    }
    void setSize(const size_t size) {
        this->size = size;
    }
    size_t getSize() const {
        return size;
    }
};

template <class RandomAccessIterator>
void swapRuns(Run<RandomAccessIterator> first, Run<RandomAccessIterator> second) {
    assert(first.getSize() == second.getSize());
    std::swap_ranges(first.getBegin(), first.getEnd(), second.getBegin());
}

template <class RandomAccessIterator, class Compare>
void inPlaceMergeRuns(Run<RandomAccessIterator> &first, Run<RandomAccessIterator> &second, Compare comp, const ITimSortParams& Params) {
    inPlaceMerge(first.getBegin(), first.getEnd(), second.getEnd(), comp, Params.getGallop());
    first.setSize(first.getSize() + second.getSize());
    second.setSize(0);
}

#endif //TIMSORT_RUN_H
