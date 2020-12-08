/*
solution: sweep line
time: O(nlogn), because of sorting
space: O(n), the worst case is we need to store all the non-overlap intervals.
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty() || intervals.size() < 1)
            return intervals;
        sort(intervals.begin(), intervals.end());
        int start = intervals[0][0];
        int end = intervals[0][1];
        vector<vector<int>> res;
        for (auto& interval : intervals) {
            if(interval[0] <= end) {
                end = max(end, interval[1]);
            } else {
                res.push_back({start, end});
                start = interval[0];
                end = interval[1];
            }
        }
        res.push_back({start, end});
        return res;
    }
};


