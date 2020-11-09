/*
solution: backtracking + memo
time: for each position, we can select k from n. The number of positions is n.
space: O(n!)
*/
class Solution {
private:
    void dfs(vector<vector<int>>& res, vector<int>& path, vector<int>& visited, vector<int>& nums){
        if(path.size() == nums.size()){
            res.push_back(path);
            return;
        }
        
        for(int i = 0; i < nums.size(); ++i){
            if (visited[i] || i > 0 && nums[i] == nums[i - 1] && !visited[i - 1])
                continue;
            visited[i] = 1;
            path.push_back(nums[i]);
            dfs(res, path, visited, nums);
            path.pop_back();
            visited[i] = 0;
        }
    }
    
    
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        if(nums.empty() || nums.size() == 0)
            return res;
        sort(nums.begin(), nums.end());
        vector<int> path;
        vector<int> visited(nums.size());
        dfs(res, path, visited, nums);
        return res;
    }
};