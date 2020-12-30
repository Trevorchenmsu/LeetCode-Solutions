/*
solution 1 : backtracking/DFS, recursion
time: O(n*2^n)
space: O(n*2^n) for the solution, O(n) for the stack space as each time we will 
store maximum n element in the stack and pop out later. 
*/
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty() || nums.size() == 0)
            return res;
        vector<int> subset;
        dfs(res, nums, subset, 0);
        return res;
    }
private:
    void dfs(vector<vector<int>> &res, vector<int> &nums, vector<int> &subset, int index) {
        res.push_back(subset);
        for (int i = index; i < nums.size(); ++i) {
            subset.push_back(nums[i]);
            dfs(res, nums, subset, i + 1);
            subset.pop_back();
        }
    }
};

/*
solution 1 : BFS
time: O(n*2^n)
space: O(n*2^n)
*/

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> q;
        if (nums.empty() || nums.size() == 0)
            return q;
        
        int index = 0;
        vector<int> newSubset;
        q.push_back(newSubset);
        
        for (int num : nums) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                vector<int> subset = q[i];
                subset.push_back(num);
                q.push_back(subset);
            }
        }
        
        return q;
    }
};


