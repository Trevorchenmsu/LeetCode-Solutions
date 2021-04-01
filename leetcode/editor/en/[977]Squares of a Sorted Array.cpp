//Given an integer array nums sorted in non-decreasing order, return an array of
// the squares of each number sorted in non-decreasing order. 
//
// 
// Example 1: 
//
// 
//Input: nums = [-4,-1,0,3,10]
//Output: [0,1,9,16,100]
//Explanation: After squaring, the array becomes [16,1,0,9,100].
//After sorting, it becomes [0,1,9,16,100].
// 
//
// Example 2: 
//
// 
//Input: nums = [-7,-3,2,3,11]
//Output: [4,9,9,49,121]
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 104 
// -104 <= nums[i] <= 104 
// nums is sorted in non-decreasing order. 
// 
//
// 
//Follow up: Squaring each element and sorting the new array is very trivial, co
//uld you find an O(n) solution using a different approach? Related Topics Array T
//wo Pointers 
// 👍 2190 👎 114


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: two pointers
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        if (nums.empty()) return {};
        vector<int> res(nums.size(), 0);

        int left = 0, right = nums.size() - 1, idx = nums.size() - 1;
        while (left <= right) {
            int left_square = nums[left] * nums[left];
            int right_square = nums[right] * nums[right];
            if ( right_square > left_square) {
                res[idx--] = right_square;
                right--;
            }
            else {
                res[idx--] = left_square;
                left++;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
