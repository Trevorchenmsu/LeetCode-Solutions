//Given an unsorted integer array nums, return the smallest missing positive int
//eger. 
//
// You must implement an algorithm that runs in O(n) time and uses constant extr
//a space. 
//
// 
// Example 1: 
// Input: nums = [1,2,0]
//Output: 3
// Example 2: 
// Input: nums = [3,4,-1,1]
//Output: 2
// Example 3: 
// Input: nums = [7,8,9,11,12]
//Output: 1
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 5 * 105 
// -231 <= nums[i] <= 231 - 1 
// 
// Related Topics Array Hash Table 
// 👍 7254 👎 1137


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: bucket sort
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            int j = i + 1;
            while (j < nums.size() && i + 1 != nums[i]) {
                swap(nums[i], nums[j++]);
            }
        }

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return nums.size() + 1;
    }
};

/*
 * solution 2: bucket sort
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        nums.insert(nums.begin(), 0);
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != i && nums[i] < nums.size() && nums[i] != nums[nums[i]])
                swap(nums[i], nums[nums[i]]);
        }

        for (int i = 1; i < nums.size(); i++)
            if (nums[i] != i) {
                return i;
            }

        return nums.size();
    }
};
//leetcode submit region end(Prohibit modification and deletion)
