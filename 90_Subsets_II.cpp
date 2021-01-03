/*
solution: backtracking
time: O(n*2^n)
space: O(n*2^n)
*/

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty() || nums.size() == 0)
            return res;
        
        vector<int> subset;
        sort(nums.begin(), nums.end());
        dfs(res, nums, subset, 0);
        return res;
    }
    
private:
    void dfs(vector<vector<int>>& res, vector<int>& nums, vector<int>& subset, int index) {
        res.push_back(subset);
        for (int i = index; i < nums.size(); ++i) {
            if (i != index && nums[i] == nums[i - 1] && i != 0) continue;
            subset.push_back(nums[i]);
            dfs(res, nums, subset, i + 1);
            subset.pop_back();
        }
    }
};