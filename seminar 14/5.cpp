#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs(n);
        for (int i = 0; i < n; ++i) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }

        sort(jobs.begin(), jobs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        vector<int> dp(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            int currProfit = jobs[i][2];
            int currStart = jobs[i][0];
            int currEnd = jobs[i][1];

            int latestNonOverlap = -1;
            int left = 0, right = i - 1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (jobs[mid][1] <= currStart) {
                    latestNonOverlap = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            int prevProfit = (latestNonOverlap == -1) ? 0 : dp[latestNonOverlap + 1];
            dp[i + 1] = max(dp[i], prevProfit + currProfit);
        }

        return dp[n];
    }
};

int main() {
    Solution sol;

    cout << "========== Тестирование jobScheduling ==========" << endl << endl;

    vector<int> s1 = {1,2,3,3};
    vector<int> e1 = {3,4,5,6};
    vector<int> p1 = {50,10,40,70};
    cout << "Тест 1:" << endl;
    cout << "startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]" << endl;
    cout << "Ожидаемо: 120" << endl;
    cout << "Получено:  " << sol.jobScheduling(s1, e1, p1) << endl << endl;

    vector<int> s2 = {1,2,3,4,6};
    vector<int> e2 = {3,5,10,6,9};
    vector<int> p2 = {20,20,100,70,60};
    cout << "Тест 2:" << endl;
    cout << "startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]" << endl;
    cout << "Ожидаемо: 150" << endl;
    cout << "Получено:  " << sol.jobScheduling(s2, e2, p2) << endl << endl;

    vector<int> s3 = {1,1,1};
    vector<int> e3 = {2,3,4};
    vector<int> p3 = {5,6,4};
    cout << "Тест 3:" << endl;
    cout << "startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]" << endl;
    cout << "Ожидаемо: 6" << endl;
    cout << "Получено:  " << sol.jobScheduling(s3, e3, p3) << endl;

    return 0;
}
