//Given a set of non-overlapping intervals, insert a new interval into the inter
//vals (merge if necessary). 
//
// You may assume that the intervals were initially sorted according to their st
//art times. 
//
// 
// Example 1: 
//
// 
//Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
//Output: [[1,5],[6,9]]
// 
//
// Example 2: 
//
// 
//Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
//Output: [[1,2],[3,10],[12,16]]
//Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10]. 
//
//
// Example 3: 
//
// 
//Input: intervals = [], newInterval = [5,7]
//Output: [[5,7]]
// 
//
// Example 4: 
//
// 
//Input: intervals = [[1,5]], newInterval = [2,3]
//Output: [[1,5]]
// 
//
// Example 5: 
//
// 
//Input: intervals = [[1,5]], newInterval = [2,7]
//Output: [[1,7]]
// 
//
// 
// Constraints: 
//
// 
// 0 <= intervals.length <= 104 
// intervals[i].length == 2 
// 0 <= intervals[i][0] <= intervals[i][1] <= 105 
// intervals is sorted by intervals[i][0] in ascending order. 
// newInterval.length == 2 
// 0 <= newInterval[0] <= newInterval[1] <= 105 
// 
// Related Topics Array 
// 👍 3344 👎 273


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution：Implementation
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // corner case
        vector<vector<int>> res;
        if (intervals.empty()) {
            res.push_back(newInterval);
            return res;
        }

        int i = 0, n = intervals.size();

        // no intersection, left part of newInterval
        while (i < n && intervals[i][1] < newInterval[0]) {
            res.push_back(intervals[i++]);
        }

        /* intersection.
         * trick：这里的条件不能采用intervals[i][1] >= newInterval[0]，因为当我们从上一个循环跳出时，
         * 这个条件实际已经满足了，所以不需要再重新判定。实际上我们需要考虑的情况如下图所示:
          new:    |___|  |___|
          old: |_____|      |____|
          注意：old的右边界可以大于其余三个边界（old和new），但是old的左边界往右移的最大边界只能是new的右边界，
          否则就不相交了，所以这里采用的条件是intervals[i][0] <= newInterval[1]
        */
        while (i < n && intervals[i][0] <= newInterval[1]) {
//        while (i < n && ) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i++][1]);
        }

        res.push_back(newInterval);

        // no intersection, right part of newInterval
        while (i < n) {
            res.push_back(intervals[i++]);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
