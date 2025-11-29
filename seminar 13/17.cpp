#include <iostream>
using namespace std;

template<typename T, typename U, typename... Rest> constexpr bool areSameType() {
    if constexpr (sizeof...(Rest) == 0) {
        return __is_same(T, U);
    } else {
        return __is_same(T, U) && areSameType<T, Rest...>();
    }
}

template<typename T> constexpr bool areSameType() {
    return true;
}

constexpr bool areSameType() {
    return true;
}

int main () {
    cout << "Тестирование функции areSameType" << endl;

    cout << "========== Тест 1 ==========" << endl;
    cout << "Сравнение int и int" << endl;
    cout << "Результат: " << areSameType<int, int>();

    cout << "========== Тест 2 ==========" << endl;
    cout << "Сравнение double и double и int" << endl;
    cout << "Результат: " << areSameType<double, double, int>();
    return 0;
}
