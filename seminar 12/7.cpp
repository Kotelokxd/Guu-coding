#include <string>
#include <cctype>
#include <iostream>
#include <vector>

using namespace std;

constexpr int MIN_LENGTH_PASSWORD = 6;
constexpr int MAX_LENGTH_PASSWORD = 20;
constexpr int MAX_IDENTICAL_CHARS = 3;

int checkOnStrongPassword(const string &password) {
    const int passwordLength = password.length();

    bool hasLower = false, hasUpper = false, hasDigit = false;
    for (char c : password) {
        if (islower(c)) hasLower = true;
        else if (isupper(c)) hasUpper = true;
        else if (isdigit(c)) hasDigit = true;
    }

    const int missingTypes = !hasLower + !hasUpper + !hasDigit;

    if (passwordLength < MIN_LENGTH_PASSWORD) {
        return max(missingTypes, MIN_LENGTH_PASSWORD - passwordLength);
    }

    vector<int> repeats;
    for (int i = 0; i < passwordLength;) {
        int j = i;
        while (j < passwordLength && password[j] == password[i]) {
            j++;
        }
        if (j - i >= MAX_IDENTICAL_CHARS) {
            repeats.push_back(j - i);
        }
        i = j;
    }

    if (passwordLength <= MAX_LENGTH_PASSWORD) {
        int replaceCount = 0;
        for (const int len : repeats) {
            replaceCount += len / 3;
        }
        return max(missingTypes, replaceCount);
    }

    int deleteNeed = passwordLength - MAX_LENGTH_PASSWORD;

    for (int i = 0; i < repeats.size() && deleteNeed > 0; i++) {
        if (repeats[i] % MAX_IDENTICAL_CHARS == 0) {
            repeats[i]--;
            deleteNeed--;
        }
    }

    for (int i = 0; i < repeats.size() && deleteNeed > 0; i++) {
        if (repeats[i] % MAX_IDENTICAL_CHARS == 1) {
            int canDelete = min(deleteNeed, 2);
            repeats[i] -= canDelete;
            deleteNeed -= canDelete;
        }
    }

    int replaceCount = 0;
    for (int len : repeats) {
        if (deleteNeed > 0 && len >= MAX_IDENTICAL_CHARS) {
            const int canDelete = min(deleteNeed, len - 2);
            len -= canDelete;
            deleteNeed -= canDelete;
        }

        if (len >= MAX_IDENTICAL_CHARS) {
            replaceCount += len / MAX_IDENTICAL_CHARS;
        }
    }

    return (passwordLength - MAX_LENGTH_PASSWORD) + max(missingTypes, replaceCount);
}

int main() {
    const string p1 = "a";
    cout << "Пароль: " << p1 << " -> Шагов: " << checkOnStrongPassword(p1) << endl;

    const string p2 = "aA1";
    cout << "Пароль: " << p2 << " -> Шагов: " << checkOnStrongPassword(p2) << endl;

    const string p3 = "1337C0d3";
    cout << "Пароль: " << p3 << " -> Шагов: " << checkOnStrongPassword(p3) << endl;

    const string p4 = "ABABABABABABABABABAB111";
    cout << "Пароль: " << p4 << " -> Шагов: " << checkOnStrongPassword(p4) << endl;

    return 0;
}
