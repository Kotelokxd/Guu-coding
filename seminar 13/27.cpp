#include <array>
#include <iostream>

constexpr long long factorial(const int n) {
    if (n < 0) return 0;
    long long res = 1;

    for (int i = 1; i <= n; ++i) {
        res *= i;
    }

    return res;
}

template<int... V>
constexpr auto compileTimeFactorial() {
    return std::array<long long, sizeof...(V)>{factorial(V)...};
}

int main() {
    constexpr auto facts = compileTimeFactorial<5, 3, 0, -1>();
    std::cout << facts[0] << " " << facts[1] << " " << facts[2] << " " << facts[3] << std::endl; 
    return 0;
}
