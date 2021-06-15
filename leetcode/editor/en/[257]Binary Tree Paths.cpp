//Given the root of a binary tree, return all root-to-leaf paths in any order. 
//
// A leaf is a node with no children. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3,null,5]
//Output: ["1->2->5","1->3"]
// 
//
// Example 2: 
//
// 
//Input: root = [1]
//Output: ["1"]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 100]. 
// -100 <= Node.val <= 100 
// 
// Related Topics Tree Depth-first Search 
// 👍 2652 👎 139


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

 /* solution 1: preorder traversal
  * time: O(n^2), for a skewed tree, we need to store n nodes. at the end of leaf node, we need to traverse the path
  * space: O(n)
  *
  * */
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        vector<int> path;
        dfs(root, path, res);
        return res;
    }

    void dfs(TreeNode* root, vector<int> path, vector<string> &res) {
        if (root == NULL) return;

        if (root->left == NULL && root->right == NULL) {
            string s = "";
            for (auto &node : path)
                s += (to_string(node) + "->");
            s += to_string(root->val);
            res.push_back(s);
            return;
        }

        path.push_back(root->val);
        dfs(root->left, path, res);
        dfs(root->right, path, res);
    }
};

/* solution 2: preorder traversal
 * time: O(n), for a skewed tree, we need to store n nodes. at the end of leaf node,
 * we need to traverse the path
 * space: O(n)
 *
 * */
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        string path = "";
        dfs(root, path, res);
        return res;
    }

    void dfs(TreeNode* root, string path, vector<string> &res) {
        if (root == NULL) return;

        if (root->left == NULL && root->right == NULL) {
            res.push_back(path + to_string(root->val));
            return;
        }

        dfs(root->left, path + to_string(root->val) + "->", res);
        dfs(root->right, path + to_string(root->val) + "->", res);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
