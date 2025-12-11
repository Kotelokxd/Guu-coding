#include <array>
#include <iostream>

using namespace std;

auto generate_sequence = []<typename T = int, int N, T Start = 0, T Step = 1>() constexpr -> array<T, N> {
    array<T, N> arr{};
    T current = Start;
    for (int i = 0; i < N; ++i) {
        arr[i] = current;
        current += Step;
    }
    return arr;
};

int main() {
    constexpr int size = 10;
    constexpr int startFrom = 5;
    constexpr int step = 2;

    constexpr auto seq = generate_sequence.operator()<int, size, startFrom, step>();
    bool passed = true;

    for (int i = 0; i < size; ++i) {
        if (const int expected = startFrom + i * step; seq[i] != expected) {
            cout << "Ошибка в индексе #" << i << ": ожидаемое значение: " << expected << ", результат: " << seq[i] << endl;
            passed = false;
        }
    }

    if (passed) {
        cout << "Проверки пройдены!" << endl;
    }

    return passed ? 0 : 1;
}