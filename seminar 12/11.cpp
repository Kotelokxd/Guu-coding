#include <iostream>
#include <vector>
#include <map>
using namespace std;

int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int i, int j, vector<vector<int>>& grid, int m, int n, 
         int& perimeter, map<pair<int, int>, bool>& threatCells, int& compId) {
    grid[i][j] = compId;

    for (int d = 0; d < 4; d++) {
        int ni = i + dirs[d][0];
        int nj = j + dirs[d][1];
        if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
            if (grid[ni][nj] == 0) {
                threatCells[make_pair(ni, nj)] = true;
                perimeter++;
            } else if (grid[ni][nj] == 1) {
                dfs(ni, nj, grid, m, n, perimeter, threatCells, compId);
            }
        }
    }
}

void spreadVirus(vector<vector<int>>& grid, int m, int n) {
    vector<vector<int>> newGrid = grid;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                for (int d = 0; d < 4; d++) {
                    int ni = i + dirs[d][0];
                    int nj = j + dirs[d][1];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 0) {
                        newGrid[ni][nj] = 1;
                    }
                }
            }
        }
    }
    grid = newGrid;
}

void isolateRegion(int i, int j, vector<vector<int>>& grid, int m, int n) {
    grid[i][j] = -1;
    for (int d = 0; d < 4; d++) {
        int ni = i + dirs[d][0];
        int nj = j + dirs[d][1];
        if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 1) {
            isolateRegion(ni, nj, grid, m, n);
        }
    }
}

int containVirus(vector<vector<int>>& isInfected) {
    int m = isInfected.size();
    int n = isInfected[0].size();
    int totalWalls = 0;
    
    while (true) {
        vector<int> perimeters;
        vector<map<pair<int, int>, bool>> threats;
        int compId = 2;
        
        vector<vector<int>> tempGrid = isInfected;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (tempGrid[i][j] == 1) {
                    int perimeter = 0;
                    map<pair<int, int>, bool> threatCells;
                    dfs(i, j, tempGrid, m, n, perimeter, threatCells, compId);
                    compId++;
                    
                    if (threatCells.size() > 0) {
                        perimeters.push_back(perimeter);
                        threats.push_back(threatCells);
                    }
                }
            }
        }
        
        if (threats.empty()) break;
        
        int maxThreatIndex = 0;
        for (int i = 1; i < threats.size(); i++) {
            if (threats[i].size() > threats[maxThreatIndex].size()) {
                maxThreatIndex = i;
            }
        }
        
        totalWalls += perimeters[maxThreatIndex];
        
        bool found = false;
        for (int i = 0; i < m && !found; i++) {
            for (int j = 0; j < n && !found; j++) {
                if (isInfected[i][j] == 1) {
                    int perimeter = 0;
                    map<pair<int, int>, bool> threatCells;
                    int dummyId = 100;
                    vector<vector<int>> testGrid = isInfected;
                    dfs(i, j, testGrid, m, n, perimeter, threatCells, dummyId);
                    
                    if (threatCells.size() == threats[maxThreatIndex].size()) {
                        isolateRegion(i, j, isInfected, m, n);
                        found = true;
                    }
                }
            }
        }
        
        spreadVirus(isInfected, m, n);
    }
    
    return totalWalls;
}

int main() {
    vector<vector<int>> grid1 = {
        {0,1,0,0,0,0,0,1},
        {0,1,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0}
    };

    vector<vector<int>> grid2 = {
        {1,1,1},
        {1,0,1},
        {1,1,1}
    };

    vector<vector<int>> grid3 = {
        {1,1,1,0,0,0,0,0,0},
        {1,0,1,0,1,1,1,1,1},
        {1,1,1,0,0,0,0,0,0}
    };

    cout << "Тестирование функции containVirus: " << endl;

    cout << "======================================" << endl;

    cout << "Ввод: [[1,1,1,0,0,0,0,0,0], [1,0,1,0,1,1,1,1,1], [1,1,1,0,0,0,0,0,0]]" << endl;
    cout << "Ожидаемый результат: 10" << endl;
    cout << "Результат выполнения функции: " << containVirus(grid1) << endl;

    cout << "======================================" << endl;

    cout << "Ввод: [[1,1,1],[1,0,1],[1,1,1]]" << endl;
    cout << "Ожидаемый результат: 4" << endl;
    cout << "Результат выполнения функции: " << containVirus(grid2) << endl;

    cout << "======================================" << endl;

    cout << "Ввод: [[1,1,1,0,0,0,0,0,0], [1,0,1,0,1,1,1,1,1], [1,1,1,0,0,0,0,0,0]] " << endl;
    cout << "Ожидаемый результат: 13" << endl;
    cout << "Результат выполнения функции: " << containVirus(grid3) << endl;

    return 0;
}
