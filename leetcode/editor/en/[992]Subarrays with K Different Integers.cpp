//Given an integer array nums and an integer k, return the number of good subarr
//ays of nums. 
//
// A good array is an array where the number of different integers in that array
// is exactly k. 
//
// 
// For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3. 
// 
//
// A subarray is a contiguous part of an array. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,1,2,3], k = 2
//Output: 7
//Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1],
// [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,1,3,4], k = 3
//Output: 3
//Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2
//,1,3], [1,3,4].
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 2 * 104 
// 1 <= nums[i], k <= nums.length 
// 
// Related Topics Array Hash Table Sliding Window Counting 
// 👍 2287 👎 31


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sliding window
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }

    int atMost(vector<int> &nums, int k) {
        int res = 0, left = 0;
        unordered_map<int, int> num2cnt;

        for (int right = 0; right < nums.size(); right++) {
            if (num2cnt[nums[right]] == 0) {
                k--;
            }

            num2cnt[nums[right]]++;

            while (k < 0) {
                num2cnt[nums[left]]--;
                if (num2cnt[nums[left]] == 0) {
                    k++;
                }
                left++;
            }

            res += right - left + 1;
        }

        return res;
    }
};


//leetcode submit region end(Prohibit modification and deletion)
