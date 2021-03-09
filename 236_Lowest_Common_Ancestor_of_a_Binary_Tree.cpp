/*
solution 1: iteration
time: O(N)
space: O(N)
*/

class Solution {
public:
	// solution 1: iteration
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    	// corner case
    	if(!root){
    		return NULL;
    	}

    	// stack for iterating the tree
    	stack<TreeNode*> s;
    	// hash map for store the child(key)-parent(value)
    	unordered_map<TreeNode*, TreeNode*> child_parent;

    	child_parent[root] = NULL;
    	s.push(root);

    	// step 1: find out p and q
    	while(!child_parent.count(p) || !child_parent.count(q)){
    		// pop out the current node
    		TreeNode* cur = s.top(); s.pop();

    		// add current node's left child to hash map and stack (for future iteration)
    		if(cur->left){
    			child_parent[cur->left] = cur;
    			s.push(cur->left);
    		}

    		// add current node's right child to hash map and stack (for future iteration)
    		if(cur->right){
    			child_parent[cur->right] = cur;
    			s.push(cur->right);
    		}
    	}

    	// create set to store all the ancestor of p
    	set<TreeNode*> p_parent;

    	// step 2: find out all parents of node p
    	while(p){
    		p_parent.insert(p); // p is the parent of itself
    		p = child_parent[p];
    	}

    	// step 3: find out the first common ancestor of p and q
    	while(!p_parent.count(q)){
    		q = child_parent[q];
    	}

    	return q;
    }
};

/*
solution 2: recursion
time: O(N)
space: O(N)
*/
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q){
            return root;
        }
        
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        if(left && right)
            return root;

        return left == nullptr ? right : left;

    }
};