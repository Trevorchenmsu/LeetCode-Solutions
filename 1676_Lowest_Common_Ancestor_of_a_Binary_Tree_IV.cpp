/*
solution: recursion + divide and conquer
time: O(mn), n is the number of nodes in the tree, m is the lenght of array
space: O(n)
*/
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
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        if (nodes.size() == 1) return nodes[0];
        
        TreeNode* lca = nodes[0];
        for (int i = 1; i < nodes.size(); i++) {
            lca = LCA(root, lca, nodes[i]);
            if (root == lca) break;
        }
        
        return lca;
        
    }
    
    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) 
            return root;
        
        TreeNode* left = LCA(root->left, p, q);
        TreeNode* right = LCA(root->right, p, q);
        
        if (left && right) return root;
        
        return left == nullptr ? right : left;
    }
};