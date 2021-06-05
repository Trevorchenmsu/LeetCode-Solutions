//You are given three positive integers: n, index, and maxSum. You want to const
//ruct an array nums (0-indexed) that satisfies the following conditions: 
//
// 
// nums.length == n 
// nums[i] is a positive integer where 0 <= i < n. 
// abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1. 
// The sum of all the elements of nums does not exceed maxSum. 
// nums[index] is maximized. 
// 
//
// Return nums[index] of the constructed array. 
//
// Note that abs(x) equals x if x >= 0, and -x otherwise. 
//
// 
// Example 1: 
//
// 
//Input: n = 4, index = 2,  maxSum = 6
//Output: 2
//Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
//There are no arrays that satisfy all the conditions and have nums[2] == 3, so 
//2 is the maximum nums[2].
// 
//
// Example 2: 
//
// 
//Input: n = 6, index = 1,  maxSum = 10
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= maxSum <= 109 
// 0 <= index < n 
// 
// Related Topics Binary Search Greedy 
// 👍 273 👎 43


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxValue(int n, int index, int maxSum)
    {
        int left = 1, right = maxSum;
        while (left < right)
        {
            int mid = right - (right-left)/2;
            if (count(mid, n, index) <= (long)maxSum)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    long count(long h, long n, long index)
    {
        long sum = 0;
        if (h > index)
        {
            sum += (h-index + h)*(index+1)/2;
        }
        else
        {
            sum += (1+h)*h/2;
            sum += index+1-h;
        }
        if (h > n-index)
        {
            sum += (h + h-(n-index)+1)*(n-index)/2;
        }
        else
        {
            sum += (h + 1)*h/2;
            sum += (n - (index+h));
        }
        return sum-h;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
