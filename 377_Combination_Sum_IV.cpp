/*
Solution 1: DFS + memo
time: 
space:
*/

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        if (nums.empty() || nums.size() == 0) 
            return 0;
        
        sort(nums.begin(), nums.end());
        int len = target / nums[0] + 1;
        vector<vector<int>> memo(len, vector<int> (target + 1, -1));
        return dfs(nums, 0, target, 0, memo);
    }
    
    int dfs(vector<int>& nums,
             int start,
             int target,
             int index,
             vector<vector<int>>& memo) {
        
        int& res = memo[index][start];
        if (res != -1) return res;
        res = 0;
        
        if (start == target) {
            ++res;
            return res;
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            int temp = start + nums[i];
            if (temp > target) break;
            res += dfs(nums, temp, target, index + 1, memo);
        }
        
        return res;
    }
};

/*
Solution 2: DP + memo
time: 
space:
*/