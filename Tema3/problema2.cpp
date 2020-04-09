#include "BST.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<string> v1 = {
        "GAZIL","THMLT","ZAYMX","EMMHM","YWDQS",
        "FIDEU","TWSBX","AHBIM","WZTAJ","VBWUS",
        "NWAYO","CTENR","HMWEB","YABDD","TSTRZ",
        "ROFCJ","OTSZF","RNVAK","YMHBY","ORODR"
    };
    ASD::BST<string> bst1(v1);
    cout << bst1;

    vector<int> v2 = {5, 7, 2, 8, 9, 11, 4, 6, 3};
    ASD::BST<int> bst2(v2);
    cout << bst2;
    cout << bst2.exists(7) << " " << bst2.exists(3) << " " << bst2.exists(5) << " " << bst2.exists(999) << endl;
    auto range = bst2.rangeQuery(8, 15);
    for (auto it: range) {
        cout << it << " ";
    }
    cout << endl;
    bst2.remove(5);
    cout << bst2;
    bst2.remove(7);
    cout << bst2;
    bst2.remove(3);
    cout << bst2;
    bst2.remove(9);
    cout << bst2;

    return 0;
}