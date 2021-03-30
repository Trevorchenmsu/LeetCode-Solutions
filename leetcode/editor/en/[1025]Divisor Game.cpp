//Alice and Bob take turns playing a game, with Alice starting first. 
//
// Initially, there is a number n on the chalkboard. On each player's turn, that
// player makes a move consisting of: 
//
// 
// Choosing any x with 0 < x < n and n % x == 0. 
// Replacing the number n on the chalkboard with n - x. 
// 
//
// Also, if a player cannot make a move, they lose the game. 
//
// Return true if and only if Alice wins the game, assuming both players play op
//timally. 
//
// 
// Example 1: 
//
// 
//Input: n = 2
//Output: true
//Explanation: Alice chooses 1, and Bob has no more moves.
// 
//
// Example 2: 
//
// 
//Input: n = 3
//Output: false
//Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 1000 
// 
// Related Topics Math Dynamic Programming 
// 👍 719 👎 1965


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool divisorGame(int n) {
        vector<int> f(n + 5, false);

        f[1] = false;
        f[2] = true;
        for (int i = 3; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                if (i % j == 0 && !f[i - j]) {
                    f[i] = true;
                    break;
                }
            }
        }

        return f[n];

    }
};
//leetcode submit region end(Prohibit modification and deletion)
