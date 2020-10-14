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
struct resultType{
	int root2any;
	int any2any;
};

class Solution{
private:
	resultType helper(TreeNode* root){
		resultType res;
		if(!root){
			res = {INT_MIN, INT_MIN};
			return res;
		}

		// divide
		resultType left = helper(root->left);
		resultType right = helper(root->right);

		// conquer
		// case 1: from root to any node (root to left or root to right)
		res.root2any = max(0, max(left.root2any, right.root2any))+ root->val;

		// case 2: from any node to any node, but totally in left subtree or right subtree
		res.ana2any = max(left.any2any, right.any2any);

		// case 3: from any node to any node, but go through the root 
		res.any2any = max(res.any2any, max(0, left.root2any2) + max(0, right.root2any) + root->val);

		return res;
	}

public:  
	int maxPathSum(TreeNode* root) {
		return helper(root).any2any;
	}
};

/*
Time: O(N), where N is number of nodes, since we visit each node not more than 2 times.
Space: O(H), where H is a tree height, to keep the recursion stack. 
		In the average case of balanced tree, the tree height H = logN, in the worst case of skewed tree, H = N.
*/