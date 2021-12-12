//Given the root of a binary tree, each node in the tree has a distinct value. 
//
// After deleting all nodes with a value in to_delete, we are left with a forest
// (a disjoint union of trees). 
//
// Return the roots of the trees in the remaining forest. You may return the res
//ult in any order. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
//Output: [[1,2,null,4],[6],[7]]
// 
//
// Example 2: 
//
// 
//Input: root = [1,2,4,null,3], to_delete = [3]
//Output: [[1,2,4]]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the given tree is at most 1000. 
// Each node has a distinct value between 1 and 1000. 
// to_delete.length <= 1000 
// to_delete contains distinct values between 1 and 1000. 
// 
// Related Topics Tree Depth-First Search Binary Tree 
// 👍 2248 👎 65


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
 * solution: post order traversal
 * time: O(n)
 * space: O(h)
 *
 * */
class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        if (root == NULL) {
            return {};
        }

        unordered_set<int> deleteSet(to_delete.begin(), to_delete.end());
        vector<TreeNode*> res;
        postorder(root, res, deleteSet);

        if (root) {
            res.push_back(root);
        }

        return res;
    }

    void postorder(TreeNode*& root, vector<TreeNode*> &res, unordered_set<int> &delSet) {
        if (root == NULL) {
            return;
        }

        postorder(root->left, res, delSet);
        postorder(root->right, res, delSet);

        auto it = delSet.find(root->val);
        if (it != delSet.end()) {
            if (root->left) {
                res.push_back(root->left);
            }
            if (root->right) {
                res.push_back(root->right);
            }
            root = NULL;
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
