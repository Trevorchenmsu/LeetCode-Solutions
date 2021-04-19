//We run a preorder depth-first search (DFS) on the root of a binary tree. 
//
// At each node in this traversal, we output D dashes (where D is the depth of t
//his node), then we output the value of this node. If the depth of a node is D, t
//he depth of its immediate child is D + 1. The depth of the root node is 0. 
//
// If a node has only one child, that child is guaranteed to be the left child. 
//
//
// Given the output S of this traversal, recover the tree and return its root. 
//
// 
// Example 1: 
//
// 
//Input: S = "1-2--3--4-5--6--7"
//Output: [1,2,5,3,4,6,7]
// 
//
// Example 2: 
//
// 
//Input: S = "1-2--3---4-5--6---7"
//Output: [1,2,5,3,null,6,null,4,null,7]
// 
//
// Example 3: 
//
// 
//Input: S = "1-401--349---90--88"
//Output: [1,401,null,349,88,90]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the original tree is in the range [1, 1000]. 
// 1 <= Node.val <= 109 
// 
// Related Topics Tree Depth-first Search 
// 👍 640 👎 22


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
 * */
class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        for (int i = 0; i < S.size(); i++) {
            int j = i;
            while (j < S.size() && S[j] == '-')
                j++;

            int depth = j - i;

            i = j;
            while (j < S.size() && isdigit(S[j]))
                j++;

            int val = stoi(S.substr(i, j - i));
            i = j - 1;

            nodes.push_back({val, depth});
        }
        int num = 0;
        return dfs(0, num);
    }

private:
    vector<pair<int, int>> nodes;
    TreeNode* dfs(int idx, int &num){
        TreeNode* root = new TreeNode(nodes[idx].first);

        int leftNum = 0, rightNum = 0;
        // build left subtree
        if (idx + 1 < nodes.size() &&
            nodes[idx].second + 1 == nodes[idx + 1].second)
            root->left = dfs(idx + 1, leftNum);

        // build right subtree
        if (idx + leftNum + 1 < nodes.size() &&
            nodes[idx].second + 1 == nodes[idx + leftNum + 1].second)
            root->right = dfs(idx + leftNum + 1, rightNum);

        num = leftNum + rightNum + 1;

        return root;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
