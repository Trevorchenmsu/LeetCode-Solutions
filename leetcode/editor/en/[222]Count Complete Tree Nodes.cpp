//Given the root of a complete binary tree, return the number of the nodes in th
//e tree. 
//
// According to Wikipedia, every level, except possibly the last, is completely 
//filled in a complete binary tree, and all nodes in the last level are as far lef
//t as possible. It can have between 1 and 2h nodes inclusive at the last level h.
// 
//
// Design an algorithm that runs in less than O(n) time complexity. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3,4,5,6]
//Output: 6
// 
//
// Example 2: 
//
// 
//Input: root = []
//Output: 0
// 
//
// Example 3: 
//
// 
//Input: root = [1]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 5 * 104]. 
// 0 <= Node.val <= 5 * 104 
// The tree is guaranteed to be complete. 
// 
// Related Topics Binary Search Tree 
// 👍 2916 👎 260


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
 * solution 1: brute force
 * time: O(n)
 * space: O(logn), stack space
 *
 * */
class Solution {
public:
    int countNodes(TreeNode* root) {
        int res = 0;
        dfs(root, res);
        return res;
    }

    void dfs(TreeNode* root, int &res) {
        if (root == NULL) return;
        res++;
        dfs(root->left, res);
        dfs(root->right, res);
    }
};


/*
 * solution 2: binary search, google interview
 * time: O(log(logn))
 * space: O(logn)
 *
 * */
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == NULL)
            return 0;

        TreeNode* node = root;
        int height = 0;

        while (node != NULL) {
            height++;
            node = node->left;
        }

        int start = 1 << (height - 1);
        int end = (1 << height) - 1;

        while (start + 1 < end) { // O(log(logn))
            int mid = start + (end - start) / 2;

            if (hasK(root, mid))
                start = mid;
            else
                end = mid;
        }

        if (hasK(root, end))
            return end;
        else
            return start;
    }

private:
    bool hasK(TreeNode* root, int k) {
        vector<int> path;

        while (k > 0) { // O(logn)
            path.push_back(k);
            k /= 2;
        }

        for (int i = path.size() - 1; i >= 0; i--) { // O(logn)
            if (root == NULL)
                return false;

            if (i == 0)
                return true;

            if (path[i - 1] == 2 * path[i])
                root = root->left;
            else
                root = root->right;
        }

        return true;
    }

};


/*
 * solution 3: recursion
 * time: O(log(logn))
 * space: O(logn)
 *
 * */
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == NULL) return 0;
        int res = 1;

        int h1 = findLeftDepth(root->left);
        int h2 = findRightDepth(root->left);
        int h3 = findLeftDepth(root->right);
        int h4 = findRightDepth(root->right);

        if (h1 == h2) {
            res += (1 << h1) - 1;
            return res + countNodes(root->right);
        }
        else {
            res += (1 << h3) - 1;
            return res + countNodes(root->left);
        }
    }

private:
    int findLeftDepth(TreeNode* node) {
        int res = 0;

        while (node != NULL) {
            res++;
            node = node->left;
        }

        return res;
    }

    int findRightDepth(TreeNode* node) {
        int res = 0;

        while (node != NULL) {
            res++;
            node = node->right;
        }

        return res;
    }

};
//leetcode submit region end(Prohibit modification and deletion)
