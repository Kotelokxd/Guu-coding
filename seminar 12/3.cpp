#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class NestedInteger {
    bool is_int;
    int value;
    vector<NestedInteger> list;

public:
    NestedInteger() : is_int(false), value(0) {}
    NestedInteger(int value) : is_int(true), value(value) {}

    bool isInteger() const;
    int getInteger() const;
    void setInteger(int value);

    void add(const NestedInteger &ni);

    const vector<NestedInteger>& getList() const;
};

bool NestedInteger::isInteger() const {
    return is_int;
}

int NestedInteger::getInteger() const {
    return value;
}

void NestedInteger::setInteger(int value) {
    is_int = true;
    this->value = value;
    list.clear();
}

void NestedInteger::add(const NestedInteger &ni) {
    if (is_int) {
        int old = value;
        list.clear();
        list.push_back(NestedInteger(old));
        is_int = false;
    }
    list.push_back(ni);
}

const vector<NestedInteger> & NestedInteger::getList() const {
    return list;
}

NestedInteger parseNested(const string &s, int &i) {
    if (s[i] == '[') {
        NestedInteger result;
        i++; // пропускаем '['

        while (i < (int)s.size() && s[i] != ']') {
            NestedInteger elem = parseNested(s, i);
            result.add(elem);

            if (i < (int) s.size() && s[i] == ',') {
                i++; // пропускаем запятую
            }
        }

        i++; // пропускаем ']'
        return result;
    } else {
        bool neg = false;
        if (s[i] == '-') {
            neg = true;
            i++;
        }

        int num = 0;
        while (i < (int)s.size() && isdigit((unsigned char)s[i])) {
            num = num * 10 + (s[i] - '0');
            i++;
        }
        if (neg) num = -num;

        return NestedInteger(num);
    }
}

NestedInteger deserialize(const string &s) {
    int i = 0;
    return parseNested(s, i);
}

void printNested(const NestedInteger &ni) {
    if (ni.isInteger()) {
        cout << ni.getInteger();
    } else {
        cout << "[";
        const auto &lst = ni.getList();
        for (size_t i = 0; i < lst.size(); ++i) {
            if (i > 0) cout << ",";
            printNested(lst[i]);
        }
        cout << "]";
    }
}

int main() {
    string line;
    if (!getline(cin, line)) {
        return 0;
    }

    string s;

    // ищем первую и вторую кавычку
    size_t first = line.find('"');
    if (first != string::npos) {
        size_t second = line.find('"', first + 1);
        if (second != string::npos) {
            s = line.substr(first + 1, second - first - 1);
        } else {
            s = line.substr(first + 1);
        }
    } else {
        s = line;
    }

    NestedInteger result = deserialize(s);

    printNested(result);
    return 0;
}
