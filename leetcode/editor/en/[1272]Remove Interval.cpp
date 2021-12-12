//A set of real numbers can be represented as the union of several disjoint inte
//rvals, where each interval is in the form [a, b). A real number x is in the set 
//if one of its intervals [a, b) contains x (i.e. a <= x < b). 
//
// You are given a sorted list of disjoint intervals intervals representing a se
//t of real numbers as described above, where intervals[i] = [ai, bi] represents t
//he interval [ai, bi). You are also given another interval toBeRemoved. 
//
// Return the set of real numbers with the interval toBeRemoved removed from int
//ervals. In other words, return the set of real numbers such that every x in the 
//set is in intervals but not in toBeRemoved. Your answer should be a sorted list 
//of disjoint intervals as described above. 
//
// 
// Example 1: 
//
// 
//Input: intervals = [[0,2],[3,4],[5,7]], toBeRemoved = [1,6]
//Output: [[0,1],[6,7]]
// 
//
// Example 2: 
//
// 
//Input: intervals = [[0,5]], toBeRemoved = [2,3]
//Output: [[0,2],[3,5]]
// 
//
// Example 3: 
//
// 
//Input: intervals = [[-5,-4],[-3,-2],[1,2],[3,5],[8,9]], toBeRemoved = [-1,4]
//Output: [[-5,-4],[-3,-2],[4,5],[8,9]]
// 
//
// 
// Constraints: 
//
// 
// 1 <= intervals.length <= 104 
// -109 <= ai < bi <= 109 
// 
// Related Topics Array 
// 👍 205 👎 18


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: implementation
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        vector<vector<int>> res;
        if (toBeRemoved.empty()) {
            return intervals;
        }

        if (intervals.size() == 1 && intervals[0] == toBeRemoved) {
            return res;
        }

        int i = 0, n = intervals.size();

        // no intersection, left part of removed interval
        while (i < n && intervals[i][1] <= toBeRemoved[0]) {
            res.push_back(intervals[i++]);
        }

        // intersection
        while (i < n && intervals[i][0] < toBeRemoved[1]) {
            if (toBeRemoved[0] >= intervals[i][0] && toBeRemoved[1] >= intervals[i][1]) {
                res.push_back({intervals[i++][0], toBeRemoved[0]});
            }
            else if (toBeRemoved[0] <= intervals[i][0] && toBeRemoved[1] <= intervals[i][1]) {
                res.push_back({toBeRemoved[1], intervals[i++][1]});
            }
            else if (toBeRemoved[0] >= intervals[i][0] && toBeRemoved[1] <= intervals[i][1]) {
                res.push_back({intervals[i][0], toBeRemoved[0]});
                res.push_back({toBeRemoved[1], intervals[i++][1]});
            }
            else {
                i++;
            }

        }

        // no intersection, right part of removed interval
        while (i < n) {
            res.push_back(intervals[i++]);
        }

        return res;
    }
};

/*
 * solution 2: implementation
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        vector<vector<int>> res;
        if (intervals.empty() || intervals[0].empty())
            return res;

        int i = 0, n = intervals.size();
        int B_s = toBeRemoved[0], B_e = toBeRemoved[1];

        for (const auto &interval : intervals) {
            int A_s = interval[0], A_e = interval[1];

            // no intersection
            if (A_e < B_s || A_s > B_e)
                res.push_back({A_s, A_e});
            else
            {
                if (A_s < B_s)
                    res.push_back({A_s, B_s});

                if (A_e > B_e)
                    res.push_back({B_e, A_e});
            }
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
