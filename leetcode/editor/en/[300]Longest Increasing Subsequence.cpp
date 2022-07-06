//Given an integer array nums, return the length of the longest strictly increas
//ing subsequence. 
//
// A subsequence is a sequence that can be derived from an array by deleting som
//e or no elements without changing the order of the remaining elements. For examp
//le, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7]. 
//
// 
// Example 1: 
//
// 
//Input: nums = [10,9,2,5,3,7,101,18]
//Output: 4
//Explanation: The longest increasing subsequence is [2,3,7,101], therefore the 
//length is 4.
// 
//
// Example 2: 
//
// 
//Input: nums = [0,1,0,3,2,3]
//Output: 4
// 
//
// Example 3: 
//
// 
//Input: nums = [7,7,7,7,7,7,7]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 2500 
// -104 <= nums[i] <= 104 
// 
//
// 
// Follow up: Can you come up with an algorithm that runs in O(n log(n)) time co
//mplexity? 
// Related Topics Array Binary Search Dynamic Programming 
// 👍 8436 👎 182


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: 1D DP
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty() || nums.size() == 0) return 0;
        int n = nums.size();
        vector<int> dp(n, 1);
        int res = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }

        return res;
    }
};
class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0

        n = len(nums)
        dp = [1] * n
        res = 0

        for i in range(n):
            for j in range(0, i):
                if nums[i] > nums[j]:
                    dp[i] = max(dp[i], dp[j] + 1)
            res = max(res, dp[i])

    return res

/*
 * solution 2: insertion/patience sort + binary search
 * time: O(nlogn)
 * space: O(n)
 * */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> LIS;

        for (auto &num : nums)
        {
            auto it = lower_bound(LIS.begin(), LIS.end(), num);
            if (it == LIS.end())
            {
                LIS.push_back(num);
            }
            else
            {
                *it = num;
            }
        }

        return LIS.size();
    }
};

//leetcode submit region end(Prohibit modification and deletion)
