//Given a set of distinct positive integers nums, return the largest subset answ
//er such that every pair (answer[i], answer[j]) of elements in this subset satisf
//ies: 
//
// 
// answer[i] % answer[j] == 0, or 
// answer[j] % answer[i] == 0 
// 
//
// If there are multiple solutions, return any of them. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,3]
//Output: [1,2]
//Explanation: [1,3] is also accepted.
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,4,8]
//Output: [1,2,4,8]
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 1000 
// 1 <= nums[i] <= 2 * 109 
// All the integers in nums are unique. 
// 
// Related Topics Array Math Dynamic Programming Sorting 
// 👍 2221 👎 103


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dp，接龙型dp
 * time: O(n*sqrt(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if (nums.empty() || nums.size() == 0) {
            return {};
        }

        sort(nums.begin(), nums.end());

        unordered_map<int, int> dp;
        unordered_map<int, int> prev;
        for (const auto& num : nums) {
            dp[num] = 1;
            prev[num] = -1;
        }

        int prev_num = nums[0];
        for (const auto& num : nums) {
            vector<int> factors = getFactors(num);
            for (auto &factor : factors) {
                auto it = dp.find(factor);
                if (it == dp.end()) {
                    continue;
                }
                if (dp[num] < dp[factor] + 1) {
                    dp[num] = dp[factor] + 1;
                    prev[num] = factor;
                }
            }
            if (dp[num] > dp[prev_num]) {
                prev_num = num;
            }
        }

        vector<int> res = getPath(prev, prev_num);
        return res;
    }

    // 不包括本身的因子集合
    vector<int> getFactors(int num) {
        vector<int> factors;
        if (num == 1) {
            return factors;
        }

        int factor = 1;
        while (factor * factor <= num) {
            if (num % factor == 0) {
                factors.push_back(factor);
                if (factor != 1 && (num / factor) != factor) {
                    factors.push_back(num / factor);
                }
            }
            factor++;
        }
        return factors;
    }

    vector<int> getPath(unordered_map<int, int>& prev, int prev_num) {
        vector<int> path;
        while (prev_num != -1) {
            path.push_back(prev_num);
            prev_num = prev[prev_num];
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
