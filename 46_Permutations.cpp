/*
solution 1: backtrack
time: O(n*n!)
space: O(n*n!)
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
solution 2:  backtrack + memo
time: O(n*n!)
space: O(n*n!)
*/
class Solution {
private:
    void dfs(vector<vector<int>>& res, vector<int>& path, vector<int>& visited, vector<int>& nums){
        if(path.size() == nums.size()){
            res.push_back(path);
            return;
        }
        
        for(int i = 0; i < nums.size(); ++i){
            if (visited[i]) continue;
            visited[i] = 1;
            path.push_back(nums[i]);
            dfs(res, path, visited, nums);
            path.pop_back();
            visited[i] = 0;
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

/*
solution 3:  poling board method （插板法）iterative
time: O(n*n!)
space: O(n*n!)
*/
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        queue<vector<int>> q;
        q.push({nums[0]});

        for (int i = 1; i < nums.size(); ++i) {
            int len = q.size();
            while (len--) {
                auto arr = q.front();
                q.pop();

                // insert the element to all the gaps
                int M = arr.size();
                for (int j = 0; j <= M; ++j) {
                    auto temp = arr;
                    temp.insert(temp.begin() + j, nums[i]);
                    q.push(temp);
                }
            }
        }

        vector<vector<int>> res;
        while (!q.empty()) {
            res.push_back(q.front());
            q.pop();
        }
        return res;
    }
};