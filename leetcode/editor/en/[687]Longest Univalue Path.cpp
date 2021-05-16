//Given the root of a binary tree, return the length of the longest path, where 
//each node in the path has the same value. This path may or may not pass through 
//the root. 
//
// The length of the path between two nodes is represented by the number of edge
//s between them. 
//
// 
// Example 1: 
//
// 
//Input: root = [5,4,5,1,1,5]
//Output: 2
// 
//
// Example 2: 
//
// 
//Input: root = [1,4,5,4,4,5]
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 104]. 
// -1000 <= Node.val <= 1000 
// The depth of the tree will not exceed 1000. 
// 
// Related Topics Tree Recursion 
// 👍 2311 👎 562


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
 * space: O(n)
 * */
class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        if (root == NULL)
            return 0;

        int tmp = dfs(root);
        return max(0, res - 1);;
    }

private:
    int res = 0;
    int dfs(TreeNode* root) {
        if (root == NULL)
            return 0;
        int L = dfs(root->left);
        int R = dfs(root->right);

        int left = 0, right = 0;
        if (root->left != NULL && root->left->val== root->val)
            left = L;

        if (root->right != NULL && root->right->val == root->val)
            right = R;

        res = max(res, left + right + 1);

        return max(left, right) + 1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
