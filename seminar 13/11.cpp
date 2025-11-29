#include <iostream>
using namespace std;

template<typename... Args> auto product(Args&&... args) {
    return (args * ...);
}

int main() {
    cout << "Тестирование функции product" << endl;

    cout << "========== Тест 1 ==========" << endl;
    cout << "Входные данные: 1, 2, 3" << endl;
    cout << "Ожидаемый результат: 6" << endl;
    cout << "Результат выполнения average: " << product(1, 2, 3) << endl;

    cout << "========== Тест 2 ==========" << endl;
    cout << "Входные данные: 4, 5, 6, 7, 8" << endl;
    cout << "Ожидаемый результат: 6720" << endl;
    cout << "Результат выполнения average: " << product(4, 5, 6, 7, 8) << endl;

    return 0;
}
