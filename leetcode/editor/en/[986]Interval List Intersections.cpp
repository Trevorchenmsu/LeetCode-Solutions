//You are given two lists of closed intervals, firstList and secondList, where f
//irstList[i] = [starti, endi] and secondList[j] = [startj, endj]. Each list of in
//tervals is pairwise disjoint and in sorted order. 
//
// Return the intersection of these two interval lists. 
//
// A closed interval [a, b] (with a < b) denotes the set of real numbers x with 
//a <= x <= b. 
//
// The intersection of two closed intervals is a set of real numbers that are ei
//ther empty or represented as a closed interval. For example, the intersection of
// [1, 3] and [2, 4] is [2, 3]. 
//
// 
// Example 1: 
//
// 
//Input: firstList = [[0,2],[5,10],[13,23],[24,25]], secondList = [[1,5],[8,12],
//[15,24],[25,26]]
//Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
// 
//
// Example 2: 
//
// 
//Input: firstList = [[1,3],[5,9]], secondList = []
//Output: []
// 
//
// Example 3: 
//
// 
//Input: firstList = [], secondList = [[4,8],[10,12]]
//Output: []
// 
//
// Example 4: 
//
// 
//Input: firstList = [[1,7]], secondList = [[3,10]]
//Output: [[3,7]]
// 
//
// 
// Constraints: 
//
// 
// 0 <= firstList.length, secondList.length <= 1000 
// firstList.length + secondList.length >= 1 
// 0 <= starti < endi <= 109 
// endi < starti+1 
// 0 <= startj < endj <= 109 
// endj < startj+1 
// 
// Related Topics Array Two Pointers 
// 👍 2581 👎 69


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: sweep line
 * time: O(m+n)
 * space: O(1)
 *
 * */
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> res;
        if (A.empty() || B.empty()) {
            return res;
        }

        int i = 0, j = 0, start = 0, end = 0;
        while (i < A.size() && j < B.size()) {
            if (A[i][0] > B[j][1]) {
                j++;
                continue;
            }

            if (B[j][0] > A[i][1]) {
                i++;
                continue;
            }


            start = max(A[i][0], B[j][0]);
            end = min(A[i][1], B[j][1]);
            res.push_back({start, end});

            if (end == A[i][1]) {
                i++;
            }
            else {
                j++;
            }
        }

        return res;
    }
};

/*
 * solution 2: sweep line
 * time: O(m+n)
 * space: O(1)
 *
 * */
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> res;
        if (firstList.empty() || secondList.empty()) return res;

        int i = 0, j = 0;
        while (i < firstList.size() && j < secondList.size()) {
            int left = max(firstList[i][0], secondList[j][0]);
            int right = min(firstList[i][1], secondList[j][1]);

            if (left <= right)
                res.push_back({left, right});

            if (firstList[i][1] < secondList[j][1])
                i++;
            else j++;
        }

        return res;

    }
};

/*
 * solution 3: sweep line
 * time: O(m+n)
 * space: O(1)
 *
 * */

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> res;
        if (A.empty() || B.empty()) {
            return res;
        }

        int i = 0, j = 0;
        int start = 0, end = 0;
        while (i < A.size() && j < B.size()) {
            if (B[j][0] >= A[i][0] && B[j][0] <= A[i][1] ||
                A[i][0] >= B[j][0] && A[i][0] <= B[j][1]) {
                start = max(A[i][0], B[j][0]);
                end = min(A[i][1], B[j][1]);
                res.push_back({start, end});
            }

            if (B[j][1] > A[i][1]) {
                i++;
            }
            else {
                j++;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
