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
    int maxDepth(TreeNode* root) {
    	// corner case
    	if(!root){
    		return 0;
    	}
    	// divide and conquer
    	int res = max(maxDepth(root->left), maxDepth(root->right)) + 1;
    	return res;
    }
};

 	