//Given an integer array nums, in which exactly two elements appear only once an
//d all the other elements appear exactly twice. Find the two elements that appear
// only once. You can return the answer in any order. 
//
// You must write an algorithm that runs in linear runtime complexity and uses o
//nly constant extra space. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,1,3,2,5]
//Output: [3,5]
//Explanation:  [5, 3] is also a valid answer.
// 
//
// Example 2: 
//
// 
//Input: nums = [-1,0]
//Output: [-1,0]
// 
//
// Example 3: 
//
// 
//Input: nums = [0,1]
//Output: [1,0]
// 
//
// 
// Constraints: 
//
// 
// 2 <= nums.length <= 3 * 104 
// -231 <= nums[i] <= 231 - 1 
// Each integer in nums will appear twice, only two integers will appear once. 
// 
// Related Topics Array Bit Manipulation 
// 👍 3530 👎 175


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unsigned diff = 0;
        for(int num:nums){
            diff ^= num;
        }
        diff &= -diff;
        vector<int> res(2, 0);
        for(int num:nums){
            if((num & diff) == 0){
                res[0] ^= num;
            }
            else res[1] ^= num;
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
