//Today, the bookstore owner has a store open for customers.length minutes. Ever
//y minute, some number of customers (customers[i]) enter the store, and all those
// customers leave after the end of that minute. 
//
// On some minutes, the bookstore owner is grumpy. If the bookstore owner is gru
//mpy on the i-th minute, grumpy[i] = 1, otherwise grumpy[i] = 0. When the booksto
//re owner is grumpy, the customers of that minute are not satisfied, otherwise th
//ey are satisfied. 
//
// The bookstore owner knows a secret technique to keep themselves not grumpy fo
//r X minutes straight, but can only use it once. 
//
// Return the maximum number of customers that can be satisfied throughout the d
//ay. 
//
// 
//
// Example 1: 
//
// 
//Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], X = 3
//Output: 16
//Explanation: The bookstore owner keeps themselves not grumpy for the last 3 mi
//nutes. 
//The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 
//= 16.
// 
//
// 
//
// Note: 
//
// 
// 1 <= X <= customers.length == grumpy.length <= 20000 
// 0 <= customers[i] <= 1000 
// 0 <= grumpy[i] <= 1 
// Related Topics Array Sliding Window 
// 👍 700 👎 69

//Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], X = 3
//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution: sliding window
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int total = 0, increase = 0;
        int n = customers.size();

        // computer total satisfied customers
        for (int i = 0; i < n; i++) {
            if (grumpy[i] == 0)
                total += customers[i];
        }

        for (int i = 0; i < X; i++) {
            increase += customers[i] * grumpy[i];
        }

        int maxIncrease = increase;

        for (int i = X; i < n; i++) {
            // maintain window
            increase += customers[i] * grumpy[i];
            increase -= customers[i - X] * grumpy[i - X];
            maxIncrease = max(maxIncrease, increase);
        }

        return total + maxIncrease;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
