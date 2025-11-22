#include <iostream>
#include <string>
using namespace std;

string predictFractionToWin(string senate) {
    const int n = senate.length();

    int radiant[20000];
    int dire[20000];

    int r_head = 0, r_tail = 0;
    int d_head = 0, d_tail = 0;

    for (int i = 0; i < n; i++) {
        if (senate[i] == 'R')
            radiant[r_tail++] = i;
        else
            dire[d_tail++] = i;
    }

    while (r_head < r_tail && d_head < d_tail) {
        int r = radiant[r_head++];
        int d = dire[d_head++];

        if (r < d) {
            radiant[r_tail++] = r + n;
        } else {
            dire[d_tail++] = d + n;
        }
    }

    return (r_head < r_tail) ? "Radiant" : "Dire";
}

int main () {
    string test_value_1 = "RD";
    string test_value_2 = "RDD";

    cout << "Тестирование функции predictFractionToWin: " << endl;

    cout << "============== Тест 1 ==============" << endl;
    cout << "Входные данные: " << test_value_1 << endl;
    cout << "Ожидаемый результат: Radiant" << endl;
    cout << "Результат выполнения функции: " << predictFractionToWin(test_value_1) << endl;

    cout << endl;

    cout << "============== Тест 2 ==============" << endl;
    cout << "Входные данные: " << test_value_2 << endl;
    cout << "Ожидаемый результат: Dire" << endl;
    cout << "Результат выполнения функции: " << predictFractionToWin(test_value_2) << endl;

    return 0;
}
