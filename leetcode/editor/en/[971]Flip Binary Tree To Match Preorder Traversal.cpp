//You are given the root of a binary tree with n nodes, where each node is uniqu
//ely assigned a value from 1 to n. You are also given a sequence of n values voya
//ge, which is the desired pre-order traversal of the binary tree. 
//
// Any node in the binary tree can be flipped by swapping its left and right sub
//trees. For example, flipping node 1 will have the following effect: 
//
// Flip the smallest number of nodes so that the pre-order traversal of the tree
// matches voyage. 
//
// Return a list of the values of all flipped nodes. You may return the answer i
//n any order. If it is impossible to flip the nodes in the tree to make the pre-o
//rder traversal match voyage, return the list [-1]. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2], voyage = [2,1]
//Output: [-1]
//Explanation: It is impossible to flip the nodes such that the pre-order traver
//sal matches voyage.
// 
//
// Example 2: 
//
// 
//Input: root = [1,2,3], voyage = [1,3,2]
//Output: [1]
//Explanation: Flipping node 1 swaps nodes 2 and 3, so the pre-order traversal m
//atches voyage. 
//
// Example 3: 
//
// 
//Input: root = [1,2,3], voyage = [1,2,3]
//Output: []
//Explanation: The tree's pre-order traversal already matches voyage, so no node
//s need to be flipped.
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is n. 
// n == voyage.length 
// 1 <= n <= 100 
// 1 <= Node.val, voyage[i] <= n 
// All the values in the tree are unique. 
// All the values in voyage are unique. 
// 
// Related Topics Tree Depth-first Search 
// 👍 527 👎 211


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
 * time: O(n)
 * space: O(n)
 *
 *
 * */
class Solution {
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> res;
        int idx = 0;
        return dfs(root, voyage, res, idx) ? res : vector<int> {-1};
    }

private:
    bool dfs(TreeNode* root, vector<int> &voyage, vector<int> &res, int &idx) {
        if (!root) return true;

        if (root->val != voyage[idx++]) return false;

        if (root->left && root->left->val != voyage[idx]) {
            res.push_back(root->val);
            return dfs(root->right, voyage, res, idx) && dfs(root->left, voyage, res, idx);
        }

        return dfs(root->left, voyage, res, idx) && dfs(root->right, voyage, res, idx);
    }

};
//leetcode submit region end(Prohibit modification and deletion)
