/*
solution 1: dp
time: O(n)
space: O(n)
*/
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        if (nums.empty()) return nums;
        
        int n = nums.size();
        vector<int> left(n);
        vector<int> right(n);
        vector<int> res(n);
        
        left[0] = 1;
        for (int i = 1; i < n; i++) {
            left[i] = left[i - 1] * nums[i - 1];
        }
        
        right[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            right[i] = nums[i + 1] * right[i + 1];
        }
        
        for (int i = 0 ; i < n; i++) {
            res[i] = left[i] * right[i];
        }
        
        return res;
    }
};


/*
solution 2: dp
time: O(n)
space: O(1)
*/
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        if (nums.empty()) return nums;
        
        int n = nums.size();
        vector<int> dp(n); // dp[i]表示在i位置的其他元素的乘积
        dp[0] = 1;
        
        // 表示当前位置左边所有元素的乘积
        for (int i = 1; i < n; i++) {
            dp[i] = dp[i - 1] * nums[i - 1];
        }
        
        // 表示当前位置右边所有元素的乘积。需要采用right来记录乘积的情况，再把累积的乘积乘上上面左边得到的乘积
        int right = 1;
        for (int i = n - 1; i >= 0; i--) {
            dp[i] *= right;
            right *= nums[i];
        }
        
        return dp;
    }
};
