#include <iostream>
#include <vector>
using namespace std;

int getWaterDropsAmount(vector<int> heights) {
    int n = heights.size();
    if (n <= 2) return 0;

    int waterDrops = 0;

    for (int i = 1; i < n - 1; i++) {
        int leftMax = 0;
        int rightMax = 0;

        for (int j = 0; j < i; j++) {
            leftMax = max(leftMax, heights[j]);
        }

        for (int j = i + 1; j < n; j++) {
            rightMax = max(rightMax, heights[j]);
        }

        int minHeight = min(leftMax, rightMax);

        if (minHeight > heights[i]) {
            waterDrops += minHeight - heights[i];
        }
    }

    return waterDrops;
}

int main () {
  cout << "Тестирование функции getWaterDropsAmount: " << endl;

  cout << "======================================" << endl;

  cout << "Ввод: [0,1,0,2,1,0,1,3,2,1,2,1]" << endl;
  cout << "Ожидаемый результат: 6" << endl;
  cout << "Результат выполнения функции: " << getWaterDropsAmount({0,1,0,2,1,0,1,3,2,1,2,1}) << endl;

  cout << "======================================" << endl;

  cout << "Ввод: [4,2,0,3,2,5]" << endl;
  cout << "Ожидаемый результат: 9" << endl;
  cout << "Результат выполнения функции: " << getWaterDropsAmount({4,2,0,3,2,5}) << endl;

  return 0;
}