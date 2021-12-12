//A path in a binary tree is a sequence of nodes where each pair of adjacent nod
//es in the sequence has an edge connecting them. A node can only appear in the se
//quence at most once. Note that the path does not need to pass through the root. 
//
//
// The path sum of a path is the sum of the node's values in the path. 
//
// Given the root of a binary tree, return the maximum path sum of any path. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3]
//Output: 6
//Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
//
// 
//
// Example 2: 
//
// 
//Input: root = [-10,9,20,null,null,15,7]
//Output: 42
//Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 
//= 42.
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 3 * 104]. 
// -1000 <= Node.val <= 1000 
// 
// Related Topics Tree Depth-first Search Recursion 
// 👍 6039 👎 409


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
 * space: O(h)
 *
 * */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        maxDownPath(root, res);
        return res;
    }

    int maxDownPath(TreeNode* root, int &res) {
        if (root == NULL) {
            return 0;
        }

        int leftPathSum = maxDownPath(root->left, res);
        int rightPathSum = maxDownPath(root->right, res);

        // 总路径和，包含左子树、右子树、根节点。如果左右子树路径和为负数，则不考虑，以0替代。
        leftPathSum = max(leftPathSum, 0);
        rightPathSum = max(rightPathSum, 0);

        res = max(res, leftPathSum + rightPathSum + root->val);

        // 返回值：在当前节点下，左右子树中路径和较大的那个子树（返回值包含当前节点值）
        return max(leftPathSum, rightPathSum) + root->val;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
