//Given a binary tree, find the lowest common ancestor (LCA) of two given nodes 
//in the tree. 
//
// According to the definition of LCA on Wikipedia: “The lowest common ancestor 
//is defined between two nodes p and q as the lowest node in T that has both p and
// q as descendants (where we allow a node to be a descendant of itself).” 
//
// 
// Example 1: 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
//Output: 3
//Explanation: The LCA of nodes 5 and 1 is 3.
// 
//
// Example 2: 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
//Output: 5
//Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant o
//f itself according to the LCA definition.
// 
//
// Example 3: 
//
// 
//Input: root = [1,2], p = 1, q = 2
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [2, 105]. 
// -109 <= Node.val <= 109 
// All Node.val are unique. 
// p != q 
// p and q will exist in the tree. 
// 
// Related Topics Tree 
// 👍 6048 👎 210


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
 * solution 1: preorder traversal + hash map + hash set
 * time: O(n), slower than solution 2 since we traverse all the nodes
 * space: O(n)
 * */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) {
            return NULL;
        }

        unordered_map<TreeNode*, TreeNode*> parents; // O(n)
        parents[root] = NULL;
        getParents(root, parents); // O(n)

        unordered_set<TreeNode*> p_parents; // O(h)
        while (p != NULL) {
            p_parents.insert(p);
            p = parents[p];
        }

        while (q != NULL) { // O(h)
            if (!p_parents.count(q)) {
                q = parents[q];
                continue;
            }
            break;
        }

        return q;
    }

private:
    void getParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*> &parents) {
        if (root == NULL) {
            return;
        }

        if (root->left != NULL) {
            parents[root->left] = root;
        }

        if (root->right != NULL) {
            parents[root->right] = root;
        }

        getParents(root->left, parents);
        getParents(root->right, parents);
    }
};

/*
 * solution 2: preorder traversal + hash map + hash set
 * time: O(n), faster since we stop when we find p and q
 * space: O(n)
 * */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // stack for tree traversal
        stack<TreeNode*> s;

        // HashMap for parent pointers
        unordered_map<TreeNode*, TreeNode*> parent;

        parent[root] = NULL;
        s.push(root);

        // iterate until we find p and q nodes
        while(!parent.count(p) || !parent.count(q)){
            TreeNode* node = s.top(); s.pop();

            // while traversing the tree, keep saving the parent pointers
            if(node->left){
                parent[node->left] = node;
                s.push(node->left);
            }
            if(node->right){
                parent[node->right] = node;
                s.push(node->right);
            }
        }

        // ancestors set for node p
        unordered_set<TreeNode*> ancestors;

        // process all ancestors for node p using parent pointers
        while(p){
            ancestors.insert(p);
            p = parent[p];
        }

        // the first ancestor of q which appears in
        // p's ancestor set is their LCA
        while(!ancestors.count(q)){
            q = parent[q];
        }

        return q;

    }
};


/*
 * solution 3: recursion
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q){
            return root;
        }

        // LCA有两种情况：一种是pq分布在树的两边，所以LCA只能是根节点；另一种是pq在同一边，所以LCA要么在左子树要么在右子树
        // 下面先从左右子树去查找，看看能不能找到pq
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // 如果左右子树找到的结果都不是空的，证明pq分布在两边。所以LCA只能是根节点
        if(left && right)
            return root;

        //如果在某一侧啥都没找到，表明pq都在同一侧。返回找到的那一侧
        return left == NULL ? right : left;
    }
};


//leetcode submit region end(Prohibit modification and deletion)
