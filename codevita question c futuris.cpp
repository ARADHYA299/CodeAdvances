#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>

using namespace std;

struct Point {
    int row, col;
    Point(int r = 0, int c = 0) : row(r), col(c) {}
    bool operator<(const Point& other) const {
        if (row != other.row) return row < other.row;
        return col < other.col;
    }
    bool operator==(const Point& other) const {
        return row == other.row && col == other.col;
    }
};

int rows, cols;
vector<string> grid;
vector<Point> cablePath;
vector<Point> rodPath;
set<Point> cableSet, rodSet;

// Find cable path using BFS
void traceCablePath() {
    // Find cable endpoints (on edges)
    Point start(-1, -1);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'C') {
                cableSet.insert(Point(i, j));
                // Check if on edge
                if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                    if (start.row == -1) {
                        start = Point(i, j);
                    }
                }
            }
        }
    }
    
    // Trace cable path from start
    if (start.row == -1) return;
    
    set<Point> visited;
    Point current = start;
    visited.insert(current);
    cablePath.push_back(current);
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (true) {
        bool found = false;
        for (int d = 0; d < 4; d++) {
            int nr = current.row + dx[d];
            int nc = current.col + dy[d];
            
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                Point next(nr, nc);
                if (grid[nr][nc] == 'C' && visited.find(next) == visited.end()) {
                    visited.insert(next);
                    cablePath.push_back(next);
                    current = next;
                    found = true;
                    break;
                }
            }
        }
        if (!found) break;
    }
}

// Find rod path
void traceRodPath() {
    // Find rod endpoints (on edges)
    Point start(-1, -1);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'R') {
                rodSet.insert(Point(i, j));
                // Check if on edge
                if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                    if (start.row == -1) {
                        start = Point(i, j);
                    }
                }
            }
        }
    }
    
    // Trace rod path
    if (start.row == -1) return;
    
    set<Point> visited;
    Point current = start;
    visited.insert(current);
    rodPath.push_back(current);
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (true) {
        bool found = false;
        for (int d = 0; d < 4; d++) {
            int nr = current.row + dx[d];
            int nc = current.col + dy[d];
            
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                Point next(nr, nc);
                if (grid[nr][nc] == 'R' && visited.find(next) == visited.end()) {
                    visited.insert(next);
                    rodPath.push_back(next);
                    current = next;
                    found = true;
                    break;
                }
            }
        }
        if (!found) break;
    }
}

// Calculate winding number to determine if cable wraps around rod
int calculateWindingNumber() {
    if (cablePath.empty() || rodPath.empty()) return 0;
    
    vector<Point> intersections;
    
    // Find all intersection points
    for (const Point& cp : cablePath) {
        if (rodSet.find(cp) != rodSet.end()) {
            intersections.push_back(cp);
        }
    }
    
    if (intersections.empty()) return 0;
    
    // Calculate signed crossings
    int windingNum = 0;
    
    for (size_t i = 0; i < intersections.size(); i++) {
        Point inter = intersections[i];
        
        // Find cable direction at intersection
        int cableIdx = -1;
        for (size_t j = 0; j < cablePath.size(); j++) {
            if (cablePath[j] == inter) {
                cableIdx = j;
                break;
            }
        }
        
        if (cableIdx == -1 || cableIdx == 0 || cableIdx == (int)cablePath.size() - 1) continue;
        
        Point cablePrev = cablePath[cableIdx - 1];
        Point cableNext = cablePath[cableIdx + 1];
        
        // Find rod direction at intersection
        int rodIdx = -1;
        for (size_t j = 0; j < rodPath.size(); j++) {
            if (rodPath[j] == inter) {
                rodIdx = j;
                break;
            }
        }
        
        if (rodIdx == -1 || rodIdx == 0 || rodIdx == (int)rodPath.size() - 1) continue;
        
        Point rodPrev = rodPath[rodIdx - 1];
        Point rodNext = rodPath[rodIdx + 1];
        
        // Determine cable direction
        int cableDir = 0; // 0=horizontal, 1=vertical
        if (cablePrev.row != cableNext.row) cableDir = 1;
        
        // Determine rod direction
        int rodDir = 0;
        if (rodPrev.row != rodNext.row) rodDir = 1;
        
        // If perpendicular crossing
        if (cableDir != rodDir) {
            // Determine crossing direction
            if (cableDir == 0) { // Cable horizontal, rod vertical
                if (cableNext.col > cablePrev.col && rodNext.row > rodPrev.row) {
                    windingNum++;
                } else if (cableNext.col < cablePrev.col && rodNext.row < rodPrev.row) {
                    windingNum++;
                } else {
                    windingNum--;
                }
            } else { // Cable vertical, rod horizontal
                if (cableNext.row > cablePrev.row && rodNext.col < rodPrev.col) {
                    windingNum++;
                } else if (cableNext.row < cablePrev.row && rodNext.col > rodPrev.col) {
                    windingNum++;
                } else {
                    windingNum--;
                }
            }
        }
    }
    
    return abs(windingNum);
}

int main() {
    cin >> rows >> cols;
    cin.ignore();
    
    grid.resize(rows);
    
    for (int i = 0; i < rows; i++) {
        string line;
        getline(cin, line);
        
        string processed = "";
        for (char c : line) {
            if (c != ' ') {
                processed += c;
            }
        }
        grid[i] = processed;
    }
    
    traceCablePath();
    traceRodPath();
    
    int result = calculateWindingNumber();
    
    cout << result << endl;
    
    return 0;
}