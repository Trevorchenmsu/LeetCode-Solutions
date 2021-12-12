//You are given an integer array coins representing coins of different denominat
//ions and an integer amount representing a total amount of money. 
//
// Return the number of combinations that make up that amount. If that amount of
// money cannot be made up by any combination of the coins, return 0. 
//
// You may assume that you have an infinite number of each kind of coin. 
//
// The answer is guaranteed to fit into a signed 32-bit integer. 
//
// 
// Example 1: 
//
// 
//Input: amount = 5, coins = [1,2,5]
//Output: 4
//Explanation: there are four ways to make up the amount:
//5=5
//5=2+2+1
//5=2+1+1+1
//5=1+1+1+1+1
// 
//
// Example 2: 
//
// 
//Input: amount = 3, coins = [2]
//Output: 0
//Explanation: the amount of 3 cannot be made up just with coins of 2.
// 
//
// Example 3: 
//
// 
//Input: amount = 10, coins = [10]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// 1 <= coins.length <= 300 
// 1 <= coins[i] <= 5000 
// All the values of coins are unique. 
// 0 <= amount <= 5000 
// 
// Related Topics Array Dynamic Programming 
// 👍 3966 👎 86


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: 坐标型dp，01背包型
 * time: O(nC), n为coin个数，C为容量大小
 * space: O(nC)
 * */
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int size = coins.size();
        vector<vector<int>> dp(size + 1, vector<int> (amount + 1));
        dp[0][0] = 1;

        for (int i = 1; i < size + 1; i++) {
            dp[i][0] = 1;
            for (int j = 1; j < amount + 1; j++) {
                dp[i][j] = dp[i - 1][j] + (j >= coins[i - 1] ? dp[i][j - coins[i - 1]] : 0);
            }
        }


        return dp[size][amount];
    }
};

/*
 * solution 2: 坐标型dp，01背包型
 * time: O(nC), n为coin个数，C为容量大小
 * space: O(C)
 * */
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int>dp(amount + 1,0);
        dp[0] = 1;
        for (int i = 0; i < coins.size(); i++)
        {
            for (int c = 1; c <= amount; c++)
            {
                if (c >= coins[i])
                    dp[c] += dp[c - coins[i]];
            }
        }

        return dp[amount];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
