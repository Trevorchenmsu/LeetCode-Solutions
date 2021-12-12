//Given the root of a binary tree, return the zigzag level order traversal of it
//s nodes' values. (i.e., from left to right, then right to left for the next leve
//l and alternate between). 
//
// 
// Example 1: 
//
// 
//Input: root = [3,9,20,null,null,15,7]
//Output: [[3],[20,9],[15,7]]
// 
//
// Example 2: 
//
// 
//Input: root = [1]
//Output: [[1]]
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
// The number of nodes in the tree is in the range [0, 2000]. 
// -100 <= Node.val <= 100 
// 
// Related Topics Tree Breadth-First Search Binary Tree 
// 👍 4357 👎 143


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
 * solution: bfs
 * time: O(N)，n为节点总数
 * space: O(n), n为节点总数
 * */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (root == NULL) {
            return {};
        }

        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        vector<vector<int>> res;
        vector<int> layer;

        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                auto cur = q.front(); q.pop();
                layer.push_back(cur->val);
                if (cur->left) {
                    q.push(cur->left);
                }
                if (cur->right) {
                    q.push(cur->right);
                }
            }

            if (level % 2 != 0) {
                reverse(layer.begin(), layer.end());
            }

            res.push_back(layer);
            layer.clear();
            level++;
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
