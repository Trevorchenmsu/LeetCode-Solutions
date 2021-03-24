//Given the root of a binary tree, return the length of the diameter of the tree
//. 
//
// The diameter of a binary tree is the length of the longest path between any t
//wo nodes in a tree. This path may or may not pass through the root. 
//
// The length of a path between two nodes is represented by the number of edges 
//between them. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3,4,5]
//Output: 3
//Explanation: 3is the length of the path [4,2,1,3] or [5,2,1,3].
// 
//
// Example 2: 
//
// 
//Input: root = [1,2]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 104]. 
// -100 <= Node.val <= 100 
// 
// Related Topics Tree 
// 👍 4432 👎 279



/*
 * Solution: dfs
 * time: O(n), traverse all the nodes
 * space: O(n) or O(logn), if the tree is balanced, it would be O(logn), which is the height of the tree.
 * if the tree is skewed, then the stack space needs to include all the nodes level.
 *
 * */

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

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int res = INT_MIN;
        dfs(root, res);
        return res;
    }

private:
    int dfs(TreeNode* root, int &res) {
        if (root == nullptr)
            return 0 ;

        int left = dfs(root->left, res);
        int right = dfs(root->right, res);

        res = max(res, left + right);

        return max(left, right) + 1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
