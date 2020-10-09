/*
solution 1: recursion
time: O(n), Because we traverse the entire input tree once, 
			the total run time is O(n), 
			where n is the total number of nodes in the tree.
space: O(n), The number of recursive calls is bound by the height of the tree. 
			 In the worst case, the tree is linear and the height is in O(n). 
*/

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) {
            return true;
        }
        
        return dfs(root->left, root->right);
    }
private:
    bool dfs(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if (!p || !q) {
            return false;
        }
        if (p->val != q->val) {
            return false;
        }
        
        return dfs(p->left, q->right) && dfs(p->right, q->left);
    }
};

/*
solution 2: iteration
time: O(n), Because we traverse the entire input tree once, 
			the total run time is O(n), 
			where n is the total number of nodes in the tree.
space: O(n), The number of recursive calls is bound by the height of the tree. 
			 In the worst case, the tree is linear and the height is in O(n). 
*/
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) {
            return true;
        }
        
        queue<TreeNode*> Q;
        // for left tree
        Q.push(root);
        // for right tree
        Q.push(root);
        
        while (!Q.empty()) {
            TreeNode* p = Q.front();
            Q.pop();
            TreeNode* q = Q.front();
            Q.pop();
            if (!p && !q) {
                continue;
            }
            if (!p || !q) {
                return false;
            }
            if (p->val != q->val) {
                return false;
            }
            Q.push(p->left);
            Q.push(q->right);
            Q.push(p->right);
            Q.push(q->left);
            
        }
        return true;
    }
};