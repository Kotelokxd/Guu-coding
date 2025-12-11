#include <iostream>
#include <concepts>

using namespace std; 

const double PI = 3.1415926;

template<typename T>
concept FloatApplicable = floating_point<T>;

constexpr auto factorial = [](unsigned n) constexpr {
    unsigned long long res = 1;
    for (unsigned i = 2; i <= n; i++) res *= i;
    return res;
};

template<FloatApplicable T>
constexpr auto sin_taylor = [](T x) constexpr {
    T sum = 0;
    T term = x;
    T x2 = x * x;

    for (int k = 0; k < 10; ++k) {
        sum += term;
        term *= -x2 / ((2*k + 2) * (2*k + 3));
    }

    return sum;
};

int main() {
    cout << "======== Тестирование функции sin_taylor ========" << endl << endl;
    
    cout << "Входные данные: PI / 2" << endl;
    cout << "Ожидаемый результат: 1" << endl;
    cout << "Результат выполнения функции: "<< sin_taylor<double>(PI / 2) << endl << endl;
    
    cout << "Входные данные: PI / 4" << endl;
    cout << "Ожидаемый результат: " << sqrt(2) / 2 << endl;
    cout << "Результат выполнения функции: "<< sin_taylor<double>(PI / 4) << endl << endl;

    cout << "Входные данные: 0" << endl;
    cout << "Ожидаемый результат: 0" << endl;
    cout << "Результат выполнения функции: "<< sin_taylor<double>(0) << endl << endl;
}
