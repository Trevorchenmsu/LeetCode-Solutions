//Given a binary tree, determine if it is height-balanced.
//
// For this problem, a height-balanced binary tree is defined as:
//
//
// a binary tree in which the left and right subtrees of every node differ in he
//ight by no more than 1.
//
//
//
// Example 1:
//
//
//Input: root = [3,9,20,null,null,15,7]
//Output: true
//
//
// Example 2:
//
//
//Input: root = [1,2,2,3,3,null,null,4,4]
//Output: false
//
//
// Example 3:
//
//
//Input: root = []
//Output: true
//
//
//
// Constraints:
//
//
// The number of nodes in the tree is in the range [0, 5000].
// -104 <= Node.val <= 104
//
// Related Topics Tree Depth-first Search Recursion
// 👍 3659 👎 236


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
 * solution1: divide and conquer
 * time: O(n)
 * space: O(n), the tree might be skewed
 *
 * */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        pair<bool, int> ret = divideConquer(root);
        return ret.first;
    }

    pair<bool, int> divideConquer(TreeNode* root) {
        // because null node is also balanced, its height is 0
        if (root == nullptr)
            return {true, 0};

        auto left = divideConquer(root->left);
        auto right = divideConquer(root->right);
        // we need to add 1 since the node is higher than its left and right sub-nodes
        int node_height = max(left.second, right.second) + 1;

        // left subtree or right subtree is not balanced
        if (!left.first || !right.first)
            return {false, node_height};

        // left and right subtrees are balanced, but not balanced in the current parent node
        if (abs(left.second - right.second) > 1)
            return {false, node_height};

        return {true, node_height};
    }
};

/*
 * solution2: divide and conquer
 * time: O(n)
 * space: O(n), the tree might be skewed
 *
 * */

struct resultType{
    bool isBalanced;
    int maxHeight;
};

class Solution {

private:
    resultType helper(TreeNode* root){
        resultType res;
        if(!root){
            res = {true, 0};
            return res;
        }

        // divide
        resultType left = helper(root->left);
        resultType right = helper(root_>right);

        // conquer
        if(!left.isBalanced || !right.isBalanced){
            res = {false, -1};
            return res;
        }

        if(abs(left.maxHeight - right.maxHeight) > 1){
            res = {false, -1};
            return res;
        }

        res = {true, max(left.maxHeight, right.maxHeight) + 1};
        return res;
    }



public:
    bool isBalanced(TreeNode* root) {
        return helper(root).isBalanced;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


