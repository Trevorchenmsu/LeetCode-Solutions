/*
solution: inorder traverse
time: O(n)
space: O(1)
*/

class Solution {
public:
    void recoverTree(TreeNode* root) {
        if (!root) {
            return;
        }
        dfs(root);
        swap(first->val, second->val);
    }

private:
    void dfs(TreeNode* root) {
        if (!root) {
            return;
        }
        // inorder traverse
        dfs(root->left);
        if (pre && pre->val >= root->val) {
            if (!first) {
                first = pre;
            }
            second = root;
        }
        pre = root;
        dfs(root->right);
    }
    
    TreeNode* first = NULL;
    TreeNode* second = NULL;
    TreeNode* pre = NULL;
};