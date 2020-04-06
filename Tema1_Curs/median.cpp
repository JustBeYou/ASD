// Example program
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

typedef unsigned int uint;
const uint max_n = 100005;

struct range_t {
    uint left, right, size;
};

typedef pair<range_t, range_t> query_t;
istream& operator>>(istream& in, query_t& q) {
    in >> q.first.left >> q.first.right >> q.second.left >> q.second.right;
    q.first.size = q.first.right - q.first.left + 1;
    q.second.size = q.second.right - q.second.left + 1;
    return in;
}

ostream& operator<<(ostream& out, const query_t& q) {
    out << q.first.left << " " << q.first.right << " " << q.second.left << " " << q.second.right << endl;
    return out;
}

uint query_range(const vector<uint>& A, const vector<uint>& B, query_t& q, const uint mid) {
    if (q.first.size == 0) return B[q.second.left + mid];
    if (q.second.size == 0) return A[q.first.left + mid];
    if (mid == 0) return min(A[q.first.left], B[q.second.left]);

    uint half = (mid + 1) / 2;
    if (q.first.size < half or 
        (q.second.size >= half and A[q.first.left + half - 1] > B[q.second.left + half - 1])) {

        q.second.left += half;
        q.second.size -= half;
    } else {
        q.first.left += half;
        q.first.size -= half;
    }

    return query_range(A, B, q, mid / 2);
}

void solve(istream& in, ostream& out) {
    uint T;
    in >> T;
    vector<uint> A, B;
    A.resize(max_n);
    B.resize(max_n);
    
    while(T--) {
        uint n, m, q;
        in >> n >> m >> q;
        
        for (uint i = 0; i < n; i++) in >> A[i];
        for (uint i = 0; i < m; i++) in >> B[i];
        while (q--) {
            query_t query;
            in >> query;
            uint mid = (query.first.size + query.second.size - 1) / 2;

            out << query_range(A, B, query, mid) << endl;
        }
    }
}

int main()
{
    ifstream in("input.txt");
    //ifstream in("mediana.in");
    //ofstream out("mediana.out");
    solve(in, cout);
}
