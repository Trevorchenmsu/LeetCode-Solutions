//Given an array of intervals where intervals[i] = [starti, endi], merge all ove
//rlapping intervals, and return an array of the non-overlapping intervals that co
//ver all the intervals in the input. 
//
// 
// Example 1: 
//
// 
//Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
//Output: [[1,6],[8,10],[15,18]]
//Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
// 
//
// Example 2: 
//
// 
//Input: intervals = [[1,4],[4,5]]
//Output: [[1,5]]
//Explanation: Intervals [1,4] and [4,5] are considered overlapping.
// 
//
// 
// Constraints: 
//
// 
// 1 <= intervals.length <= 104 
// intervals[i].length == 2 
// 0 <= starti <= endi <= 104 
// 
// Related Topics Array Sorting 
// 👍 8548 👎 410


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: sort
 * time: O(nlogn)
 * space: O(logn)
 *
 * */
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int start = intervals[0][0], end = intervals[0][1];

        vector<vector<int>> res;
        for (int i = 0; i < intervals.size(); i++) {
            //只要发生重叠，就只更新右边界，取较大值
            if (intervals[i][0] <= end) {
                end = max(end, intervals[i][1]);
            }
            // 当不重叠时，就要对前面的区间进行清算，同时用当前位置来更新start，end指针
            else {
                res.push_back({start, end});
                start = intervals[i][0];
                end = intervals[i][1];
            }
        }

        res.push_back({start, end});
        return res;
    }
};

/*
 * solution 2: sweep line
 * time: O(nlogn)
 * space: O(logn)
 *
 * */

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<vector<int>> res;
        vector<int> starts, ends;

        for (int i = 0; i < n; ++i) {
            starts.push_back(intervals[i][0]);
            ends.push_back(intervals[i][1]);
        }

        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        for (int i = 0, j = 0; i < n; ++i) {
            if (i == n - 1 || starts[i + 1] > ends[i]) {
                res.push_back({starts[j], ends[i]});
                j = i + 1;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
