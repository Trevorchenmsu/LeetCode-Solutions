/*
solution: sorting
time: O(nlogn), we use sort() function to sort the array
space: O(1)
*/
class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.empty() || intervals.size() == 0)
            return true;
        
        sort(intervals.begin(), intervals.end());
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i - 1][1] > intervals[i][0])
                return false;
        }
        
        return true;
    }
};