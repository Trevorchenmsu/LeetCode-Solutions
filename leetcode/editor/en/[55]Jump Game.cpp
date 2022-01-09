//Given an array of non-negative integers nums, you are initially positioned at 
//the first index of the array. 
//
// Each element in the array represents your maximum jump length at that positio
//n. 
//
// Determine if you are able to reach the last index. 
//
// 
// Example 1: 
//
// 
//Input: nums = [2,3,1,1,4]
//Output: true
//Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
// 
//
// Example 2: 
//
// 
//Input: nums = [3,2,1,0,4]
//Output: false
//Explanation: You will always arrive at index 3 no matter what. Its maximum jum
//p length is 0, which makes it impossible to reach the last index.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 3 * 104 
// 0 <= nums[i] <= 105 
// 
// Related Topics Array Greedy 
// 👍 6375 👎 427


//leetcode submit region begin(Prohibit modification and deletion)
// backtrack, O(2^n), TLE

/*
 * solution 0: backtrack + memo
 * time: O(n^2)，对每个元素，我们要查找后面有效的next nums[i]，最多只能到n个，走过的路会被memo记住，不会重复走。
 * space: O(n)
 * */
class Solution {
public:
    vector<int> memo;
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        memo = vector<int> (n);
        memo[n - 1] = 1;
        return canJumpFromPos(0, nums) == 1;
    }

    int canJumpFromPos(int pos, vector<int> &nums) {
        if (memo[pos] != 0)
            return memo[pos];
        int n = nums.size();
        int farthest = min(pos + nums[pos], n - 1);
        for (int next = pos + 1; next <= farthest; next++) {
            if (canJumpFromPos(next, nums) == 1) {
                memo[pos] = 1;
                return memo[pos];
            }
        }
        memo[pos] = -1;
        return memo[pos];
    }
};

/*
 * solution 1: top down dp, TLE
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.empty() || nums.size() == 0) {
            return false;
        }

        int n = nums.size();
        vector<int> dp(n);
        dp[0] = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                dp[i] = dp[j] && (nums[j] + j >= i);
                if (dp[i] == 1) {
                    break;
                }
            }
        }

        return dp[n - 1];
    }
};

/*
 * solution 2: greedy
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int max_val = 0;

        for(int i = 0; i < nums.size(); ++i){
            if(i > max_val) return false;
            max_val = max(max_val, nums[i] + i);
        }

        return true;
    }
};


/*
 * solution 3: bottom up dp
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = max(dp[i - 1], nums[i - 1]) - 1;
            if (dp[i] < 0) return false;
        }
        return true;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
