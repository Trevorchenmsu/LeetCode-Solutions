//Given the root of a binary tree and an integer targetSum, return the number of
// paths where the sum of the values along the path equals targetSum. 
//
// The path does not need to start or end at the root or a leaf, but it must go 
//downwards (i.e., traveling only from parent nodes to child nodes). 
//
// 
// Example 1: 
//
// 
//Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
//Output: 3
//Explanation: The paths that sum to 8 are shown.
// 
//
// Example 2: 
//
// 
//Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 1000]. 
// -109 <= Node.val <= 109 
// -1000 <= targetSum <= 1000 
// 
// Related Topics Tree 
// 👍 5134 👎 323


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
 * time: O(n^2)
 * space: O(n)
 *
 * */
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        int res = 0;
        traverseTree(root, targetSum, res);
        return res;
    }

private:
    void traverseTree(TreeNode* root, int sum, int &res) {
        if (root == NULL)
            return;

        traverseTree(root->left, sum, res);
        traverseTree(root->right, sum, res);
        res += pathSumNum(root, sum);
    }

    int pathSumNum(TreeNode* root, int sum) {
        if (root == NULL)
            return 0;

        if (root->val == sum)
            return 1 + pathSumNum(root->left, 0) + pathSumNum(root->right, 0);
        else
            return pathSumNum(root->left, sum - root->val) + pathSumNum(root->right, sum - root->val);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
