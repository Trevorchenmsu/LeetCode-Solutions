//Given two non-empty binary trees s and t, check whether tree t has exactly the
// same structure and node values with a subtree of s. A subtree of s is a tree co
//nsists of a node in s and all of this node's descendants. The tree s could also 
//be considered as a subtree of itself. 
//
// Example 1: 
//Given tree s: 
//
// 
//     3
//    / \
//   4   5
//  / \
// 1   2
// 
//Given tree t:
//
// 
//   4 
//  / \
// 1   2
// 
//Return true, because t has the same structure and node values with a subtree o
//f s.
//
// 
//
// Example 2: 
//Given tree s: 
//
// 
//     3
//    / \
//   4   5
//  / \
// 1   2
//    /
//   0
// 
//Given tree t:
//
// 
//   4
//  / \
// 1   2
// 
//Return false.
//
// 
// Related Topics Tree 
// 👍 3246 👎 162


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
  * solution 1:dfs
  * time:
  * space:
  *
  * */
//class Solution {
//public:
//    bool isSubtree(TreeNode* s, TreeNode* t) {
//        if (s == nullptr) return false;
//
//        if (s->val == t->val && isSameTree(s, t))
//            return true;
//        else
//            return isSubtree(s->left, t) || isSubtree(s->right, t);
//    }
//
//private:
//    bool isSameTree(TreeNode* s, TreeNode* t) {
//        if ((s == t) || (s != nullptr && t != nullptr &&
//                        s->val == t->val &&
//                        isSameTree(s->left, t->left) && isSameTree(s->right, t->right)))
//            return true;
//        else return false;
//    }
//
//};

/*
 * solution 2:dfs
 * time:
 * space:
 *
 * */

class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s == nullptr)
            return false;

        if (isSameTree(s, t))
            return true;

        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }

private:
    bool isSameTree(TreeNode* s, TreeNode* t) {
        if (s == nullptr && t == nullptr)
            return true;

        if (s == nullptr || t == nullptr)
            return false;

        return (s->val == t->val) &&
               (isSameTree(s->left, t->left)) &&
               (isSameTree(s->right, t->right));
    }

};
//leetcode submit region end(Prohibit modification and deletion)
