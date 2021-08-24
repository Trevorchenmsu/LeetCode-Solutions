//Given an integer array nums, move all 0's to the end of it while maintaining t
//he relative order of the non-zero elements. 
//
// Note that you must do this in-place without making a copy of the array. 
//
// 
// Example 1: 
// Input: nums = [0,1,0,3,12]
//Output: [1,3,12,0,0]
// Example 2: 
// Input: nums = [0]
//Output: [0]
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 104 
// -231 <= nums[i] <= 231 - 1 
// 
//
// 
//Follow up: Could you minimize the total number of operations done? Related Top
//ics Array Two Pointers 
// 👍 5395 👎 169

// Example 1:
// Input: nums = [0,1,0,3,12]
//Output: [1,3,12,0,0]
//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two pointers
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int left = 0, right = 0;
        while (right < nums.size()) {
            if (nums[right] != 0)
                swap(nums[left++], nums[right++]);
            else right++;
        }
    }
};


/*
 * solution 2: two pointers
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int left = 0, right = 0;
        while (right < nums.size()) {
            if (nums[right] != 0)
                nums[left++] = nums[right++];
            else
                right++;
        }

        while(left < nums.size()){
            nums[left++] = 0;
        }
    }
};


//leetcode submit region end(Prohibit modification and deletion)
