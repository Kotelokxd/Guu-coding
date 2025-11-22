#include <vector>
#include <map>
#include <iostream>

using namespace std;

int getMinBusAmount(vector<vector<int>>& routes, int source, int target) {
    if (source == target) return 0;
    
    map<int, vector<int>> stopToRoutes;
    for (int i = 0; i < routes.size(); i++) {
        for (int j = 0; j < routes[i].size(); j++) {
            int stop = routes[i][j];
            stopToRoutes[stop].push_back(i);
        }
    }
    
    vector<bool> visitedRoute(routes.size(), false);
    
    vector<int> currentLevel;
    
    if (stopToRoutes.find(source) != stopToRoutes.end()) {
        vector<int>& sourceRoutes = stopToRoutes[source];
        for (int i = 0; i < sourceRoutes.size(); i++) {
            int route = sourceRoutes[i];
            currentLevel.push_back(route);
            visitedRoute[route] = true;
        }
    }
    
    int busCount = 1;
    
    while (!currentLevel.empty()) {
        vector<int> nextLevel;
        
        for (int i = 0; i < currentLevel.size(); i++) {
            int route = currentLevel[i];
            
            for (int j = 0; j < routes[route].size(); j++) {
                int stop = routes[route][j];
                
                if (stop == target) {
                    return busCount;
                }
                
                if (stopToRoutes.find(stop) != stopToRoutes.end()) {
                    vector<int>& nextRoutes = stopToRoutes[stop];
                    for (int k = 0; k < nextRoutes.size(); k++) {
                        int nextRoute = nextRoutes[k];
                        if (!visitedRoute[nextRoute]) {
                            visitedRoute[nextRoute] = true;
                            nextLevel.push_back(nextRoute);
                        }
                    }
                }
            }
        }
        
        currentLevel = nextLevel;
        busCount++;
    }
    
    return -1;
}

int main() {
    cout << "Тестирование функции getMinBusAmount: " << endl;

    cout << "======================================" << endl;

    vector<vector<int>> routes1 = {{1,2,7}, {3,6,7}};
    cout << "Ввод: routes = [[1,2,7],[3,6,7]], source = 1, target = 6 " << endl;
    cout << "Ожидаемый результат: 2" << endl;
    cout << "Результат выполнения функции: " << getMinBusAmount(routes1, 1, 6) << endl;

    cout << "======================================" << endl;

    vector<vector<int>> routes2 = {{7,12},{4,5,15},{6},{15,19},{9,12,13}};
    cout << "Ввод: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12 " << endl;
    cout << "Ожидаемый результат: -1" << endl;
    cout << "Результат выполнения функции: " << getMinBusAmount(routes2, 15,12 ) << endl;

    return 0;
}
