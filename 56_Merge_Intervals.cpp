/*
solution: sweep line
time: O(nlogn), because of sorting
space: O(1) or O(n), 
If we can sort intervals in place, we do not need more than constant additional space. 
Otherwise, we must allocate linear space to store a copy of intervals and sort that.
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


