/*
Solution 1: BFS + two queues
time:O(N) since one has to visit each node.
Space: O(D) to keep the queues, where D is a tree diameter. Let's use the last level to estimate 
	   the queue size. This level could contain up to N/2 tree nodes in the case of complete binary tree
*/
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root) {
            return res;
        }
        
        queue<TreeNode*> currentLevel;
        queue<TreeNode*> nextLevel;
        
        nextLevel.push(root);
        TreeNode* node = NULL;
        while (!nextLevel.empty()) {
            currentLevel = nextLevel;
            queue<TreeNode*> empty;
            swap(empty, nextLevel);
            
            while (!currentLevel.empty()) {
                node = currentLevel.front();
                currentLevel.pop();
                if (node->left) {
                    nextLevel.push(node->left);
                }
                if (node->right) {
                    nextLevel.push(node->right);
                }
            }
            
            res.push_back(node->val);
        }
        return res;
    }
};

/*
Solution 2: BFS + one queue + sentinel(null)
time:O(N) since one has to visit each node.
Space: O(D) to keep the queues, where D is a tree diameter. Let's use the last level to estimate 
	   the queue size. This level could contain up to N/2 tree nodes in the case of complete binary tree
*/

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root) {
            return res;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        q.push(NULL);
        
        TreeNode* pre, *cur = root;
        
        while (!q.empty()) {
            cur = q.front();
            q.pop();
            
            while (cur) {
                if (cur->left) {
                    q.push(cur->left);
                }
                if (cur->right) {
                    q.push(cur->right);
                }
                
                pre = cur;
                cur = q.front();
                q.pop();
            }
            
            res.push_back(pre->val);
                
            // add null as the sentinel
            if (!q.empty()) {
                q.push(NULL);
            }
        }
        return res;
    }
};

/*
Solution 3: BFS + one queue + level size
time:O(N) since one has to visit each node.
Space: O(D) to keep the queues, where D is a tree diameter. Let's use the last level to estimate 
	   the queue size. This level could contain up to N/2 tree nodes in the case of complete binary tree
*/
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        // edge case
        if (!root) {
            return res;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                
                if (i == size - 1) {
                    res.push_back(node->val);
                }
                
                if (node->left) {
                    q.push(node->left);
                }
                
                if (node->right) {
                    q.push(node->right);
                }
            }
        }
        return res;
    }
};

/*
Solution 4: BFS + one queue + level size
time:O(N) since one has to visit each node.
Space: O(H) to keep the recursion stack, where H is a tree height. The worst-case situation is a skewed tree, when H = N.
*/
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root) {
            return res;
        }
        dfs(root, 0, res);
        return res;
    }
    
private:
    void dfs(TreeNode* root, int level, vector<int> &res) {
        if (level == res.size()) {
            res.push_back(root->val);
        }
        
        if (root->right) {
            dfs(root->right, level + 1, res);
        }
        if (root->left) {
            dfs(root->left, level + 1, res);
        }
    }
};