/*
solution: recursion + divide and conquer + bfs
time: O(n)
space:O(n)
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
    int findDistance(TreeNode* root, int p, int q) {
        if (root == nullptr) return 0;
        if (p == q) return 0;
        
        TreeNode* lca = findLCA(root, p, q); // O(n)
        if (lca == nullptr) return 0;
        
        int pDis = distance(lca, p); // (n)
        int qDis = distance(lca, q);
        
        return pDis + qDis;
    }
    
private:
    TreeNode* findLCA(TreeNode* root, int p, int q) {
        if(!root || root->val == p || root->val == q){
            return root;
        }
        
        TreeNode* left = findLCA(root->left, p, q);
        TreeNode* right = findLCA(root->right, p, q);
        
        if(left && right)
            return root;

        return left == nullptr ? right : left;
    }
    
    // bfs to compute shortest distance
    int distance(TreeNode* node, int val) {
        queue<TreeNode*> q;
        q.push(node);
        int res = 0;
        
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                TreeNode* cur = q.front();
                q.pop();
                if (cur->val == val) return res;
                if (cur->left != nullptr) q.push(cur->left);
                if (cur->right != nullptr) q.push(cur->right);
            }
            res++;
        }
        
        return res;
    }
};