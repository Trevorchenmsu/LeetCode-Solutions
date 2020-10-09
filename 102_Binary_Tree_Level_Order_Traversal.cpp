/*
solution 1: BFS
time: O(N), since each node is processed exactly once.
space: O(N), to keep the output structure which contains N node values.
*/
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        // edge case
        if (!root) {
            return res;
        }
        queue<TreeNode*> Q;
        Q.push(root);
        
        // BFS 
        while (!Q.empty()) {
            int size = Q.size();
            vector<int> level;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = Q.front();
                Q.pop();
                level.push_back(node->val);
                if (node->left) {
                    Q.push(node->left);
                }
                if (node->right) {
                    Q.push(node->right);
                }
            }
            res.push_back(level);
        }
        
        return res;
    }
};

/*
solution 2: DFS
time: O(N), since each node is processed exactly once.
space: O(N), to keep the output structure which contains N node values.
*/

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) {
            return res;
        }
        
        int maxLevel = 0;
        while (true) {
            vector<int> level;
            dfs(root, level, 0, maxLevel);
            if (level.empty()) {
                break;
            }
            res.push_back(level);
            ++maxLevel;
        }
        return res;
    }
private:
    void dfs(TreeNode* root, vector<int>& level, int currentLevel, int maxLevel) {
        if (!root || currentLevel > maxLevel) {
            return;
        }
        
        if (currentLevel == maxLevel) {
            level.push_back(root->val);
            return;
        }
        
        dfs(root->left, level, currentLevel + 1, maxLevel);
        dfs(root->right, level, currentLevel + 1, maxLevel);
    }
    
};