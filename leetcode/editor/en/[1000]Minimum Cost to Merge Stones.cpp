//There are n piles of stones arranged in a row. The ith pile has stones[i] ston
//es. 
//
// A move consists of merging exactly k consecutive piles into one pile, and the
// cost of this move is equal to the total number of stones in these k piles. 
//
// Return the minimum cost to merge all piles of stones into one pile. If it is 
//impossible, return -1. 
//
// 
// Example 1: 
//
// 
//Input: stones = [3,2,4,1], k = 2
//Output: 20
//Explanation: We start with [3, 2, 4, 1].
//We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
//We merge [4, 1] for a cost of 5, and we are left with [5, 5].
//We merge [5, 5] for a cost of 10, and we are left with [10].
//The total cost was 20, and this is the minimum possible.
// 
//
// Example 2: 
//
// 
//Input: stones = [3,2,4,1], k = 3
//Output: -1
//Explanation: After any merge operation, there are 2 piles left, and we can't m
//erge anymore.  So the task is impossible.
// 
//
// Example 3: 
//
// 
//Input: stones = [3,5,1,2,6], k = 3
//Output: 25
//Explanation: We start with [3, 5, 1, 2, 6].
//We merge [5, 1, 2] for a cost of 8, and we are left with [3, 8, 6].
//We merge [3, 8, 6] for a cost of 17, and we are left with [17].
//The total cost was 25, and this is the minimum possible.
// 
//
// 
// Constraints: 
//
// 
// n == stones.length 
// 1 <= n <= 30 
// 1 <= stones[i] <= 100 
// 2 <= k <= 30 
// 
// Related Topics Array Dynamic Programming 
// 👍 1251 👎 69


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: 二维dp，区间型
 * time: O(n^3)
 * space: O(n^2)
 * */
class Solution {
public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();

        // 最终剩下一堆，所以要删除n-1堆。每次合并k堆成一堆，相当于删除k-1堆，因为这两个数要可以整除
        if((n - 1) % (K - 1) != 0) {
            return -1;
        }

        vector<int> prefixSum(n + 1);
        for(int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + stones[i];
        }

        vector<vector<int>> dp(n, vector<int>(n));
        for (int len = K; len <= n; len++) { // 从k开始，因为小于k的dp都为0
            for (int start = 0; start <= n - len; start++) {
                int end = start + len - 1;
                int cost = prefixSum[end + 1] - prefixSum[start];
                dp[start][end] = INT_MAX;
                for (int mid = start; mid < end; mid += K - 1) { // 这里递增的范围取决于k，小于k长度的不用考虑
                    dp[start][end] = min(dp[start][end], dp[start][mid] + dp[mid + 1][end]);
                }

                if ((end - start) % (K - 1) == 0) {
                    dp[start][end] += cost;
                }
            }
        }

        return dp[0][n - 1];
    }
};


//leetcode submit region end(Prohibit modification and deletion)
