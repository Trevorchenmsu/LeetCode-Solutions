//Given an unsorted array of integers nums, return the length of the longest con
//secutive elements sequence. 
//
// You must write an algorithm that runs in O(n) time. 
//
// 
// Example 1: 
//
// 
//Input: nums = [100,4,200,1,3,2]
//Output: 4
//Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Theref
//ore its length is 4.
// 
//
// Example 2: 
//
// 
//Input: nums = [0,3,7,2,5,8,4,6,0,1]
//Output: 9
// 
//
// 
// Constraints: 
//
// 
// 0 <= nums.length <= 105 
// -109 <= nums[i] <= 109 
// 
// Related Topics Array Hash Table Union Find 
// 👍 6688 👎 309


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dfs + memo
 * time: O(n^2)
 * space: O(n)
 * */
class Solution:
        def minimumTotal(self, triangle: List[List[int]]) -> int:
        return self.divide_conquer(triangle, 0, 0, {})

        def divide_conquer(self, triangle, x, y, memo):
        if x == len(triangle):
        return 0

        if (x, y) in memo:
        return memo[(x, y)]

        left = self.divide_conquer(triangle, x + 1, y, memo)
        right = self.divide_conquer(triangle, x + 1, y + 1, memo)
        memo[(x, y)] = min(left, right) + triangle[x][y]

        return  memo[(x, y)]

/*
 * solution: dp, 自底向上
 * time: O(n^2)
 * space: O(n^2)
 * */

class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        dp = [[0] * (i + 1) for i in range(n)]


        // dp中初始化的位置就是找没有重叠的位置，自底向上的情况是在最底层没有重复位置，所以需要初始化
        for i in range(n):
            dp[n - 1][i] = triangle[n - 1][i]

        for i in range(n - 2, -1, -1):
            for j in range(i + 1):
                dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j]

        return dp[0][0]

/*
 * solution: dp, 自顶向下
 * time: O(n^2)
 * space: O(n^2)
 * */
class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        dp = [[0] * (i + 1) for i in range(n)]

        //没有重叠的部分需要初始化
        dp[0][0] = triangle[0][0]
        for i in range(1, n):
            dp[i][0] = dp[i - 1][0] + triangle[i][0]
            dp[i][i] = dp[i - 1][i - 1] + triangle[i][i]

        for i in range(2, n):
            for j in range(1, i):
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j]

        return min(dp[n - 1])
//leetcode submit region end(Prohibit modification and deletion)
