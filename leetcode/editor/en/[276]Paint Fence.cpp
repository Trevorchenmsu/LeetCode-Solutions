//You are painting a fence of n posts with k different colors. You must paint th
//e posts following these rules: 
//
// 
// Every post must be painted exactly one color. 
// There cannot be three or more consecutive posts with the same color. 
// 
//
// Given the two integers n and k, return the number of ways you can paint the f
//ence. 
//
// 
// Example 1: 
//
// 
//Input: n = 3, k = 2
//Output: 6
//Explanation: All the possibilities are shown.
//Note that painting all the posts red or all the posts green is invalid because
// there cannot be three posts in a row with the same color.
// 
//
// Example 2: 
//
// 
//Input: n = 1, k = 1
//Output: 1
// 
//
// Example 3: 
//
// 
//Input: n = 7, k = 2
//Output: 42
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 50 
// 1 <= k <= 105 
// The testcases are generated such that the answer is in the range [0, 231 - 1]
// for the given n and k. 
// 
// Related Topics Dynamic Programming 
// 👍 1082 👎 343


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dp
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int numWays(int n, int k) {
        if (n == 0) return 0;
        if (n == 1) return k;
        if (n == 2) return k * k;

        vector<int> dp(n + 1);
        // 一根柱子时，可以填k种颜色
        dp[1] = k;
        // 两个柱子时有两种情况：同色和不同色。同色：k种；不同色：第一根柱子选k种，第二根只能选k-1种。所以k+k*(k-1)=k*k
        dp[2] = k * k;

        for (int i = 3; i <= n; i++) {
            /*
             * 状态转移公式解释：考虑当前柱子和上一个柱子，只有两种方式：同色、不同色
             *（1）不同色：前一个柱子有dp[i-1]种方法，当前柱子要不同色，只有k-1种选择，所以dp[i-1]*(k-1);
             *（2）同色：当前柱子必须跟上一个柱子同一颜色，没得选择。那么此时需要检查i-2柱子，因为不能保证连续3个同色。
             * 那么第i-2柱子有dp[i-2]方案，i-1和i同色，只可以选另外的k-1种颜色，所以dp[i-2]*(k-1)
             * */
            dp[i] = (dp[i - 2] + dp[i - 1]) * (k - 1);
        }

        return dp[n];
    }
};

/*
 * solution 2: dp
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int numWays(int n, int k) {
        if (n == 0) return 0;
        if (n == 1) return k;

        int same = k;
        int diff = k * (k - 1);

        for (int i = 2; i < n; i++) {
            int same_temp = same;
            int diff_temp = diff;
            diff = (same_temp + diff_temp) * (k - 1);
            same = diff_temp;
        }

        return same + diff;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
