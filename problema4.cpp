#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int directionX[] = {1, -1, 0, 0};
const int directionY[] = {0, 0, 1, -1};

struct Point;
using Ranking = map<Point, int>;
using Roots = map<Point, Point>;

struct Point {
    int x, y;

    bool operator<(const Point& rhs) const {
        if (x == rhs.x) {
            return y < rhs.y;
        }
        return x < rhs.x;
    }

    bool operator==(const Point& rhs) const {
        return x == rhs.x and y == rhs.y;
    }

    bool operator!=(const Point& rhs) const {
        return !(*this == rhs);
    }

    Point& operator=(const Point& rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        
        return *this;
    }

    bool isValid(const int n, Ranking& ranks) {
        return x <= n and y <= n && x > 0 and y > 0 && ranks[*this] != 0;
    }
};

Point findRoot(Point p, Roots& roots) {
    Point R;
    for (R = p; R != roots[R]; R = roots[R]) ;
 
    Point y = p;
    Point tmp;
    while (y != roots[y]) {
        tmp = roots[y];
        roots[y] = R;
        y = tmp;
    }
 
    return R;
}


void pointPrint(const Point& p) {
    cout << p.x << " " << p.y << " ";
}

void unite(Point lhs, Point rhs, Roots& roots, Ranking& ranks) {
    lhs = findRoot(lhs, roots);
    rhs = findRoot(rhs, roots);
 
    if (ranks[lhs] > ranks[rhs]) {
        roots[rhs] = lhs;
        ranks[lhs] += ranks[rhs];
    } else {
        roots[lhs] = rhs;
        ranks[rhs] += ranks[rhs];
    }
}

void addNeighbours(const Point& p, const int size, Roots& roots, Ranking& ranks) {
    for (int i = 0; i < 4; i++) {
        Point newPoint;
        newPoint.x = p.x + directionX[i];
        newPoint.y = p.y + directionY[i];

        if (newPoint.isValid(size, ranks)) {
            unite(p, newPoint, roots, ranks);
        }
    }
}

void solve(vector<Point> points) {
    Roots roots;
    Ranking ranks;
    int size = points.size();

    for (auto point: points) {
        roots[point] = point;
        ranks[point] = 1;
    }

    for (auto point: points) {
        addNeighbours(point, size, roots, ranks);
    }

    map<Point, vector<Point>> solution;
    for (auto point: points) {
        auto root = findRoot(point, roots);
        solution[root].push_back(point);
    }

    int i = 1;
    for (auto it: solution) {
        cout << i << " : "; 
        for (auto point: it.second) {
            pointPrint(point); cout << ", ";
        }
        i++;
        cout << endl;
    }
}

int main() {
    solve({
        {1, 3},
        {2, 3},
        {2, 4},
        {4, 5},
        {5, 4},
        {5, 5},
        {6, 2},
        {6, 5},
        {6, 7},
        {6, 1},
        {6, 2},
        {6, 3},
        {6, 7},
        {7, 1},
        {7, 2},
        {7, 3},
        {7, 6},
        {7, 7},
    });

    return 0;
}