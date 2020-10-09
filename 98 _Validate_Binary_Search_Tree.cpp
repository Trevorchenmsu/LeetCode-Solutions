/*
solution 1: inorder traverse
time: O(n), traverse all the nodes
space: O(1)
*/
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) {
            return true;
        }
        // left tree node
        if(!isValidBST(root->left)) {
            return false;
        }
        
        // root tree node
        if (!firstNode && lastVal >= root->val) {
            return false;
        }
        firstNode = false;
        lastVal = root->val;
        
        // right tree node
        if (!isValidBST(root->right)) {
            return false;
        }
        return true;
    }
private:
    bool firstNode = true;
    int lastVal = INT_MIN;
};

/*
solution 2: divide and conquer
time: O(n), traverse all the nodes
space: O(1)
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
        
        if (min >= root->val) {
            return false;
        }
        if (max <= root->val) {
            return false;
        }
        
        bool left = divideConquer(root->left, min, root->val);
        bool right = divideConquer(root->right, root->val, max);
        return left && right;
    }
};