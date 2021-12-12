//Given a signed 32-bit integer x, return x with its digits reversed. If reversi
//ng x causes the value to go outside the signed 32-bit integer range [-231, 231 -
// 1], then return 0. 
//
// Assume the environment does not allow you to store 64-bit integers (signed or
// unsigned). 
//
// 
// Example 1: 
// Input: x = 123
//Output: 321
// Example 2: 
// Input: x = -123
//Output: -321
// Example 3: 
// Input: x = 120
//Output: 21
// Example 4: 
// Input: x = 0
//Output: 0
// 
// 
// Constraints: 
//
// 
// -231 <= x <= 231 - 1 
// 
// Related Topics Math 
// 👍 5370 👎 8035


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: implementation
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    int reverse(int x) {
        if (x == 0) {
            return 0;
        }

        int sign = 1;
        if (x < 0) {
            sign = -1;
        }

        string tmp = to_string(abs(x));
        string res = tmp.erase(0, tmp.find_first_not_of('0'));
        ::reverse(res.begin(), res.end());

        if (stol(res) > INT_MAX) {
            return 0;
        }

        int num = stoi(res) * sign;

        return num;
    }
};

/*
 * solution 2: implementation
 * time: O(n), n is the number of digits
 * space: O(1)
 *
 * */
class Solution {
public:
    int reverse(int x) {
        long res = 0;
        while (x != 0) {
            res = res * 10 + x % 10;
            x /= 10;

            if (res > INT_MAX || res < INT_MIN) {
                return 0;
            }
        }

        return (int) res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
