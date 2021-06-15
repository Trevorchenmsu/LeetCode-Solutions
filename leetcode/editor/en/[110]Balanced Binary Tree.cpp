//Given a binary tree, determine if it is height-balanced. 
//
// For this problem, a height-balanced binary tree is defined as: 
//
// 
// a binary tree in which the left and right subtrees of every node differ in he
//ight by no more than 1. 
// 
//
// 
// Example 1: 
//
// 
//Input: root = [3,9,20,null,null,15,7]
//Output: true
// 
//
// Example 2: 
//
// 
//Input: root = [1,2,2,3,3,null,null,4,4]
//Output: false
// 
//
// Example 3: 
//
// 
//Input: root = []
//Output: true
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 5000]. 
// -104 <= Node.val <= 104 
// 
// Related Topics Tree Depth-first Search Recursion 
// 👍 3659 👎 236


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
 * solution: divide and conquer
 * time: O(n)
 * space: O(n), the tree might be skewed
 *
 * */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        auto res = divideConquer(root);
        return res.first;
    }

    pair<bool, int> divideConquer(TreeNode* root) {
        if (root == NULL)
            return {true, 0};

        auto left = divideConquer(root->left);
        auto right = divideConquer(root->right);
        int height = max(left.second, right.second) + 1;

        if (!left.first || !right.first)
            return {false, height};

        if (abs(left.second - right.second) > 1)
            return {false, height};

        return {true, height};
    }
};
//leetcode submit region end(Prohibit modification and deletion)
