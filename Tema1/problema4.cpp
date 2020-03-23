#include <iostream>
#include <map>
#include <vector>
#include <fstream>

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

void solve(vector<Point>& points, vector<vector<char>>& matrix) {
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
        for (auto point: it.second) {
            matrix[point.x][point.y] = i + '0';
        }
        i++;
    }
}

int main() {
    ifstream in("problema4.in");
    int n;
    vector<Point> points;

    in >> n;
    vector<vector<char>> matrix(n + 1);

    for (int i = 1; i <= n; i++) {
        matrix[i].push_back('#'); // useless spot
        for (int j = 1; j <= n; j++) {
            char c;
            in >> c;
            matrix[i].push_back(c);
            if (matrix[i][j] == '1') {
                points.push_back({i, j});
            }
        }
    }
    
    solve(points, matrix);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}