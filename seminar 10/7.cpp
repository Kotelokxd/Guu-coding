#include <iostream>
#include <string>
using namespace std;

template <typename T>
class PriorityQueue {
private:
    struct Node {
        int priority;
        T value;
        Node* next;
        Node(int p, T v) : priority(p), value(v), next(nullptr) {}
    };
    Node* head;
 
public:
    PriorityQueue() : head(nullptr) {}
    ~PriorityQueue() { clear(); }

    void enqueue(int p, T v);
    T dequeue();
    string toString();
    void clear();

    friend ostream& operator<<(ostream& os, const PriorityQueue& q) {
        for (auto t = q.head; t; t = t->next) {
            os << "(" << t->priority << "," << t->value << ")";
            if (t->next) os << " ";
        }
        return os;
    }

    friend istream& operator>>(istream& is, PriorityQueue& q) {
        q.clear();
        string s;
        if (!getline(is, s)) return is;

        size_t i = 0;
        while (i < s.size()) {
            if (s[i] != '(') { i++; continue; }
            i++;

            int p = 0;
            bool neg = false;
            if (i < s.size() && s[i] == '-') { neg = true; i++; }
            while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                p = p * 10 + (s[i] - '0');
                i++;
            }
            if (neg) p = -p;
            if (i < s.size() && s[i] == ',') i++;

            int v = 0;
            neg = false;
            if (i < s.size() && s[i] == '-') { neg = true; i++; }
            while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                v = v * 10 + (s[i] - '0');
                i++;
            }
            if (neg) v = -v;

            if (i < s.size() && s[i] == ')') i++;

            q.enqueue(p, v);
        }
        return is;
    }
};

template <typename T>
void PriorityQueue<T>::enqueue(int p, T v) {
    auto* n = new Node(p, v);
    if (!head || p > head->priority) {
        n->next = head;
        head = n;
        return;
    }
    auto t = head;
    while (t->next && p <= t->next->priority)
        t = t->next;
    n->next = t->next;
    t->next = n;
}

template <typename T>
T PriorityQueue<T>::dequeue() {
    if (!head) {
        cout << "Очередь пуста!\n";
        return T();
    }
    auto t = head;
    decltype(t->value) v = t->value;
    head = head->next;
    delete t;
    return v;
}

template <typename T>
string PriorityQueue<T>::toString() {
    string s;
    for (auto t = head; t; t = t->next) {
        s += "(" + to_string(t->priority) + "," + to_string(t->value) + ")";
        if (t->next) s += " ";
    }
    return s;
}

template <typename T>
void PriorityQueue<T>::clear() {
    while (head) {
        auto t = head;
        head = head->next;
        delete t;
    }
}

int main() {
    PriorityQueue<int> q;

    q.enqueue(10, 100);
    q.enqueue(30, 300);
    q.enqueue(20, 200);
    q.enqueue(30, 350);

    cout << "Очередь: " << q << "\n";
    cout << "toString: " << q.toString() << "\n\n";

    cout << "Извлекли: " << q.dequeue() << "\n";
    cout << "Извлекли: " << q.dequeue() << "\n";
    cout << "Осталось: " << q << "\n\n";

    cout << "Вводите как строку, например:\n";
    cout << "(5,55) (15,150) (5,88)\n";
    cout << "-> ";

    PriorityQueue<int> q2;
    cin >> q2;
    cout << "Прочитано: " << q2 << "\n";

    return 0;
}
