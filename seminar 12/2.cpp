#include <iostream>
#include <string>
#include <vector>
using namespace std;

int longestSubstring(const string &s){
    int n = s.size();
    int res = 0;

    for (int i = 0; i < n; i++){
        vector<bool> visited(26, false);

        for (int j = i; j < n; j++){
            if (visited[s[j] - 'a'] == true)
                break;
            else
            {
                res = max(res, j - i + 1);
                visited[s[j] - 'a'] = true;
            }
        }
    }
    return res;
}

int main () {
  cout << "Тестирование функции longestSubstring: " << endl;

  cout << "======================================" << endl;

  cout << "Ввод: abcabcbb" << endl;
  cout << "Ожидаемый результат: 3" << endl;
  cout << "Результат выполнения функции: " << longestSubstring("abcabcbb") << endl;

  cout << "======================================" << endl;

  cout << "Ввод: bbbbb" << endl;
  cout << "Ожидаемый результат: 1" << endl;
  cout << "Результат выполнения функции: " << longestSubstring("bbbbb") << endl;

  cout << "======================================" << endl;

  cout << "Ввод: pwwkew" << endl;
  cout << "Ожидаемый результат: 3" << endl;
  cout << "Результат выполнения функции: " << longestSubstring("pwwkew") << endl;
  return 0;
}
