//Given the root of a binary tree, determine if it is a valid binary search tree
// (BST). 
//
// A valid BST is defined as follows: 
//
// 
// The left subtree of a node contains only nodes with keys less than the node's
// key. 
// The right subtree of a node contains only nodes with keys greater than the no
//de's key. 
// Both the left and right subtrees must also be binary search trees. 
// 
//
// 
// Example 1: 
//
// 
//Input: root = [2,1,3]
//Output: true
// 
//
// Example 2: 
//
// 
//Input: root = [5,1,4,null,null,3,6]
//Output: false
//Explanation: The root node's value is 5 but its right child's value is 4.
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 104]. 
// -231 <= Node.val <= 231 - 1 
// 
// Related Topics Tree Depth-first Search Recursion 
// 👍 6068 👎 691


//leetcode submit region begin(Prohibit modification and deletion)
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

/*
 * solution 1: dfs/recursion
 * time: O(n)
 * space: O(h)
 *
 * */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (root == NULL)
            return true;
        return dfs(root, LONG_MIN, LONG_MAX);
    }

    bool dfs(TreeNode* root, long min, long max) {
        if (root == NULL)
            return true;

        if (min >= root->val)
            return false;

        if (max <= root->val)
            return false;

        return dfs(root->left, min, root->val) && dfs(root->right, root->val, max);
    }
};


/*
 * solution 2: dfs/recursion
 * time: O(n)
 * space: O(h)
 *
 * */

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (root == NULL) return true;

        int flag = 0;

        if (root->left != NULL) {
            TreeNode* node = root->left;
            while (node->right != NULL) {
                node = node->right;
            }
            if (node->val >= root->val)
                flag = 1;
        }

        if (root->right != NULL) {
            TreeNode* node = root->right;
            while (node->left != NULL) {
                node = node->left;
            }
            if (node->val <= root->val)
                flag = 1;
        }

        bool left = isValidBST(root->left);
        bool right = isValidBST(root->right);

        if (flag || !left || !right)
            return false;

        return left && right;
    }
};

/*
 * solution 3: dfs + inorder traversal
 * time: O(n)
 * space: O(h)
 *
 * */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (root == NULL)
            return true;

        if (!isValidBST(root->left))
            return false;

        if (!firstNode && root->val <= prev)
            return false;

        firstNode = false;
        prev = root->val;

        if (!isValidBST(root->right))
            return false;

        return true;
    }

private:
    bool firstNode = true;
    long prev = LONG_MIN;
};


/*
 * solution 4: iteration + inorder traversal
 * time: O(n)
 * space: O(h)
 *
 * */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long pre = LONG_MIN;
        stack<TreeNode*> nodeStack;

        // use root as condition, then we do not need to consider whether roo would be null
        while (root || !nodeStack.empty()) {
            // add the left nodes
            while (root) {
                nodeStack.push(root);
                root = root->left;
            }

            TreeNode* node = nodeStack.top();
            nodeStack.pop();

            if (node->val <= pre)
                return false;

            pre = node->val;
            root = node->right;
        }

        return true;
    }

};

//leetcode submit region end(Prohibit modification and deletion)
