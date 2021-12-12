//Given the root of a binary tree, return the inorder traversal of its nodes' va
//lues. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,null,2,3]
//Output: [1,3,2]
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
//Input: root = [1]
//Output: [1]
// 
//
// Example 4: 
//
// 
//Input: root = [1,2]
//Output: [2,1]
// 
//
// Example 5: 
//
// 
//Input: root = [1,null,2]
//Output: [1,2]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 100]. 
// -100 <= Node.val <= 100 
// 
//
// 
//Follow up: Recursive solution is trivial, could you do it iteratively? Related
// Topics Stack Tree Depth-First Search Binary Tree 
// 👍 5852 👎 246


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
 * solution 1: iteration, inorder traversal
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> res;

        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }

            auto cur = st.top(); st.pop();
            res.push_back(cur->val);
            if (cur->right) {
                root = cur->right;
            }
        }
        return res;
    }
};

/*
 * solution 2: recursion, inorder traversal
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        dfs(root, res);
        return res;
    }

    void dfs(TreeNode* root, vector<int> &res) {
        if (root == NULL) {
            return;
        }

        dfs(root->left, res);
        res.push_back(root->val);
        dfs(root->right, res);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
