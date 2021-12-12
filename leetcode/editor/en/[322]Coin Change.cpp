//You are given an integer array coins representing coins of different denominat
//ions and an integer amount representing a total amount of money. 
//
// Return the fewest number of coins that you need to make up that amount. If th
//at amount of money cannot be made up by any combination of the coins, return -1.
// 
//
// You may assume that you have an infinite number of each kind of coin. 
//
// 
// Example 1: 
//
// 
//Input: coins = [1,2,5], amount = 11
//Output: 3
//Explanation: 11 = 5 + 5 + 1
// 
//
// Example 2: 
//
// 
//Input: coins = [2], amount = 3
//Output: -1
// 
//
// Example 3: 
//
// 
//Input: coins = [1], amount = 0
//Output: 0
// 
//
// Example 4: 
//
// 
//Input: coins = [1], amount = 1
//Output: 1
// 
//
// Example 5: 
//
// 
//Input: coins = [1], amount = 2
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// 1 <= coins.length <= 12 
// 1 <= coins[i] <= 231 - 1 
// 0 <= amount <= 104 
// 
// Related Topics Array Dynamic Programming Breadth-First Search 
// 👍 7580 👎 207


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dp
 * time: O(mn), m is the number of the coins, n is the total amount.
 * space: O(n)
 * */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < coins.size(); j++) {
                if (i < coins[j]) {
                    continue;
                }
                //状态转移方程可以这样思考：既然dp[i]是当数额为i时的最小硬币数，那它是怎样从上一个状态达到当前的状态的？肯定是添加了一个
                // 硬币。但是我们不知道是哪个硬币，所以需要遍历所有硬币，即coins[j]，加入一个硬币就得到了dp[i]，所以有dp[i]=dp[i-coins[j]]+1
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }

        // dp[amount]最大数只能是amount，即每一次都拿1元的硬币，所以大于的话就不合理了。
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
