//You have an inventory of different colored balls, and there is a customer that
// wants orders balls of any color. 
//
// The customer weirdly values the colored balls. Each colored ball's value is t
//he number of balls of that color you currently have in your inventory. For examp
//le, if you own 6 yellow balls, the customer would pay 6 for the first yellow bal
//l. After the transaction, there are only 5 yellow balls left, so the next yellow
// ball is then valued at 5 (i.e., the value of the balls decreases as you sell mo
//re to the customer). 
//
// You are given an integer array, inventory, where inventory[i] represents the 
//number of balls of the ith color that you initially own. You are also given an i
//nteger orders, which represents the total number of balls that the customer want
//s. You can sell the balls in any order. 
//
// Return the maximum total value that you can attain after selling orders color
//ed balls. As the answer may be too large, return it modulo 109 + 7. 
//
// 
// Example 1: 
//
// 
//Input: inventory = [2,5], orders = 4
//Output: 14
//Explanation: Sell the 1st color 1 time (2) and the 2nd color 3 times (5 + 4 + 
//3).
//The maximum total value is 2 + 5 + 4 + 3 = 14.
// 
//
// Example 2: 
//
// 
//Input: inventory = [3,5], orders = 6
//Output: 19
//Explanation: Sell the 1st color 2 times (3 + 2) and the 2nd color 4 times (5 +
// 4 + 3 + 2).
//The maximum total value is 3 + 2 + 5 + 4 + 3 + 2 = 19.
// 
//
// Example 3: 
//
// 
//Input: inventory = [2,8,4,10,6], orders = 20
//Output: 110
// 
//
// Example 4: 
//
// 
//Input: inventory = [1000000000], orders = 1000000000
//Output: 21
//Explanation: Sell the 1st color 1000000000 times for a total value of 50000000
//0500000000. 500000000500000000 modulo 109 + 7 = 21.
// 
//
// 
// Constraints: 
//
// 
// 1 <= inventory.length <= 105 
// 1 <= inventory[i] <= 109 
// 1 <= orders <= min(sum(inventory[i]), 109) 
// 
// Related Topics Math Greedy Sort 
// 👍 311 👎 82


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        sort(inventory.begin(), inventory.end());
        reverse(inventory.begin(), inventory.end());
        int n = inventory.size();
        inventory.push_back(0);
        long long M = 1e9+7;

        long long ret = 0;
        for (int i=0; i<n; i++)
        {
            long long a = inventory[i];
            long long b = inventory[i+1];
            long long total = (a-b)*(i+1);

            if (total <= (long long)orders)
            {
                ret += (a+b+1)*(a-b)/2*(i+1);
                orders -= total;
                ret %= M;
            }
            else
            {
                long long k = orders/(i+1);
                ret += (a+a-k+1)*k/2*(i+1);
                ret %= M;

                long long m = orders%(i+1);
                ret += (a-k)*m;
                ret %= M;
                break;
            }
            if (orders<=0) break;
        }
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
