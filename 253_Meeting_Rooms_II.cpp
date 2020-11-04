/*
solution: priority queue-min heap
time: O（nlogn), we sort the array 
space: O(n), since we can only have n meetings in the min-heap at the same time.
*/
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int res = 0;
        if (intervals.empty() || intervals.size() == 0)
            return res;
        
        // define min heap
        priority_queue<int, vector<int>, greater<int>> rooms_heap;
        sort(intervals.begin(), intervals.end());
        rooms_heap.push(intervals[0][1]);
        
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] >= rooms_heap.top())
                rooms_heap.pop();
            rooms_heap.push(intervals[i][1]);
        }    
     
        return rooms_heap.size();
    }
};
