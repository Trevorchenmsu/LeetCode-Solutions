//Given an integer array nums and an integer k, return true if there are two dis
//tinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <
//= k. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,3,1], k = 3
//Output: true
// 
//
// Example 2: 
//
// 
//Input: nums = [1,0,1,1], k = 1
//Output: true
// 
//
// Example 3: 
//
// 
//Input: nums = [1,2,3,1,2,3], k = 2
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// -109 <= nums[i] <= 109 
// 0 <= k <= 105 
// 
// Related Topics Array Hash Table 
// 👍 1275 👎 1370


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: hash table
 * time: O(mn), m is the number of distinct elements. n is the largest number of duplicate elements
 * space: O(m)
 * */
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        if (nums.empty()) return false;

        unordered_map<int, vector<int>> cnt;
        for (int i = 0; i < nums.size(); i++) {
            cnt[nums[i]].push_back(i);
        }

        for (auto &[num, idx_arr] : cnt) {
            if (idx_arr.size() == 1) continue;
            for (int i = 1; i < idx_arr.size(); i++) {
                if (idx_arr[i] - idx_arr[i - 1] <= k)
                    return true;
            }
        }

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
