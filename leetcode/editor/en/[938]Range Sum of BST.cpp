//Given the root node of a binary search tree, return the sum of values of all n
//odes with a value in the range [low, high]. 
//
// 
// Example 1: 
//
// 
//Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
//Output: 32
// 
//
// Example 2: 
//
// 
//Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
//Output: 23
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 2 * 104]. 
// 1 <= Node.val <= 105 
// 1 <= low <= high <= 105 
// All Node.val are unique. 
// Related Topics Tree Depth-first Search Recursion 
// 👍 2179 👎 286


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
 * Solution: inorder tree traversal
 * time: O(n)
 * space: O(logn)
 *
 * */

class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        int sum = 0;
        dfs(root, low, high, sum);
        return sum;
    }

private:
    void dfs(TreeNode* root, int low, int high, int &sum) {
        if (root == nullptr)
            return;

        // inorder traversal
        dfs(root->left, low, high, sum);

        if (root->val >= low && root->val <= high)
            sum += root->val;

        dfs(root->right, low, high, sum);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
