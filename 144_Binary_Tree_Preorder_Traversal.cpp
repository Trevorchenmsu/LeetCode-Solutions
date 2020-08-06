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
    vector<int> preorderTraversal(TreeNode* root) {
    	vector<int> res;
    	//corner case
    	if(!root){
    		return res;
    	}

    	stack<TreeNode*> s;
    	s.push(root);

    	// iteration
    	while(!s.empty()){
    		TreeNode* cur = s.top(); s.pop();
    		res.push_back(cur->val);
    		if(cur->righ){
    			s.push(cur->right);
    		}
    		if(cur->left){
    			s.push(cur->left);
    		}
    	}
    	return res;
    }
};

