/*
solution: priority queue-min heap
time: O（nlogn), we sort the array and min-heap push/pop takes O(logn), 
when we traverse array,it will be O(n*logn)
space: O(n), since we can only have n meetings in the min-heap at the same time.
*/
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty() || intervals[0].empty())
            return 0;
        
        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> miniHeap;
        miniHeap.push(intervals[0][1]);
        
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= miniHeap.top())
                miniHeap.pop();
            miniHeap.push(intervals[i][1]);
        }
        
        return miniHeap.size();
    }
};