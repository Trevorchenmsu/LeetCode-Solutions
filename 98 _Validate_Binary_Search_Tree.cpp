/*
solution 1: inorder traverse
time: O(n), traverse all the nodes
space: O(n), since we keep inorder traversal nums with N elements.
*/
class Solution {
private:
    bool firstNode = true;
    int preVal = INT_MIN;
public:
    bool isValidBST(TreeNode* root) {
        if(!root){
            return true;
        }
        
        // traverse left tree
        if(!isValidBST(root->left)){
            return false;
        }
        
        // lastval represents previous node value. it should be smaller than current node value
        if(!firstNode && preVal >= root->val){
            return false;
        }
        firstNode = false;
        preVal = root->val;
        
        // traverse right tree
        if(!isValidBST(root->right)){
            return false;
        }
        return true;
    }
};

/*
solution 2: divide and conquer/dfs
time: O(n), traverse all the nodes
space: O(n) since we keep up to the entire tree.
*/
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return divideConquer(root, LONG_MIN, LONG_MAX);
    }
    
private:
    bool divideConquer(TreeNode* root, long min, long max) {
        if (!root) {
            return true;
        }
        
        // execuation for right tree
        if (min >= root->val) {
            return false;
        }
        
        // execuation for left tree
        if (max <= root->val) {
            return false;
        }
        
        bool left = divideConquer(root->left, min, root->val);
        bool right = divideConquer(root->right, root->val, max);
        return left && right;
    }
};

/*
solution 3: inorder iterative
time: O(n), traverse all the nodes
space: O(1)
*/
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long pre = LONG_MIN;
        stack<TreeNode*> s;
        
        while (root || !s.empty()) {
            //  traverse the left tree
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            if (root->val <= pre) return false;
            // traverse the right tree
            pre = root->val;
            root = root->right;
        }
        return true;
    }
};
