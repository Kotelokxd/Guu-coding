#include <iostream>
#include <stdexcept>
using namespace std;

template<typename... Args>
auto average(Args&&... args) {
    if constexpr (sizeof...(args) == 0) {
        throw runtime_error("Ошибка. Получено 0 аргументов");
    }

    return (args + ...) / sizeof...(args);
}

int main() {
    cout << "Тестирование функции average" << endl << endl;

    cout << "========== Тест 1 ==========" << endl;
    cout << "Входные данные: 1, 2, 3" << endl;
    cout << "Ожидаемый результат: 2" << endl;
    cout << "Результат выполнения average: " << average(1, 2, 3) << endl;

    cout << "========== Тест 2 ==========" << endl;
    cout << "Входные данные: 4, 5, 6, 7, 8" << endl;
    cout << "Ожидаемый результат: 6" << endl;
    cout << "Результат выполнения average: " << average(4, 5, 6, 7, 8) << endl;

    return 0;
}
