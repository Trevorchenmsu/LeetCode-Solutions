//You are given the root of a binary tree with n nodes, where each node is uniqu
//ely assigned a value from 1 to n. You are also given a sequence of n values voya
//ge, which is the desired pre-order traversal of the binary tree. 
//
// Any node in the binary tree can be flipped by swapping its left and right sub
//trees. For example, flipping node 1 will have the following effect: 
//
// Flip the smallest number of nodes so that the pre-order traversal of the tree
// matches voyage. 
//
// Return a list of the values of all flipped nodes. You may return the answer i
//n any order. If it is impossible to flip the nodes in the tree to make the pre-o
//rder traversal match voyage, return the list [-1]. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2], voyage = [2,1]
//Output: [-1]
//Explanation: It is impossible to flip the nodes such that the pre-order traver
//sal matches voyage.
// 
//
// Example 2: 
//
// 
//Input: root = [1,2,3], voyage = [1,3,2]
//Output: [1]
//Explanation: Flipping node 1 swaps nodes 2 and 3, so the pre-order traversal m
//atches voyage. 
//
// Example 3: 
//
// 
//Input: root = [1,2,3], voyage = [1,2,3]
//Output: []
//Explanation: The tree's pre-order traversal already matches voyage, so no node
//s need to be flipped.
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is n. 
// n == voyage.length 
// 1 <= n <= 100 
// 1 <= Node.val, voyage[i] <= n 
// All the values in the tree are unique. 
// All the values in voyage are unique. 
// 
// Related Topics Tree Depth-first Search 
// 👍 527 👎 211


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
 * solution: dfs
 * time: O(n)
 * space: O(n)
 *
 *
 * */

/* 做题前的疑问：
 * 1.怎样确定最小翻转节点数？没有特别的记录，只要遇到不同的就交换，有点贪心的思想，结果就是最小的。
 * 2.怎样翻转节点？答案的dfs就比较tricky
 * 3.如何判定voyage和节点不同时是左节点还是右节点？先与跟节点判定，然后元素指针前进来判定左还是右
 * 4.被翻转的是子树，但是记录翻转节点数是这个子树的父节点？对，所以要进行翻转的时候需要把父节点加到结果中
 *
 * */
class Solution {
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> res;
        int idx = 0;
        return dfs(root, voyage, res, idx) ? res : vector<int> {-1};
    }

private:
    /*
     * dfs返回值：在遍历树的过程中，判定当前节点和当前数组元素是否相等。
     * */
    bool dfs(TreeNode* root, vector<int> &voyage, vector<int> &res, int &idx) {
        // 如果当前节点为空，在voyage里面不会有任何体现或差异，所以空节点不影响结果，可判定为true
        if (!root) return true;

        /* 首先要明确的是，我们要翻转的是子树，而不是父节点，如果父节点一开始就不等于当前数组元素
         * 那么就需要退回到上一层去作为上一层父节点的子节点，然后进行flip。
         * idx++这里是为了方便下面处理子节点，因为idx前进就相当于考虑下一个节点
        */
        if (root->val != voyage[idx++]) return false;

        /* 既然已经确定父节点相等了，接下来就要看看左右子节点是否满足当前数组元素的要求
         * 如果左子节点存在且不等于当前数组元素，即表示遇到了要交换的节点，先把根节点存到结果中。
         * 下面的两个dfs的位置就体现了交换左右子树的过程：可以看到在idx下的元素本该对应着左子节点，
         * 但是因为前面我们已经知道它不等于左子节点，所以在进一步递归时，我们把root改成了root->right，
         * 如果在下一层的递归中，这个dfs返回的是false，则证明交换不成功。如果成功的话会逐步深入递归。
         * */
        if (root->left && root->left->val != voyage[idx]) {
            res.push_back(root->val);
            return dfs(root->right, voyage, res, idx) && dfs(root->left, voyage, res, idx);
        }

        return dfs(root->left, voyage, res, idx) && dfs(root->right, voyage, res, idx);
    }

};
//leetcode submit region end(Prohibit modification and deletion)
