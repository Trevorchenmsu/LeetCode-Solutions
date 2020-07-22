struct resultType{
	bool isBalanced;
	int maxHeight;
};

class Solution {

private:
    resultType helper(TreeNode* root){
    	resultType res;
    	if(!root){
    		res = {true, 0};
    		return res;
    	}

    	// divide
    	resultType left = helper(root->left);
    	resultType right = helper(root_>right);

    	// conquer
    	if(!left.isBalanced || !right.isBalanced){
    		res = {false, -1};
    		return res;
    	}

    	if(abs(left.maxHeight - right.maxHeight) > 1){
    		res = {false, -1};
    		return res;
    	}

    	res = {true, max(left.maxHeight, right.maxHeight) + 1};
    	return res;
    }



public:
    bool isBalanced(TreeNode* root) {
        return helper(root).isBalanced;
    }
};

