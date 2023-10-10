//Given the root of a binary tree, invert the tree, and return its root. 
//
// 
// Example 1: 
//
// 
//Input: root = [4,2,7,1,3,6,9]
//Output: [4,7,2,9,6,3,1]
// 
//
// Example 2: 
//
// 
//Input: root = [2,1,3]
//Output: [2,3,1]
// 
//
// Example 3: 
//
// 
//Input: root = []
//Output: []
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 100]. 
// -100 <= Node.val <= 100 
// 
// Related Topics Tree 
// 👍 5418 👎 78


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
 * solution 1: divide and conquer + recursion
 * time: O(n)
 * space: O(n)
 *
 * */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) {
            return root;
        }

        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        root->right = left;
        root->left = right;

        return root;
    }
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        invertTreeRecursive(root);
        return root;
    }

    void invertTreeRecursive(TreeNode* &root)
    {
        if (!root) return;

        invertTreeRecursive(root->left);
        invertTreeRecursive(root->right);
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        return flipLeftRight(root);
    }

    TreeNode* flipLeftRight(TreeNode* node) {
        if (node == nullptr)
            return node;

        TreeNode* tmp;
        tmp = node->left;
        node->left = node->right;
        node->right = tmp;

        node->left = flipLeftRight(node->left);
        node->right = flipLeftRight(node->right);

        return node;
    }
};

/*
 * solution 2: BFS level traversal
 * time: O(n)
 * space: O(n)
 *
 * */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr)
            return root;

        queue<TreeNode*> node_q;
        node_q.push(root);

        while (!node_q.empty()) {
            TreeNode* cur = node_q.front();
            node_q.pop();

            TreeNode* tmp = cur->left;
            cur->left = cur->right;
            cur->right = tmp;

            if (cur->left != nullptr)
                node_q.push(cur->left);

            if (cur->right != nullptr)
                node_q.push(cur->right);
        }

        return root;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
