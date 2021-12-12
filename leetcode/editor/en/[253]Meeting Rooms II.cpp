//Given an array of meeting time intervals intervals where intervals[i] = [start
//i, endi], return the minimum number of conference rooms required. 
//
// 
// Example 1: 
// Input: intervals = [[0,30],[5,10],[15,20]]
//Output: 2
// Example 2: 
// Input: intervals = [[7,10],[2,4]]
//Output: 1
// 
// 
// Constraints: 
//
// 
// 1 <= intervals.length <= 104 
// 0 <= starti < endi <= 106 
// 
// Related Topics Array Two Pointers Greedy Sorting Heap (Priority Queue) 
// 👍 4146 👎 74


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: mini heap
 * time: O(nlogn)
 * space: O(n)
 *
 * */
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (auto &interval : intervals) {
            if (!minHeap.empty() && interval[0] >= minHeap.top()) {
                minHeap.pop();
            }
            minHeap.push(interval[1]);
        }

        return minHeap.size();
    }
};

/*
 * solution 2: sweep line
 * time: O(nlogn)
 * space: O(n)
 *
 * */
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<int> starts, ends;
        for (auto &interval : intervals) {
            starts.push_back(interval[0]);
            ends.push_back(interval[1]);
        }

        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        int res = 0, cur_end = 0;

        for (int i = 0; i < intervals.size(); i++) {
            if (starts[i] < ends[cur_end]) {
                res++;
            }
            else {
                cur_end++;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
