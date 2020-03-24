#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;

// This is already defined in <functional> in C++20 :(
template <typename T>
struct identity {
    T operator()(T t) const { 
        return t; 
    }
};

template <typename T, typename IndexFunctionType = identity<T>>
void countSortInternal(vector<T>& v, IndexFunctionType IndexFunction) {
    if (v.size() == 0) return ;

    T minValue = accumulate(v.begin(), v.end(), IndexFunction(*v.begin()), [&](T minValue, T curr) { return min(minValue, IndexFunction(curr)); });
    T maxValue = accumulate(v.begin(), v.end(), IndexFunction(*v.begin()), [&](T maxValue, T curr) { return max(maxValue, IndexFunction(curr)); });

    size_t range = maxValue - minValue + 1;
    vector<T> count(range), copyV(v);

    for (auto it: v) {
        count[IndexFunction(it) - minValue]++;
    }

    for (size_t i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    for (auto it = copyV.rbegin(); it != copyV.rend(); ++it) {
        v[count[IndexFunction(*it) - minValue] - 1] = *it;
        count[IndexFunction(*it) - minValue]--;
    }
}

template <typename T, typename IndexFunctionType = identity<T>>
void countSort(vector<T>& v) {
    IndexFunctionType IndexFunction;
    countSortInternal(v, IndexFunction);
}

template <typename T, typename IndexFunctionType = identity<T>>
void countSort(vector<T>& v, IndexFunctionType IndexFunction) {
    countSortInternal(v, IndexFunction);
}

template <typename T>
struct Divide {
    T initialDenominator;
    T denominator;
    Divide(T denominator): denominator(1), initialDenominator(denominator) {}

    T operator()(T elem) const {
        return (elem / denominator) % initialDenominator;
    }

    Divide& operator++()
    {
        denominator *= initialDenominator;
        return *this;
    }
};

template <typename T>
struct BitShift {
    size_t initialShifter;
    size_t shifter;
    size_t mask;
    BitShift(size_t shifter): shifter(0), initialShifter(shifter), mask((1ULL << (shifter + 1)) - 1) {}

    T operator()(T elem) const {
        return (elem >> shifter) & mask;
    }

    BitShift& operator++() {
        shifter += initialShifter;
        mask = (1ULL << (shifter + 1)) - 1;
        return *this;
    }
};

template <typename T, typename RadixCriteriaType = Divide<T>>
void radixSort(vector<T>& v, RadixCriteriaType RadixCriteria) {
    for (
        T maxValue = *max_element(v.begin(), v.end());
        RadixCriteria(maxValue) != 0;
        ++RadixCriteria
        ) {
        
        countSort<T, RadixCriteriaType>(v, RadixCriteria);
    }
}

int main() {
    vector<int> v1({716522, 786842, 62364, 580837, 992525, 494088, 967101, 328380, 531035, 67505});
    countSort<int>(v1);
    for (auto it: v1) {
        cout << it << " ";
    }
    cout << endl;

    vector<int> v2({716522, 786842, 62364, 580837, 992525, 494088, 967101, 328380, 531035, 67505});;
    radixSort<int, Divide<int>>(v2, Divide<int>(10));
    for (auto it: v2) {
        cout << it << " ";
    }
    cout << endl;

    vector<int> v3({716522, 786842, 62364, 580837, 992525, 494088, 967101, 328380, 531035, 67505});
    radixSort<int, BitShift<int>>(v3, BitShift<int>(8));
    for (auto it: v3) {
        cout << it << " ";
    }
    cout << endl;

    return 0;
}