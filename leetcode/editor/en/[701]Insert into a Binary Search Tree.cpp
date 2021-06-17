//You are given the root node of a binary search tree (BST) and a value to inser
//t into the tree. Return the root node of the BST after the insertion. It is guar
//anteed that the new value does not exist in the original BST. 
//
// Notice that there may exist multiple valid ways for the insertion, as long as
// the tree remains a BST after insertion. You can return any of them. 
//
// 
// Example 1: 
//
// 
//Input: root = [4,2,7,1,3], val = 5
//Output: [4,2,7,1,3,5]
//Explanation: Another accepted tree is:
//
// 
//
// Example 2: 
//
// 
//Input: root = [40,20,60,10,30,50,70], val = 25
//Output: [40,20,60,10,30,50,70,null,null,25]
// 
//
// Example 3: 
//
// 
//Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
//Output: [4,2,7,1,3,5]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree will be in the range [0, 104]. 
// -108 <= Node.val <= 108 
// All the values Node.val are unique. 
// -108 <= val <= 108 
// It's guaranteed that val does not exist in the original BST. 
// 
// Related Topics Tree 
// 👍 1647 👎 100


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
 * solution: dfs
 * time: O(h)
 * space: O(h)
 * */
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode* node = new TreeNode(val);
        if (root == NULL) {
            return node;
        }

        dfs(root, node);
        return root;
    }

    void dfs(TreeNode * root, TreeNode * node) {
        if (root == NULL) {
            return;
        }

        if (root->val > node->val) {
            if (root->left == NULL) {
                root->left = node;
            }
            else {
                dfs(root->left, node);
            }
        }

        if (root->val < node->val) {
            if (root->right == NULL) {
                root->right = node;
            }
            else {
                dfs(root->right, node);
            }
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
