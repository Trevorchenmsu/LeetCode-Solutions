//Given an array of intervals intervals where intervals[i] = [starti, endi], ret
//urn the minimum number of intervals you need to remove to make the rest of the i
//ntervals non-overlapping. 
//
// 
// Example 1: 
//
// 
//Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
//Output: 1
//Explanation: [1,3] can be removed and the rest of the intervals are non-overla
//pping.
// 
//
// Example 2: 
//
// 
//Input: intervals = [[1,2],[1,2],[1,2]]
//Output: 2
//Explanation: You need to remove two [1,2] to make the rest of the intervals no
//n-overlapping.
// 
//
// Example 3: 
//
// 
//Input: intervals = [[1,2],[2,3]]
//Output: 0
//Explanation: You don't need to remove any of the intervals since they're alrea
//dy non-overlapping.
// 
//
// 
// Constraints: 
//
// 
// 1 <= intervals.length <= 105 
// intervals[i].length == 2 
// -5 * 104 <= starti < endi <= 5 * 104 
// 
// Related Topics Array Dynamic Programming Greedy Sorting 
// 👍 2415 👎 70


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: greedy
 * time: O(nlogn)
 * space: O(logn) for sorting
 *
 * */
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int  res = 0, end = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= end) {
                end = intervals[i][1];
            }
            else {
                res++;
                end = min(end, intervals[i][1]);
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
