//Given the root of a binary tree and an array of TreeNode objects nodes, return
// the lowest common ancestor (LCA) of all the nodes in nodes. All the nodes will 
//exist in the tree, and all values of the tree's nodes are unique. 
//
// Extending the definition of LCA on Wikipedia: "The lowest common ancestor of 
//n nodes p1, p2, ..., pn in a binary tree T is the lowest node that has every pi 
//as a descendant (where we allow a node to be a descendant of itself) for every v
//alid i". A descendant of a node x is a node y that is on the path from node x to
// some leaf node. 
//
// 
// Example 1: 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [4,7]
//Output: 2
//Explanation: The lowest common ancestor of nodes 4 and 7 is node 2.
// 
//
// Example 2: 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [1]
//Output: 1
//Explanation: The lowest common ancestor of a single node is the node itself.
//
// 
//
// Example 3: 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [7,6,2,4]
//Output: 5
//Explanation: The lowest common ancestor of the nodes 7, 6, 2, and 4 is node 5.
//
// 
//
// Example 4: 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [0,1,2,3,4,5,6,7,8]
//Output: 3
//Explanation: The lowest common ancestor of all the nodes is the root node.
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 104]. 
// -109 <= Node.val <= 109 
// All Node.val are unique. 
// All nodes[i] will exist in the tree. 
// All nodes[i] are distinct. 
// 
// Related Topics Tree Depth-first Search 
// 👍 127 👎 4


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
 * solution: divide and conquer
 * time: O(n*m), n is the number of nodes of the tree, m is the size of node array
 * space: O(n)
 * */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        if (root == NULL) {
            return NULL;
        }

        TreeNode* lca = nodes[0];

        for (int i = 1; i < nodes.size(); i++) {
            lca = LCA(root, lca, nodes[i]);
            if (root == lca) {
                break;
            }
        }

        return lca;
    }

private:
    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q) {
            return root;
        }

        TreeNode* left = LCA(root->left, p, q);
        TreeNode* right = LCA(root->right, p, q);

        if (left && right) {
            return root;
        }

        return left == NULL ? right : left;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
