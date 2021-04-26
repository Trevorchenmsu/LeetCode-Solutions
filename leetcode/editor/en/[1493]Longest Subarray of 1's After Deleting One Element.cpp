//Given a binary array nums, you should delete one element from it. 
//
// Return the size of the longest non-empty subarray containing only 1's in the 
//resulting array. 
//
// Return 0 if there is no such subarray. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,1,0,1]
//Output: 3
//Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbe
//rs with value of 1's. 
//
// Example 2: 
//
// 
//Input: nums = [0,1,1,1,0,1,1,0,1]
//Output: 5
//Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1] longes
//t subarray with value of 1's is [1,1,1,1,1]. 
//
// Example 3: 
//
// 
//Input: nums = [1,1,1]
//Output: 2
//Explanation: You must delete one element. 
//
// Example 4: 
//
// 
//Input: nums = [1,1,0,0,1,1,1,0,1]
//Output: 4
// 
//
// Example 5: 
//
// 
//Input: nums = [0,0,0]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 10^5 
// nums[i] is either 0 or 1. 
// 
// Related Topics Array 
// 👍 393 👎 7


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: sliding window, shrinkable
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int left = 0, right = 0;
        int cnt = 0, res = 0, n = nums.size();

        while (right < n) {
            cnt += nums[right] == 0;
            while (cnt > 1)
                cnt -= nums[left++] == 0;
            res = max(res, right - left);
            right++;
        }

        return res;
    }
};

/*
 * solution 2: sliding window, non-shrinkable
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int left = 0, right = 0;
        int cnt = 0, n = nums.size();

        while (right < n) {
            cnt += nums[right] == 0;
            if (cnt > 1)
                cnt -= nums[left++] == 0;
            right++;
        }

        return right - left - 1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
