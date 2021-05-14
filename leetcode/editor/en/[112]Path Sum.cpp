//Given the root of a binary tree and an integer targetSum, return true if the t
//ree has a root-to-leaf path such that adding up all the values along the path eq
//uals targetSum. 
//
// A leaf is a node with no children. 
//
// 
// Example 1: 
//
// 
//Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
//Output: true
// 
//
// Example 2: 
//
// 
//Input: root = [1,2,3], targetSum = 5
//Output: false
// 
//
// Example 3: 
//
// 
//Input: root = [1,2], targetSum = 0
//Output: false
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 5000]. 
// -1000 <= Node.val <= 1000 
// -1000 <= targetSum <= 1000 
// 
// Related Topics Tree Depth-first Search 
// 👍 3133 👎 610


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
 * solution 1: iteration
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == NULL)
            return false;

        stack<TreeNode*> nodeStack;
        nodeStack.push(root);

        // preorder traversal, root, left, right
        while (!nodeStack.empty()) {
            TreeNode* node = nodeStack.top();
            nodeStack.pop();

            if (node->left == NULL && node->right == NULL) {
                if (node->val == targetSum)
                    return true;
            }

            if (node->right != NULL) {
                node->right->val += node->val;
                nodeStack.push(node->right);
            }

            if (node->left != NULL) {
                node->left->val += node->val;
                nodeStack.push(node->left);
            }
        }

        return false;
    }
};


/*
 * solution 2: recursion
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == NULL)
            return false;

        if (root->left == NULL && root->right == NULL) {
            if (root->val == targetSum)
                return true;
        }

        return hasPathSum(root->left, targetSum - root->val) ||
               hasPathSum(root->right, targetSum - root->val);
    }
};


/*
 * solution 3: BFS
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == NULL)
            return false;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            if (node->left == NULL && node->right == NULL) {
                if (node->val == targetSum)
                    return true;
            }

            if (node->left != NULL) {
                node->left->val += node->val;
                q.push(node->left);
            }

            if (node->right != NULL) {
                node->right->val += node->val;
                q.push(node->right);
            }
        }

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
