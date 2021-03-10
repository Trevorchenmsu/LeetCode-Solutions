/*
solution: inorder traverse
time: O(n), traverse all the nodes
space: O(n), since we keep inorder traversal nums with N elements.
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
    void recoverTree(TreeNode* root) {
        if (root == nullptr) return;
        
        dfs(root);
        swap(first->val, second->val);
    }
    
private:
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    TreeNode* pre = nullptr;
    
    void dfs(TreeNode* root) {
        if (root == nullptr) return;
        
        // inorder traversial
        dfs(root->left);
            
        if (pre != nullptr && pre->val >= root->val) {
            if (first == nullptr) first = pre;
            second = root;
        }
        pre = root;
            
        dfs(root->right);
    }
};