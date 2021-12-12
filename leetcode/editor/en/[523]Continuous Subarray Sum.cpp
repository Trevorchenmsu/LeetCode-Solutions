//Given an integer array nums and an integer k, return true if nums has a contin
//uous subarray of size at least two whose elements sum up to a multiple of k, or 
//false otherwise. 
//
// An integer x is a multiple of k if there exists an integer n such that x = n 
//* k. 0 is always a multiple of k. 
//
// 
// Example 1: 
//
// 
//Input: nums = [23,2,4,6,7], k = 6
//Output: true
//Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up t
//o 6.
// 
//
// Example 2: 
//
// 
//Input: nums = [23,2,6,4,7], k = 6
//Output: true
//Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elemen
//ts sum up to 42.
//42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
// 
//
// Example 3: 
//
// 
//Input: nums = [23,2,6,4,7], k = 13
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// 0 <= nums[i] <= 109 
// 0 <= sum(nums[i]) <= 231 - 1 
// 1 <= k <= 231 - 1 
// 
// Related Topics Array Hash Table Math Prefix Sum 
// 👍 645 👎 111


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: prefix sum + hash set
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (nums.empty() || nums.size() == 0) {
            return false;
        }

        unordered_set<int> remainder_set;
        int sum = 0, pre = 0;

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            auto it = remainder_set.find(sum % k);
            if (it != remainder_set.end()) {
                return true;
            }
            remainder_set.insert(pre);
            pre = sum % k;
        }

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
