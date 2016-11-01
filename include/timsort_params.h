#ifndef TIMSORT_TIMSORT_PARAMS_H
#define TIMSORT_TIMSORT_PARAMS_H

enum EWhatMerge {
    WM_NoMerge,
    WM_MergeXY,
    WM_MergeYZ
};

struct ITimSortParams {
    virtual size_t minRun(int n) const = 0;
    virtual bool needMerge(size_t lenX, size_t lenY) const = 0;
    virtual EWhatMerge whatMerge(size_t lenX, size_t lenY, size_t lenZ) const = 0;
    virtual size_t getGallop() const = 0;
};

struct IDefaultTimSortParams : public ITimSortParams {
    IDefaultTimSortParams() {}
    ~IDefaultTimSortParams() {}
    virtual size_t minRun(int n) const {
        bool flag = false;
        while (n >= 64) {
            flag |= n & 1;
            n >>= 1;
        }
        return n + flag;
    }
    virtual bool needMerge(size_t lenX, size_t lenY) const {
        return lenY <= lenX;
    }
    virtual EWhatMerge whatMerge(size_t lenX, size_t lenY, size_t lenZ) const {
        if (lenZ > (lenX + lenY) && lenY > lenX)
            return WM_NoMerge;
        if (lenZ <= lenX + lenY)
            return (lenX <= lenZ) ? WM_MergeXY : WM_MergeYZ;
        if (lenY <= lenX)
            return WM_MergeXY;
    }
    virtual size_t getGallop() const {
        return (size_t)7;
    }
};

const IDefaultTimSortParams DefaultTimSortParams;

#endif //TIMSORT_TIMSORT_PARAMS_H
