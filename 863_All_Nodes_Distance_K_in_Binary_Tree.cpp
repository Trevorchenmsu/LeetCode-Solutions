/*
solution: DFS + BFS
time: O(N), where N is the number of nodes in the given tree.
space: O(N)
*/
class Solution {
private:
    unordered_map<TreeNode*, TreeNode*> parent;
    void dfs(TreeNode* node, TreeNode* par) {
        if (!node) {
            return;
        }
        parent[node] = par;
        dfs(node->left, node);
        dfs(node->right, node);
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (!root) {
            return vector<int>(); 
        }
        
        // dfs: get the parent map
        dfs(root, NULL);
        
        
        set<TreeNode*> visited;
        queue<TreeNode*> q;
        visited.insert(target);
        q.push(target);
        int distance = 0;
        
        // bfs: get all the neighbors
        while (!q.empty()) {
            // traverse for each layer
            int size = q.size();
            vector<int> res;
            for (int i = 0; i < size; ++i) {
                TreeNode* cur = q.front();
                q.pop();
                res.push_back(cur->val);
                
                // get the left node
                if (cur->left && visited.find(cur->left) == visited.end()) {
                    visited.insert(cur->left);
                    q.push(cur->left);
                }
                
                // get the right node
                if (cur->right && visited.find(cur->right) == visited.end()) {
                    visited.insert(cur->right);
                    q.push(cur->right);
                }
                
                // get the parent node
                if (parent[cur] && visited.find(parent[cur]) == visited.end()) {
                    visited.insert(parent[cur]);
                    q.push(parent[cur]);
                }
            }
            if (distance == K) {
                return res;
            }
            ++distance;
        }
        return vector<int>();
    }
};