#include <iostream>
#include <vector>
using namespace std;

int getMinCandies (vector<int> ratings) {
  const int n = ratings.size();

  vector<int> candies(n, 1);

  for (int i = 1; i < n; i ++) {
    if (ratings[i] > ratings[i - 1]) {
      candies[i] = candies[i - 1] + 1;
    }
  }

  for (int i = n - 2; i >= 0; i --) {
    if (ratings[i] > ratings[i + 1]) {
      candies[i] = max(candies[i], candies[i + 1] + 1);
    }
  }

  int candiesAmount = 0;
  for (int i = 0; i < n; i ++) {
    candiesAmount += candies[i];
  }

  return candiesAmount;
}

int main () {
  const vector<int> ratings1{1, 0, 2};
  const vector<int> ratings2{1, 2, 2};

  cout << "========== Тестирование функции getMinCandies ==========" << endl << endl;

  cout << "Входные данные: ratings = [1,0,2]" << endl;
  cout << "Ожидаемый результат: 5" << endl;
  cout << "Результат выполнения функции: " << getMinCandies(ratings1) << endl << endl;

  cout << "Входные данные: ratings = [1,2,2]" << endl;
  cout << "Ожидаемый результат: 4" << endl;
  cout << "Результат выполнения функции: " << getMinCandies(ratings2) << endl << endl;

  return 0;
}
