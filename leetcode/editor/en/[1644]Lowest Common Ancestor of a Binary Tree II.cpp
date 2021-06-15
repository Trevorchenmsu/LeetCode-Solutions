//Given the root of a binary tree, return the lowest common ancestor (LCA) of tw
//o given nodes, p and q. If either node p or q does not exist in the tree, return
// null. All values of the nodes in the tree are unique. 
//
// According to the definition of LCA on Wikipedia: "The lowest common ancestor 
//of two nodes p and q in a binary tree T is the lowest node that has both p and q
// as descendants (where we allow a node to be a descendant of itself)". A descend
//ant of a node x is a node y that is on the path from node x to some leaf node. 
//
// 
// Example 1: 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
//Output: 3
//Explanation: The LCA of nodes 5 and 1 is 3. 
//
// Example 2: 
//
// 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
//Output: 5
//Explanation: The LCA of nodes 5 and 4 is 5. A node can be a descendant of itse
//lf according to the definition of LCA. 
//
// Example 3: 
//
// 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 10
//Output: null
//Explanation: Node 10 does not exist in the tree, so return null.
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 104]. 
// -109 <= Node.val <= 109 
// All Node.val are unique. 
// p != q 
// 
//
// 
//Follow up: Can you find the LCA traversing the tree, without checking nodes ex
//istence? Related Topics Tree 
// 👍 164 👎 6


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 /*
  * solution: divide and conquer
  * time: O(n)
  * space: O(n)
  * */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) {
            return NULL;
        }

        bool pFound = search(root, p); // O(n)
        bool qFound = search(root, q);

        if (!pFound || !qFound) {
            return NULL;
        }

        return LCA(root, p, q);
    }

private:
    bool search(TreeNode* root, TreeNode* node) {
        if (root == NULL) {
            return false;
        }

        if (root == node) {
            return true;
        }

        return search(root->left, node) || search(root->right, node);
    }

    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q) {
            return root;
        }

        TreeNode* left = LCA(root->left, p, q);
        TreeNode* right = LCA(root->right, p, q);

        if (left != NULL && right != NULL) {
            return root;
        }

        return left == NULL ? right : left;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
