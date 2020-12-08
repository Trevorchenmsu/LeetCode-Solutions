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

// solution 1: recursive
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
    	vector<int> res;
    	if(!root){
    		return res;
    	}
    	traverse(root, res);
    	return res;
    }

    void traverse(TreeNode* root, vector<int>& res){
    	if(!root){
    		return;
    	}

    	traverse(root->left, res);
    	res.push_back(root->val);
    	traverse(root->right, res);
    }
};



// solution 2: iteration 
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
    	vector<int> res;
    	// corner case
    	if(!root){
    		return res;
    	}

    	stack<TreeNode*> s;
		while(root){
			s.push(root);
			root = root->left;
		}

    	while(!s.empty()){
    		TreeNode* cur = s.top(); s.pop();
    		res.push_back(cur->val);

    		if(cur->right){
    			cur = cur->right;
    			while(cur){
    				s.push(cur);
    				cur = cur->left;
    			}
    		}
    		
    	}
    	return res;
};

