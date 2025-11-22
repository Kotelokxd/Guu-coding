
#include <iostream>

using namespace std;

void swap(int ar[], int a, int b) {
    int temp = ar[a];
    ar[a] = ar[b];
    ar[b] = temp;
}

void sortColors(int ar[], const int n) {
    int low = 0, mid = 0, high = n - 1;

    while (mid <= high) {
        switch (ar[mid]) {
            case 0: swap(ar, low++, mid++); break;
            case 1: mid++; break;
            case 2: swap(ar, mid, high--); break;
            default: throw range_error("color not implemented");
        }
    }

}

void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

void testCase1() {
    const int n = 6;
    int testValues[n] = {
        2,0,2,1,1,0
    };

    sortColors(testValues, n);
    printArray(testValues, n);
}


void testCase2() {
    const int n = 3;
    int testValues[n] = {
        0, 1, 2
    };

    sortColors(testValues, n);
    printArray(testValues, n);
}

int main() {
    testCase1();
    testCase2();

    return 0;
}
