//Given an integer array nums where every element appears three times except for
// one, which appears exactly once. Find the single element and return it. 
//
// You must implement a solution with a linear runtime complexity and use only c
//onstant extra space. 
//
// 
// Example 1: 
// Input: nums = [2,2,3,2]
//Output: 3
// Example 2: 
// Input: nums = [0,1,0,1,0,1,99]
//Output: 99
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 3 * 104 
// -231 <= nums[i] <= 231 - 1 
// Each element in nums appears exactly three times except for one element which
// appears once. 
// 
// Related Topics Array Bit Manipulation 
// 👍 4477 👎 501


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: bit manipulation
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        /* 考虑每个整数的32个bit,eg.[2,2,3,2]，(nums[j] >> i) & 1的操作相当
         * 于一步步右移整数的位来实现考虑每个bit。
         * 在i=0时，考虑第一位。所以3个2中的第一位都是0，因为2的32位为0000...10,而3的第一位则为1，因为3的为00...11
         * 则遍历整个数据后得到sum为1。所以sum模1结果为1，同时i=0，没有左移回去。这里结果res取或，目的就是将一个个的1求回来
         * 所以现在的res结果为00....1。在i=1时，nums都要右移动一位，3个2中第一位都变成了1，与1求与后仍然为1，所以3个2的和为3
         * 3右移一位后与1求与的结果也是1，所以sum总和为4，对3求模结果为1。此时的i=1左移就生效了，因此结果是00...10
         * 由于前面得到的res是00...1，跟现在的结果00...10，求或操作就可以结合两个1，变成了00...11，所以结果是3
         * */
        for (int i = 0; i < 32; ++i) {
            int sum = 0;
            for (int j = 0; j < nums.size(); ++j) {
                sum += (nums[j] >> i) & 1;
            }
            res |= (sum % 3) << i;
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
