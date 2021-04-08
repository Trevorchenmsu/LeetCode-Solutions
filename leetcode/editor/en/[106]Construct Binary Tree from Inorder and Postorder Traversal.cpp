//Given two integer arrays inorder and postorder where inorder is the inorder tr
//aversal of a binary tree and postorder is the postorder traversal of the same tr
//ee, construct and return the binary tree. 
//
// 
// Example 1: 
//
// 
//Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
//Output: [3,9,20,null,null,15,7]
// 
//
// Example 2: 
//
// 
//Input: inorder = [-1], postorder = [-1]
//Output: [-1]
// 
//
// 
// Constraints: 
//
// 
// 1 <= inorder.length <= 3000 
// postorder.length == inorder.length 
// -3000 <= inorder[i], postorder[i] <= 3000 
// inorder and postorder consist of unique values. 
// Each value of postorder also appears in inorder. 
// inorder is guaranteed to be the inorder traversal of the tree. 
// postorder is guaranteed to be the postorder traversal of the tree. 
// 
// Related Topics Array Tree Depth-first Search 
// 👍 2556 👎 48


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
 * solution 3: dfs + Hash table
 * time: O(n)
 * space: O(logn) for stack space, O(n) for construct a binary tree
 * */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); i++)
            node_idx[inorder[i]] = i;

        return dfs(postorder, 0, postorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

private:
    unordered_map<int, int> node_idx;
    TreeNode* dfs(vector<int> &postorder, int pLeft, int pRight, vector<int> &inorder, int iLeft, int iRight) {
        if (pLeft > pRight)
            return nullptr;

        int root_idx = node_idx[postorder[pRight]];

        TreeNode* cur = new TreeNode(inorder[root_idx]);

        // build left sub-tree and right-subtree
        cur->left = dfs(postorder, pLeft, pLeft + (root_idx - iLeft) - 1, inorder, iLeft, root_idx);
        cur->right = dfs(postorder, pLeft + (root_idx - iLeft), pRight - 1, inorder, root_idx + 1, iRight);

        return cur;
    }

};
//leetcode submit region end(Prohibit modification and deletion)
