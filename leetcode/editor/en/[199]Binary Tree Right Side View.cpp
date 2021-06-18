//Given the root of a binary tree, imagine yourself standing on the right side o
//f it, return the values of the nodes you can see ordered from top to bottom. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3,null,5,null,4]
//Output: [1,3,4]
// 
//
// Example 2: 
//
// 
//Input: root = [1,null,3]
//Output: [1,3]
// 
//
// Example 3: 
//
// 
//Input: root = []
//Output: []
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 100]. 
// -100 <= Node.val <= 100 
// 
// Related Topics Tree Depth-first Search Breadth-first Search Recursion Queue 
// 👍 4173 👎 227


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/*
 * solution 1: BFS
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (root == NULL) {
            return res;
        }

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int len = q.size();
            int cnt = 0;
            while (len--) {
                TreeNode* cur = q.front(); q.pop();
                if (cnt == 0) {
                    res.push_back(cur->val);
                }
                cnt++;

                if (cur->right != NULL) {
                    q.push(cur->right);
                }

                if (cur->left != NULL) {
                    q.push(cur->left);
                }
            }
        }

        return res;
    }
};

/*
 * solution 2: DFS
 * time: O(n)
 * space: O(n)
 * */
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
//leetcode submit region end(Prohibit modification and deletion)
