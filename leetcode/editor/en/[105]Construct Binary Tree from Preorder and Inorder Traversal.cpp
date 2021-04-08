//Given two integer arrays preorder and inorder where preorder is the preorder t
//raversal of a binary tree and inorder is the inorder traversal of the same tree,
// construct and return the binary tree. 
//
// 
// Example 1: 
//
// 
//Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
//Output: [3,9,20,null,null,15,7]
// 
//
// Example 2: 
//
// 
//Input: preorder = [-1], inorder = [-1]
//Output: [-1]
// 
//
// 
// Constraints: 
//
// 
// 1 <= preorder.length <= 3000 
// inorder.length == preorder.length 
// -3000 <= preorder[i], inorder[i] <= 3000 
// preorder and inorder consist of unique values. 
// Each value of inorder also appears in preorder. 
// preorder is guaranteed to be the preorder traversal of the tree. 
// inorder is guaranteed to be the inorder traversal of the tree. 
// 
// Related Topics Array Tree Depth-first Search 
// 👍 4983 👎 127


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
 * solution 1: dfs + vector
 * time: O(nlogn)
 * space: O(logn) for stack space, O(n) for construct a binary tree
 * */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return dfs(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

private:
    TreeNode* dfs(vector<int> &preorder, int pLeft, int pRight, vector<int> &inorder, int iLeft, int iRight) {
        if (pLeft > pRight || iLeft > iRight)
            return nullptr;

        int i;
        for (i = iLeft;i < iRight; i++) {
            if (preorder[pLeft] == inorder[i])
                break;
        }

        TreeNode* cur = new TreeNode(inorder[i]);

        // build left sub-tree and right-subtree
        cur->left = dfs(preorder, pLeft + 1, pLeft + i - iLeft , inorder, iLeft, i);
        cur->right = dfs(preorder, pLeft + i - iLeft + 1, pRight, inorder, i + 1, iRight);

        return cur;
    }
};


/*
 * solution 2: dfs + iterator
 * time: O(nlogn)
 * space: O(logn) for stack space, O(n) for construct a binary tree
 * */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return dfs(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
    }

private:
    typedef vector<int>::iterator iter;

    TreeNode* dfs(iter pLeft, iter pRight, iter iLeft, iter iRight) {
        if (iLeft == iRight)
            return nullptr;

        iter rootIter = find(iLeft, iRight, *pLeft);
        TreeNode* cur = new TreeNode(*pLeft);

        cur->left = dfs(pLeft + 1, pLeft + (rootIter - iLeft), iLeft, rootIter);
        cur->right = dfs(pLeft + (rootIter - iLeft) + 1, pRight, rootIter + 1, iRight);

        return cur;
    }
};



/*
 * solution 3: dfs + Hash table
 * time: O(n)
 * space: O(logn) for stack space, O(n) for construct a binary tree
 * */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); i++)
            node_idx[inorder[i]] = i;

        return dfs(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

private:
    unordered_map<int, int> node_idx;
    TreeNode* dfs(vector<int> &preorder, int pLeft, int pRight, vector<int> &inorder, int iLeft, int iRight) {
        if (pLeft > pRight || iLeft > iRight)
            return nullptr;

        int root_idx = node_idx[preorder[pLeft]];

        TreeNode* cur = new TreeNode(inorder[root_idx]);

        // build left sub-tree and right-subtree
        cur->left = dfs(preorder, pLeft + 1, pLeft + root_idx - iLeft , inorder, iLeft, root_idx);
        cur->right = dfs(preorder, pLeft + root_idx - iLeft + 1, pRight, inorder, root_idx + 1, iRight);

        return cur;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
