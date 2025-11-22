#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class IntStack {
private:
    int data[50];
    int topIndex;

public:
    IntStack();
    void push(int value);
    int pop();
    bool empty();
    bool full();
};

class StringStack {
private:
    string data[50];
    int topIndex;

public:
    StringStack();
    void push(const string& value);
    string pop();
    bool empty();
    bool full();
};

IntStack::IntStack() {
    topIndex = -1;
}

void IntStack::push(int value) {
    if (full()) {
        cout << "Ошибка: переполнение стека чисел" << endl;
        return;
    }
    data[++topIndex] = value;
}

int IntStack::pop() {
    if (empty()) {
        cout << "Ошибка: стек чисел пуст" << endl;
        return 0;
    }
    return data[topIndex--];
}

bool IntStack::empty() {
    return topIndex == -1;
}

bool IntStack::full() {
    return topIndex == 49;
}

StringStack::StringStack() {
    topIndex = -1;
}

void StringStack::push(const string& value) {
    if (full()) {
        cout << "Ошибка: переполнение стека строк" << endl;
        return;
    }
    data[++topIndex] = value;
}

string StringStack::pop() {
    if (empty()) {
        cout << "Ошибка: стек строк пуст" << endl;
        return "";
    }
    return data[topIndex--];
}

bool StringStack::empty() {
    return topIndex == -1;
}

bool StringStack::full() {
    return topIndex == 49;
}

string decodeString(const string& s) {
    IntStack countStack;
    StringStack stringStack;
    string currentString = "";
    int currentNumber = 0;

    for (char c : s) {
        if (isdigit(c)) {
            currentNumber = currentNumber * 10 + (c - '0');
        } else if (c == '[') {
            countStack.push(currentNumber);
            stringStack.push(currentString);
            currentNumber = 0;
            currentString = "";
        } else if (c == ']') {
            int repeatCount = countStack.pop();
            string previousString = stringStack.pop();
            
            string repeatedString = "";
            for (int i = 0; i < repeatCount; i++) {
                repeatedString += currentString;
            }
            currentString = previousString + repeatedString;
        } else {
            currentString += c;
        }
    }

    return currentString;
}

int main() {
    cout << "=== ДЕКОДИРОВАНИЕ СТРОКИ ===" << endl << endl;

    string test1 = "3[a]2[bc]";
    string test2 = "3[a2[c]]";
    string test3 = "2[abc]3[cd]ef";

    cout << "Тест 1:" << endl;
    cout << "Ввод: " << test1 << endl;
    cout << "Вывод: " << decodeString(test1) << endl << endl;

    cout << "Тест 2:" << endl;
    cout << "Ввод: " << test2 << endl;
    cout << "Вывод: " << decodeString(test2) << endl << endl;

    cout << "Тест 3:" << endl;
    cout << "Ввод: " << test3 << endl;
    cout << "Вывод: " << decodeString(test3) << endl << endl;

    string test4 = "1[2[3[a]]]";
    cout << "Тест вложенности:" << endl;
    cout << "Ввод: " << test4 << endl;
    cout << "Вывод: " << decodeString(test4) << endl;

    return 0;
}