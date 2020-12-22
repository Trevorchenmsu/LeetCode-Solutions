/*
solution 1: dp, top down
time: O(n^2)
space: O(n)
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.empty() || nums.size() == 0)
            return false;
        
        int n = nums.size();
        
        // dp[i] indicates the bool state whether it can jump from 0 to i
        vector<int> dp(n);
        
        // initilazition
        dp[0] = true;
        
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && nums[j] + j >= i) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n - 1];
    }
};

