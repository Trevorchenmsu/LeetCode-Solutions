//You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] r
//epresents the width and the height of an envelope. 
//
// One envelope can fit into another if and only if both the width and height of
// one envelope are greater than the other envelope's width and height. 
//
// Return the maximum number of envelopes you can Russian doll (i.e., put one in
//side the other). 
//
// Note: You cannot rotate an envelope. 
//
// 
// Example 1: 
//
// 
//Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
//Output: 3
//Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] 
//=> [5,4] => [6,7]).
// 
//
// Example 2: 
//
// 
//Input: envelopes = [[1,1],[1,1],[1,1]]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// 1 <= envelopes.length <= 5000 
// envelopes[i].length == 2 
// 1 <= wi, hi <= 104 
// 
// Related Topics Array Binary Search Dynamic Programming Sorting 
// 👍 2563 👎 66


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dp，接龙型dp
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    static bool cmp(const vector<int> &v1, const vector<int> &v2) {
        if (v1[0] != v2[0]) {
            return v1[0] < v2[0];
        }
        else {
            return v2[1] < v1[1];
        }
    }

    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if (envelopes.empty() || envelopes.size() == 0) {
            return 0;
        }

        sort(envelopes.begin(), envelopes.end(), cmp);
        int n = envelopes.size();
        vector<int> dp(n, 1);

        int res = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (envelopes[i][1] > envelopes[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }

        return res;
    }
};

/*
 * solution 2: insertion sort + binary search
 * time: O(nlogn)
 * space: O(n)
 * */

class Solution {
public:
    static bool cmp(const vector<int> &v1, const vector<int> &v2) {
        if (v1[0] != v2[0]) {
            return v1[0] < v2[0];
        }
        else {
            return v2[1] < v1[1];
        }
    }

    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if (envelopes.empty() || envelopes.size() == 0) {
            return 0;
        }

        sort(envelopes.begin(), envelopes.end(), cmp);
        int n = envelopes.size();
        vector<int> LIS;

        for (const auto& envelope: envelopes) {
            int height = envelope[1];
            auto it = lower_bound(LIS.begin(), LIS.end(), height);
            if (it == LIS.end()) {
                LIS.push_back(height);
            }
            else {
                *it = height;
            }
        }

        return LIS.size();
    }
};
//leetcode submit region end(Prohibit modification and deletion)
