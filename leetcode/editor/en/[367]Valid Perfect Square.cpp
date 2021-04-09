//Given a positive integer num, write a function which returns True if num is a 
//perfect square else False. 
//
// Follow up: Do not use any built-in library function such as sqrt. 
//
// 
// Example 1: 
// Input: num = 16
//Output: true
// Example 2: 
// Input: num = 14
//Output: false
// 
// 
// Constraints: 
//
// 
// 1 <= num <= 2^31 - 1 
// 
// Related Topics Math Binary Search 
// 👍 1194 👎 194


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: binary search
 * time: O(logn)
 * space: O(1)
 *
 * */
class Solution {
public:
    bool isPerfectSquare(int num) {
        long start = 1, end = num;

        while (start + 1 < end) {
            long mid = start + (end - start) / 2;
            if (mid * mid == num)
                return true;
            else if (mid * mid > num)
                end = mid;
            else
                start = mid;
        }

        if (start * start == num || end * end == num)
            return true;

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
