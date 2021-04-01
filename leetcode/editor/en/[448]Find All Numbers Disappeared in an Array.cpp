//Given an array nums of n integers where nums[i] is in the range [1, n], return
// an array of all the integers in the range [1, n] that do not appear in nums. 
//
// 
// Example 1: 
// Input: nums = [4,3,2,7,8,2,3,1]
//Output: [5,6]
// Example 2: 
// Input: nums = [1,1]
//Output: [2]
// 
// 
// Constraints: 
//
// 
// n == nums.length 
// 1 <= n <= 105 
// 1 <= nums[i] <= n 
// 
//
// 
// Follow up: Could you do it without extra space and in O(n) runtime? You may a
//ssume the returned list does not count as extra space. 
// Related Topics Array 
// 👍 4017 👎 290


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash set
 * time: O(n)
 * space: O(n)
 * */
//class Solution {
//public:
//    vector<int> findDisappearedNumbers(vector<int>& nums) {
//        vector<int> res;
//        if (nums.empty()) return res;
//
//        unordered_set<int> num_set(nums.begin(), nums.end());
//        for (int i = 1; i <= nums.size(); i++) {
//            if (num_set.count(i)) continue;
//            res.push_back(i);
//        }
//
//        return res;
//    }
//};


/*
 * solution 2: inplace
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        if (nums.empty()) return res;

        int n = nums.size();
        for (auto &num : nums) {
            int x = (num - 1) % n; // since some value may have been added by n
            nums[x] += n;
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] <= n)
                res.push_back(i + 1);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
