//Implement pow(x, n), which calculates x raised to the power n (i.e., xn). 
//
// 
// Example 1: 
//
// 
//Input: x = 2.00000, n = 10
//Output: 1024.00000
// 
//
// Example 2: 
//
// 
//Input: x = 2.10000, n = 3
//Output: 9.26100
// 
//
// Example 3: 
//
// 
//Input: x = 2.00000, n = -2
//Output: 0.25000
//Explanation: 2-2 = 1/22 = 1/4 = 0.25
// 
//
// 
// Constraints: 
//
// 
// -100.0 < x < 100.0 
// -231 <= n <= 231-1 
// -104 <= xn <= 104 
// 
// Related Topics Math Recursion 
// 👍 3135 👎 4358


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: exponential search
 * time: O(logn)
 * space: O(1)
 * */
class Solution {
public:
    double myPow(double x, int n) {
        if (n > 0) {
            return pow(x, n);
        }
        else {
            return 1.0 / pow(x, abs(n));
        }
    }

    double pow(double x, int n) {
        if (n == 0) {
            return 1;
        }

        double num = pow(x, n / 2);
        if (n % 2 == 0) {
            return num * num;
        }
        else {
            return num * num * x;
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
