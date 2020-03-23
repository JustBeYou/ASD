#include <vector>
#include <iostream>

using namespace std;

struct solution {
    bool exists;
    int candidate;
};

solution solve(vector<int> v) {
    solution sol = {false, 0};
    int count = 0;

    for (auto elem: v) {
        if (count == 0) {
            sol.candidate = elem;
            count = 1;
        } else if (elem == sol.candidate) {
            count++;
        } else {
            count--;
        }
    }

    count = 0;
    for (auto elem: v) {
        if (elem == sol.candidate) {
            count++;
        }
    }

    if (count > v.size() / 2) {
        sol.exists = true;
    }

    return sol;
}

void solver(vector<int> v) {
    auto sol = solve(v);

    if (sol.exists) {
        cout << sol.candidate << endl;
    } else {
        cout << "Does not exists" << endl;
    }
}

int main() {
    solver({1, 1, 1, 2, 3});
    solver({1, 2, 3});
    solver({3, 4, 4, 3, 3, 2, 3});
}