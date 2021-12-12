//Given a list of intervals, remove all intervals that are covered by another in
//terval in the list. 
//
// Interval [a,b) is covered by interval [c,d) if and only if c <= a and b <= d.
// 
//
// After doing so, return the number of remaining intervals. 
//
// 
// Example 1: 
//
// 
//Input: intervals = [[1,4],[3,6],[2,8]]
//Output: 2
//Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
// 
//
// Example 2: 
//
// 
//Input: intervals = [[1,4],[2,3]]
//Output: 1
// 
//
// Example 3: 
//
// 
//Input: intervals = [[0,10],[5,12]]
//Output: 2
// 
//
// Example 4: 
//
// 
//Input: intervals = [[3,10],[4,10],[5,11]]
//Output: 2
// 
//
// Example 5: 
//
// 
//Input: intervals = [[1,2],[1,4],[3,4]]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// 1 <= intervals.length <= 1000 
// intervals[i].length == 2 
// 0 <= intervals[i][0] < intervals[i][1] <= 10^5 
// All the intervals are unique. 
// Related Topics Array Sorting 
// 👍 719 👎 27


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sort + greedy
 * time: O(nlogn)
 * space: O(log) for sorting
 * */
class Solution {
public:
    /*
     * 排序要求：如果起点不同时，按照起点升序排序；如果起点相同时，按照终点降序排序
     * 为什么要这样排序？起点不同升序排序，主要是想要优先处理左边界较小的区间，因为它可以包含更广的范围。
     * 而起点相同时，按照终点降序排序，是因为最大的终点与最小的起点可以组合成在一个相同起点内的最大区间。例如
     1|_______|4
     1|_____|3
     1|____|2
     当我们考虑第一个区间[1,4]并计入结果时，因为后序的2和3不会比4大，所以都属于被包括的区间，因此要删除掉，所不被计数。
     这是起点相同的情况。对于起点不同，但是终点小于4的情况，例如
     1|_______|4
      2|____|3
      3|____|4

    在这些起点不同的情况，只要它们的终点没有大于4，它们就还是被包含区间，也是要被删除的，所有计数器不更新。
    因此，只有在满足end > pre_end的情况下，才会更新计数器。这时候表明之前的最大区间已经考虑完毕，继续下一轮同样的考虑。
     * */
    static bool cmp (const vector<int> &v1, const vector<int> &v2) {
        if (v1[0] == v2[0]) {
            return v2[1] < v1[1];
        }
        else {
            return v1[0] < v2[0];
        }
    }

    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);

        /* 为什么这里可以只考虑end而不用考虑start？这就是前面排序以起点为升序排序的意义。起点升序排序后，在遍历下一个元素时，总是
         * 可以保证下一个元素的起点肯定大于上一个元素的起点，即被包括在上一个元素起点里面。所以此时我们只需要比较终点即可。如果终点大于
         * 上一个元素的终点，那肯定交错了，结果加一且更新终点。
         * 为什么相同起点后又要对终点进行降序排序？假设我们对终点按升序排序，那么比较当前end和之前end的逻辑就会与上面的相反，因为在这种情况下
         * 当前end大于之前end时，反而时当前元素包含了上一个元素，cnt是不应该加1，所以不合理。当我们进行降序排序时，大的范围就会排在前面，当
         * 遍历下一个小的范围时，因为它的end没有超过preend，所以cnt不会加1。
         * */
        int cnt = 0, pre_end = 0, end = 0;
        for (auto &interval : intervals) {
            end = interval[1];

            if (pre_end < end) {
                cnt++;
                pre_end = end;
            }
        }

        return cnt;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
