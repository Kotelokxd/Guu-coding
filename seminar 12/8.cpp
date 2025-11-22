#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool canReachToEnd(const vector<int>& stones) {
    unordered_map<int, unordered_set<int>> jumps;

    for (int s : stones) {
        jumps[s] = unordered_set<int>();
    }

    jumps[0].insert(0);

    for (const int currentStone : stones) {
        for (const int k : jumps[currentStone]) {
            for (int nextJump = k - 1; nextJump <= k + 1; ++nextJump) {
                if (nextJump > 0) {
                    const int nextPosition = currentStone + nextJump;

                    if (jumps.count(nextPosition)) {
                        jumps[nextPosition].insert(nextJump);
                    }
                }
            }
        }
    }

    return !jumps[stones.back()].empty();
}

int main() {
    vector stones1 = {0,1,3,5,6,8,12,17};
    cout << "Пример 1: " << canReachToEnd(stones1) << endl;

    vector stones2 = {0,1,2,3,4,8,9,11};
    cout << "Пример 2: " << canReachToEnd(stones2) << endl;

    return 0;
}