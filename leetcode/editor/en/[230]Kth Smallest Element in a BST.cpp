//Given the root of a binary search tree, and an integer k, return the kth (1-in
//dexed) smallest element in the tree. 
//
// 
// Example 1: 
//
// 
//Input: root = [3,1,4,null,2], k = 1
//Output: 1
// 
//
// Example 2: 
//
// 
//Input: root = [5,3,6,2,4,null,null,1], k = 3
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is n. 
// 1 <= k <= n <= 104 
// 0 <= Node.val <= 104 
// 
//
// 
//Follow up: If the BST is modified often (i.e., we can do insert and delete ope
//rations) and you need to find the kth smallest frequently, how would you optimiz
//e? Related Topics Binary Search Tree 
// 👍 4077 👎 90


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
 * solution 1: inorder traversal + iteration
 * time: O(n)
 * space: O(h+k)
 * */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        if (root == NULL) {
            return -1;
        }

        stack<TreeNode*> st;
        int cnt = 0;

        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }

            TreeNode* cur = st.top(); st.pop();
            cnt++;
            if (cnt == k) {
                return cur->val;
            }

            if (cur->right != NULL) {
                root = cur->right;
            }
        }

        return -1;
    }
};

/*
 * solution 2: inorder traversal + recursion
 * time: O(n)
 * space: O(h+k)
 * */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int res = 0;
        inorder(root, res, k);
        return res;
    }

    void inorder(TreeNode* root, int &res, int &k) {
        if (root == NULL) {
            return;
        }

        inorder(root->left, res, k);

        k--;
        if (k == 0) {
            res = root->val;
            return;
        }

        inorder(root->right, res, k);
    }
};

/*
 * solution for follow-up: quick select
 * time : O(n)
 * space: O(n)
 * */

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        unordered_map<TreeNode*, int> numOfChildren;
        countNode(root, numOfChildren);
        return quickSelectOnTree(root, k, numOfChildren);
    }

private:
    int countNode(TreeNode* root, unordered_map<TreeNode*, int> &numOfChildren) {
        if (root == NULL) {
            return 0;
        }

        int left = countNode(root->left, numOfChildren);
        int right = countNode(root->right, numOfChildren);
        numOfChildren[root] = left + right + 1;

        return left + right + 1;
    }

    int quickSelectOnTree(TreeNode* root, int k,  unordered_map<TreeNode*, int> &numOfChildren) {
        if (root == NULL) {
            return -1;
        }

        int left = root->left == NULL ? 0 : numOfChildren[root->left];

        if (left >= k) {
            return quickSelectOnTree(root->left, k, numOfChildren);
        }

        if (left + 1 == k) {
            return root->val;
        }

        return quickSelectOnTree(root->right, k - left - 1, numOfChildren);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
