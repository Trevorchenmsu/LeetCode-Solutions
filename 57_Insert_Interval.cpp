/*
solution: sweep line
time: O(n)
space: O(1)
*/
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        if (intervals.empty()) {
            res.push_back(newInterval);
            return res;
        }
        
        int i = 0, len = intervals.size();
        
        // no intersection: new interval is larger than the individual interval
        while (i < len && intervals[i][1] < newInterval[0]) {
            res.push_back(intervals[i++]);
        }
        
        // intersection:
        while (i < len && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(intervals[i][0], newInterval[0]);
            newInterval[1] = max(intervals[i++][1], newInterval[1]);
        }
        
        res.push_back(newInterval);
        
        // no intersection: new interval is smaller than the individual interval
        while (i < len) {
            res.push_back(intervals[i++]);
        }
            
        return res;
    }
};