//You have a total of n coins that you want to form in a staircase shape, where 
//every k-th row must have exactly k coins. 
// 
// Given n, find the total number of full staircase rows that can be formed. 
//
// n is a non-negative integer and fits within the range of a 32-bit signed inte
//ger. 
//
// Example 1:
// 
//n = 5
//
//The coins can form the following rows:
//¤
//¤ ¤
//¤ ¤
//
//Because the 3rd row is incomplete, we return 2.
// 
// 
//
// Example 2:
// 
//n = 8
//
//The coins can form the following rows:
//¤
//¤ ¤
//¤ ¤ ¤
//¤ ¤
//
//Because the 4th row is incomplete, we return 3.
// 
// Related Topics Math Binary Search 
// 👍 913 👎 789


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: math
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    int arrangeCoins(int n) {
        if (n <= 1) return n;

        int cnt = 0;

        while (n >= 0) {
            cnt++;
            n -= cnt;
        }

        return cnt - 1;
    }
};


/*
 * solution 2: binary search
 * time: O(logn)
 * space: O(1)
 *
 * */
class Solution {
public:
    int arrangeCoins(int n) {
        if (n <= 1) return n;

        long start = 1, end = n;
        while (start + 1 < end) {
            long mid = start + (end - start) / 2;
            long sum = mid * (mid + 1) / 2;
            if (sum > n)
                end = mid;
            else
                start = mid;
        }

        if (end * (end + 1) / 2 < n)
            return (int) end;

        return (int) start;
    }

};
//leetcode submit region end(Prohibit modification and deletion)
