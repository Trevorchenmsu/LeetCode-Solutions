//Given two integers dividend and divisor, divide two integers without using mul
//tiplication, division, and mod operator. 
//
// Return the quotient after dividing dividend by divisor. 
//
// The integer division should truncate toward zero, which means losing its frac
//tional part. For example, truncate(8.345) = 8 and truncate(-2.7335) = -2. 
//
// Note: Assume we are dealing with an environment that could only store integer
//s within the 32-bit signed integer range: [−231, 231 − 1]. For this problem, ass
//ume that your function returns 231 − 1 when the division result overflows. 
//
// 
// Example 1: 
//
// 
//Input: dividend = 10, divisor = 3
//Output: 3
//Explanation: 10/3 = truncate(3.33333..) = 3.
// 
//
// Example 2: 
//
// 
//Input: dividend = 7, divisor = -3
//Output: -2
//Explanation: 7/-3 = truncate(-2.33333..) = -2.
// 
//
// Example 3: 
//
// 
//Input: dividend = 0, divisor = 1
//Output: 0
// 
//
// Example 4: 
//
// 
//Input: dividend = 1, divisor = 1
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// -231 <= dividend, divisor <= 231 - 1 
// divisor != 0 
// 
// Related Topics Math Bit Manipulation 
// 👍 2195 👎 7948


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: bit manipulation / exponential search
 * time: O((logn)^2)
 * space: O(1)
 *
 * */

class Solution {
public:
    int divide(int dividend, int divisor) {
        long ldividend = labs(dividend), ldivisor = labs(divisor), res = 0;

        if (ldividend < ldivisor) {
            return 0;
        }

        long sum = ldivisor, quotient = 1;

        // 既然无法用乘除模三种运算，只能用加法或者位运算。如果用加法，不能一个一个divisor的添加，否则会TLE
        // 每次添加应该是sum+sum的添加，本质是2*sum，所以跟位运算左移一位本质上是一样的。
        // 这里的复杂度类似二分O(logn)
        while ((sum << 1) < ldividend) {
            sum <<= 1;
            quotient <<= 1;
        }

        // 当两倍sum大于被除数时，被除数是不够除的，所以减去当前sum，再回去重新计算剩余的新的商
        // 递归这里再进行新一层的计算，复杂度为O((logn)^2)
        res += quotient + divide(ldividend - sum, ldivisor);

        if ((dividend < 0) ^ (divisor < 0)) {
            res = -res;
        }

        return res > INT_MAX ? INT_MAX : res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
