#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n);
        for (auto& c : connections) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }

        vector<int> disc(n, -1);
        vector<int> low(n, -1);
        vector<vector<int>> result;
        int time = 0;

        dfs(0, -1, graph, disc, low, result, time);

        sort(result.begin(), result.end());
        return result;
    }

private:
    void dfs(int u, int parent, vector<vector<int>>& graph,
             vector<int>& disc, vector<int>& low,
             vector<vector<int>>& result, int& time) {
        disc[u] = low[u] = time++;
        for (int v : graph[u]) {
            if (v == parent) continue;
            if (disc[v] == -1) {
                dfs(v, u, graph, disc, low, result, time);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u]) {
                    result.push_back({u, v});
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
};

void print(const vector<vector<int>>& res) {
    cout << "[";
    for (int i = 0; i < res.size(); ++i) {
        cout << "[" << res[i][0] << "," << res[i][1] << "]";
        if (i + 1 < res.size()) cout << ",";
    }
    cout << "]";
}

int main() {
    cout << "========== Тестирование criticalConnections ==========" << endl << endl;

    Solution sol;

    int n1 = 4;
    vector<vector<int>> conn1 = {{0,1},{1,2},{2,0},{1,3}};
    auto res1 = sol.criticalConnections(n1, conn1);

    cout << "Тест 1: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]" << endl;
    cout << "Ожидаемо: [[1,3]]" << endl;
    cout << "Получено: ";
    print(res1);
    cout << endl << endl;

    int n2 = 2;
    vector<vector<int>> conn2 = {{0,1}};
    auto res2 = sol.criticalConnections(n2, conn2);

    cout << "Тест 2: n = 2, connections = [[0,1]]" << endl;
    cout << "Ожидаемо: [[0,1]]" << endl;
    cout << "Получено: ";
    print(res2);
    cout << endl;

    return 0;
}
