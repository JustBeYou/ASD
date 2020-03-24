#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <utility>

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

int main() {
    vector<int> v({3, 5, -1, 7, 11, -24});
    countSort<int>(v);
    for (auto it: v) {
        cout << it << " ";
    }
    cout << endl;

    return 0;
}