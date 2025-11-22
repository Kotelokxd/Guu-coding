#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int networkDelayTime(vector<vector<int> > &times, int n, int k) {
    vector<vector<pair<int, int> > > adj(n + 1);

    for (const auto &time: times) {
        int u = time[0];
        int v = time[1];
        int w = time[2];
        adj[u].push_back({w, v});
    }

    vector dist(n + 1, INT_MAX);
    dist[k] = 0;

    // Приоритетная очередь для алгоритма Дейкстры
    // Хранит пары: {текущее_время, узел}, сортирует по времени (по возрастанию)
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, k});

    while (!pq.empty()) {
        int currentTime = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        if (currentTime > dist[u]) continue;

        for (const auto &edge: adj[u]) {
            int timeToNeighbor = edge.first;
            int v = edge.second;

            // если путь через u быстрее, обновляем
            if (dist[u] + timeToNeighbor < dist[v]) {
                dist[v] = dist[u] + timeToNeighbor;
                pq.push({dist[v], v});
            }
        }
    }

    int maxTime = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1;
        maxTime = max(maxTime, dist[i]);
    }

    return maxTime;
}

int main() {
    vector<vector<int> > times1 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    cout << "Пример 1: " << networkDelayTime(times1, 4, 2) << endl;

    vector<vector<int> > times2 = {{1, 2, 1}};
    cout << "Пример 2: " << networkDelayTime(times2, 2, 1) << endl;

    vector<vector<int> > times3 = {{1, 2, 1}};
    cout << "Пример 3: " << networkDelayTime(times3, 2, 2) << endl;

    return 0;
}

