class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
    	vector<int> res;
    	if(!root){
    		return res;
    	}

    	list<int> list;
    	stack<TreeNode*> s;
    	s.push(root);

    	while(!s.empty()){
    		TreeNode* node = s.top(); s.pop();
    		list.push_front(node->val);
    		if(node->left){
    			s.push(node->left);
    		}
    		if(node->right){
    			s.push(node->right);
    		}
    	}

    	res = vector<int>(begin(list), end(list));
    	return res;

    }
};


