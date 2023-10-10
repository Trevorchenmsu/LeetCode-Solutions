//Given an integer array nums of length n where all the integers of nums are in 
//the range [1, n] and each integer appears once or twice, return an array of all 
//the integers that appears twice. 
//
// You must write an algorithm that runs in O(n) time and uses only constant ext
//ra space. 
//
// 
// Example 1: 
// Input: nums = [4,3,2,7,8,2,3,1]
//Output: [2,3]
// Example 2: 
// Input: nums = [1,1,2]
//Output: [1]
// Example 3: 
// Input: nums = [1]
//Output: []
// 
// 
// Constraints: 
//
// 
// n == nums.length 
// 1 <= n <= 105 
// 1 <= nums[i] <= n 
// Each element in nums appears once or twice. 
// 
// Related Topics Array Hash Table 
// 👍 6128 👎 249


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: in-place flip
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        if (nums.empty() || nums.size() == 0) {
            return res;
        }

        /*
         * 核心思想：注意题目条件保证nums[i]一定在[1,n]范围内，所以nums[i]-1作为index一定存在。因此每一次我们都对这个index进行flip
         * 如果元素只出现一次，那么index位置的元素被flip为负数后，后面遍历不会再遇到这个，所以不需要加入结果。如果元素出现两次，因为第一次
         * 的时候已经将元素flip了，所以第二次遇到的时候是负数，因此判定为<0即可加入结果。
         * */

        for (auto i = 0; i < nums.size(); ++i) {
            int idx = abs(nums[i]) - 1;

            if (nums[idx] < 0) {
                res.push_back(abs(nums[i]));
            }
            else {
                nums[idx] = -nums[idx];
            }
        }

        return res;
    }
};


class Solution:
    def findDuplicates(self, nums: List[int]) -> List[int]:
        if nums is None: return None

        res = []

        for i in range(len(nums)):
            idx = abs(nums[i]) - 1
            if nums[idx] < 0:
            res.append(abs(nums[i]))
            else:
            nums[idx] = -nums[idx]

    return res
//leetcode submit region end(Prohibit modification and deletion)
