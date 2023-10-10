//Given a triangle array, return the minimum path sum from top to bottom. 
//
// For each step, you may move to an adjacent number of the row below. More form
//ally, if you are on index i on the current row, you may move to either index i o
//r index i + 1 on the next row. 
//
// 
// Example 1: 
//
// 
//Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
//Output: 11
//Explanation: The triangle looks like:
//   2
//  3 4
// 6 5 7
//4 1 8 3
//The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined abov
//e).
// 
//
// Example 2: 
//
// 
//Input: triangle = [[-10]]
//Output: -10
// 
//
// 
// Constraints: 
//
// 
// 1 <= triangle.length <= 200 
// triangle[0].length == 1 
// triangle[i].length == triangle[i - 1].length + 1 
// -104 <= triangle[i][j] <= 104 
// 
//
// 
//Follow up: Could you do this using only O(n) extra space, where n is the total
// number of rows in the triangle? Related Topics Array Dynamic Programming 
// 👍 5061 👎 386


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
