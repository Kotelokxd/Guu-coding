#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Triangle {
    vector<vector<int>> grid;

public:
    Triangle() = default;

    void addRow(const vector<int>& row);

    int getHeight() const;
    int getMinimumPathSum() const;

    friend ostream& operator<<(ostream& os, const Triangle& obj) {
        if (obj.grid.empty()) {
            os << "Треугольник пуст.";
            return os;
        }

        for (const auto& row : obj.grid) {
            for (const int val : row) {
                os << val << " ";
            }
            os << endl;
        }
        return os;
    }
};

void Triangle::addRow(const vector<int> &row) {
    grid.push_back(row);
}

int Triangle::getHeight() const {
    return grid.size();
}

int Triangle::getMinimumPathSum() const {
    if (grid.empty()) return 0;

    const int n = grid.size();

    vector<int> dp = grid[n - 1];

    for (int row = n - 2; row >= 0; --row) {
        for (int col = 0; col <= row; ++col) {
            dp[col] = grid[row][col] + min(dp[col], dp[col + 1]);
        }
    }

    return dp[0];
}

Triangle inputTriangle() {
    Triangle tr;
    int rows;
    cout << "Введите высоту треугольника (количество строк): ";

    while (!(cin >> rows) || rows < 1) {
        cout << "Некорректный ввод. Введите положительное целое число: ";
        cin.clear();
    }

    cout << "Введите элементы треугольника построчно:" << endl;
    for (int i = 0; i < rows; ++i) {
        vector<int> row;

        int cols = i + 1;

        cout << "Строка " << (i + 1) << " (" << cols << " чисел): ";
        for (int j = 0; j < cols; ++j) {
            int val;
            cin >> val;
            row.push_back(val);
        }
        tr.addRow(row);
    }

    return tr;
}

int main() {
    Triangle tr = inputTriangle();

    cout << "\n--- Треугольник ---" << endl;
    cout << tr;

    if (tr.getHeight() > 0) {
        const int result = tr.getMinimumPathSum();
        cout << "-----------------------" << endl;
        cout << "Минимальная сумма пути: " << result << endl;
    } else {
        cout << "Треугольник пуст." << endl;
    }

    return 0;
}