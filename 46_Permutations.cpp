/*
solution 1: +backno memo
time:
space: O(n!), we need to store all the permutaions.
*/

class Solution {
private:
    void backtrack(vector<vector<int>>& res, vector<int>& nums, vector<int>& list){
        if(list.size() == nums.size()){
            res.push_back(list);
            return;
        }
        
        for(int i = 0; i < nums.size(); ++i){
            if(find(list.begin(), list.end(), nums[i]) != list.end())
                continue;
            list.push_back(nums[i]);
            backtrack(res, nums, list);
            list.pop_back();
        }
    }
    
    
public:
    vector<vector<int>> permute(vector<int>& nums) {
        // edge case
        vector<vector<int>> res;
        if(nums.empty() || nums.size() == 0)
            return res;
        vector<int> list;
        backtrack(res, nums, list);
        return res;
    }
};

/*
solution 2:  memo
time:
space: O(n!), we need to store all the permutaions.
*/
class Solution {
private:
    void dfs(vector<vector<int>>& res, vector<int>& path, vector<int>& visited, vector<int>& nums){
        if(path.size() == nums.size()){
            res.push_back(path);
            return;
        }
        
        for(int i = 0; i < nums.size(); ++i){
            if(!visited[i]){
                visited[i] = 1;
                path.push_back(nums[i]);
                dfs(res, path, visited, nums);
                path.pop_back();
                visited[i] = 0;
            }
        }
    }
    
    
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        if(nums.empty() || nums.size() == 0)
            return res;
        vector<int> path;
        vector<int> visited(nums.size());
        dfs(res, path, visited, nums);
        return res;
    }
};