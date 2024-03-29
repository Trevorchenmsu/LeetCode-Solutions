//Given an array of integers nums and an integer target, return indices of the t
//wo numbers such that they add up to target. 
//
// You may assume that each input would have exactly one solution, and you may n
//ot use the same element twice. 
//
// You can return the answer in any order. 
//
// 
// Example 1: 
//
// 
//Input: nums = [2,7,11,15], target = 9
//Output: [0,1]
//Output: Because nums[0] + nums[1] == 9, we return [0, 1].
// 
//
// Example 2: 
//
// 
//Input: nums = [3,2,4], target = 6
//Output: [1,2]
// 
//
// Example 3: 
//
// 
//Input: nums = [3,3], target = 6
//Output: [0,1]
// 
//
// 
// Constraints: 
//
// 
// 2 <= nums.length <= 103 
// -109 <= nums[i] <= 109 
// -109 <= target <= 109 
// Only one valid answer exists. 
// 
// Related Topics Array Hash Table 
// 👍 20494 👎 721

//Input: nums = [2,7,11,15], target = 9
//Output: [0,1]
//Output: Because nums[0] + nums[1] == 9, we return [0, 1].
//
//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table
 * time: O(n)
 * space: O(n)
 *
 * */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res = {-1, -1};
        unordered_map<int, int> num_map;

        for (int i = 0; i < nums.size(); i++) {
            auto it = num_map.find(target - nums[i]);
            if (it != num_map.end()) {
                res[0] = num_map[target - nums[i]];
                res[1] = i;
                return res;
            }

            num_map[nums[i]] = i;
        }

        return res;
    }
};

/*
 * solution 2: two pointers
 * time: O(nlogn)
 * space: O(n)
 *
 * */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> copy = nums;
        sort(nums.begin(), nums.end());

        int left = 0, right = nums.size() - 1;
        while (left < right) {
            if (nums[left] + nums[right] == target)
                break;
            else if (nums[left] + nums[right] > target)
                right--;
            else
                left++;
        }

        vector<int> res;
        for (int i = 0; i < copy.size(); i++) {
            if (copy[i] == nums[left] || copy[i] == nums[right])
                res.push_back(i);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
