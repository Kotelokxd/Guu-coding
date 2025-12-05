#include <iostream>
#include <vector>
using namespace std;

int getMinKnightHP (const vector<vector<int>>& dungeon) {
    int m = dungeon.size();
    int n = dungeon[0].size();

    vector<vector<int>> minHPForTile(m, vector<int>(n));

    minHPForTile[m-1][n-1] = (dungeon[m-1][n-1] >= 0 ? 1 : 1 - dungeon[m-1][n-1]);

    for (int j = n - 1; j >= 0; j --) {
        int needHP = minHPForTile[m - 1][j] - dungeon[m - 1][j - 1];
        minHPForTile[m - 1][j - 1] = max(1, needHP);
    }

    for (int i = m - 2; i >= 0; --i) {
        int need = minHPForTile[i+1][n-1] - dungeon[i][n-1];
        minHPForTile[i][n-1] = max(1, need);
    }

    for (int i = m - 2; i >= 0; --i) {
        for (int j = n - 2; j >= 0; --j) {
            int min_next = min(minHPForTile[i+1][j], minHPForTile[i][j+1]);
            int need = min_next - dungeon[i][j];
            minHPForTile[i][j] = max(1, need);
        }
    }

    return minHPForTile[0][0];
}

int main () {
    const vector<vector<int>> dungeon {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};

    cout << "========== Тестирование функции getMinKnightHP ==========" << endl << endl;

    cout << "Входные данные: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]" << endl;
    cout << "Ожидаемый результат: 7" << endl;
    cout << "Результат выполнения функции: " << getMinKnightHP(dungeon);

    return 0;
}