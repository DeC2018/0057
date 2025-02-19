#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        const int n = intervals.size();
        vector<vector<int>> ans;
        int i = 0;

        while (i < n && intervals[i][1] < newInterval[0])
            ans.push_back(intervals[i++]);

        // Merge overlapping intervals
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            ++i;
        }

        ans.push_back(newInterval);

        while (i < n)
            ans.push_back(intervals[i++]);

        return ans;
    }
};

int main() {
    Solution solution;

    vector<vector<int>> intervals1 = {{1, 3}, {6, 9}};
    vector<int> newInterval1 = {2, 5};
    cout << "Input: intervals = [[1,3],[6,9]], newInterval = [2,5]" << endl;
    vector<vector<int>> result1 = solution.insert(intervals1, newInterval1);
    cout << "Output: [";
    for (size_t i = 0; i < result1.size(); ++i) {
        cout << "[" << result1[i][0] << "," << result1[i][1] << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    vector<vector<int>> intervals2 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<int> newInterval2 = {4, 8};
    cout << "Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]" << endl;
    vector<vector<int>> result2 = solution.insert(intervals2, newInterval2);
    cout << "Output: [";
    for (size_t i = 0; i < result2.size(); ++i) {
        cout << "[" << result2[i][0] << "," << result2[i][1] << "]";
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    return 0;
}
