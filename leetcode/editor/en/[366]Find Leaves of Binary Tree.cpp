//Given the root of a binary tree, collect a tree's nodes as if you were doing t
//his: 
//
// 
// Collect all the leaf nodes. 
// Remove all the leaf nodes. 
// Repeat until the tree is empty. 
// 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3,4,5]
//Output: [[4,5,3],[2],[1]]
//Explanation:
//[[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers si
//nce per each level it does not matter the order on which elements are returned.
// 
//
// Example 2: 
//
// 
//Input: root = [1]
//Output: [[1]]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 100]. 
// -100 <= Node.val <= 100 
// 
// Related Topics Tree Depth-First Search Binary Tree 
// 👍 1648 👎 29


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
 * time: O(nlogn)
 * space: O(h)
 * */
class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        if (root == NULL) {
            return {};
        }

        vector<vector<int>> res;
        vector<int> path;
        while (root) {
            path.clear();
            getLeaf(path, root);
            res.push_back(path);
            removeLeaf(root);
        }

        return res;
    }

    void getLeaf(vector<int>& path, TreeNode* root) {
        if (root == NULL) {
            return;
        }

        if (root->left == NULL && root->right == NULL) {
            path.push_back(root->val);
        }

        getLeaf(path, root->left);
        getLeaf(path, root->right);
    }

    void removeLeaf(TreeNode*& root) {
        if (root == NULL) {
            return;
        }

        if (root->left == NULL && root->right == NULL) {
            root = NULL;
            return;
        }

        removeLeaf(root->left);
        removeLeaf(root->right);
    }
};

/*
 * solution 2: 解法一优化版，返回节点为空即可，不需要置为空
 * time: O(n)
 * space: O(h)
 * */

class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        if (root == NULL) {
            return {};
        }

        vector<vector<int>> res;
        vector<int> path;
        while (root) {
            path.clear();
            root = removeLeaf(path, root);
            res.push_back(path);
        }

        return res;
    }

    TreeNode* removeLeaf(vector<int>& path, TreeNode* root) {
        if (root == NULL) {
            return root;
        }

        if (root->left == NULL && root->right == NULL) {
            path.push_back(root->val);
            return NULL;
        }

        root->left = removeLeaf(path, root->left);
        root->right = removeLeaf(path, root->right);
        return root;
    }
};

/*
 * solution 3: bottom up traversal
 * time: O(n)
 * space: O(h)
 * */
class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> res;
        search(root, res);
        return res;
    }

    int search(TreeNode* root, vector<vector<int>>& res) {
        /* 这里返回-1的原因是因为采用bottom up的方式来记录每一层的level值
           对于top down的情况，因为是从上到下逐层遍历，是无法区别不同层的叶子节点，
           而使用bottom up，就可以让每个叶子节点的位置为0，父节点向上递增即可。
           root为空时，表示是叶子节点的下一层，返回-1目的是为了计算level时可以累积
        */
        if (root == NULL) {
            return -1;
        }

        //这里选左右子树较大深度的操作也比较tricky。如果不这样操作，例1中的根节点就和2同个level
        int level = 1 + max(search(root->left, res), search(root->right, res));
        if (level >= res.size()) {
            res.resize(level + 1);
        }
        res[level].push_back(root->val);
        return level;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
