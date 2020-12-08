/*
solution: BFS
time: O(nlogn), map will sort its key automatically.
space: O(n), worst case in the map is each key correponds to each node.
*/
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        map<int, vector<int>> results;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        
        // bfs
        while (!q.empty()) {
            pair<TreeNode*, int> nodePair = q.front(); q.pop();
            TreeNode* node = nodePair.first;
            int colIndex = nodePair.second;
            if (node) {
                results[colIndex].push_back(node->val);
                q.push({node->left, colIndex - 1});
                q.push({node->right, colIndex + 1});
            }
        }
        
        vector<vector<int>> res;
        for (auto result : results) {
            res.push_back(result.second);
        }
        
        return res;
    }
};