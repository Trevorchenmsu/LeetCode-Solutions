//Given the root of a binary tree, flatten the tree into a "linked list": 
//
// 
// The "linked list" should use the same TreeNode class where the right child po
//inter points to the next node in the list and the left child pointer is always n
//ull. 
// The "linked list" should be in the same order as a pre-order traversal of the
// binary tree. 
// 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,5,3,4,null,6]
//Output: [1,null,2,null,3,null,4,null,5,null,6]
// 
//
// Example 2: 
//
// 
//Input: root = []
//Output: []
// 
//
// Example 3: 
//
// 
//Input: root = [0]
//Output: [0]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 2000]. 
// -100 <= Node.val <= 100 
// 
//
// 
//Follow up: Can you flatten the tree in-place (with O(1) extra space)? Related 
//Topics Tree Depth-first Search 
// 👍 4623 👎 415


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
 * solution 1: preorder traversal + global variable
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == NULL) {
            return;
        }

        if (pre != NULL) {
            pre->left = NULL;
            pre->right = root;
        }

        pre = root;
        TreeNode* right = root->right;

        flatten(root->left);
        flatten(right);
    }
    TreeNode* pre = NULL;
};

/*
 * solution 2: divide and conquer + postorder traversal
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    void flatten(TreeNode* root) {
        divideConquer(root);
    }

private:
    TreeNode* divideConquer(TreeNode* root) {
        if (root == NULL) {
            return root;
        }

        TreeNode* left_last_node = divideConquer(root->left);
        TreeNode* right_last_node = divideConquer(root->right);

        if (left_last_node != NULL) {
            left_last_node->right = root->right;
            root->right = root->left;
            root->left = NULL;
        }

        if (right_last_node != NULL) {
            return right_last_node;
        }

        if (left_last_node != NULL) {
            return left_last_node;
        }

        return root;
    }
};


/*
 * solution 3: preorder traversal + iteration
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == NULL) {
            return;
        }

        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* cur = st.top(); st.pop();
            if (cur->right != NULL) {
                st.push(cur->right);
            }

            if (cur->left != NULL) {
                st.push(cur->left);
            }

            if (!st.empty()) {
                cur->right = st.top();
            }

            cur->left = NULL;
        }
    }

};
//leetcode submit region end(Prohibit modification and deletion)
