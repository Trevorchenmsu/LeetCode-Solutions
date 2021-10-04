//Given the root of a binary tree, find the largest subtree, which is also a Bin
//ary Search Tree (BST), where the largest means subtree has the largest number of
// nodes. 
//
// A Binary Search Tree (BST) is a tree in which all the nodes follow the below-
//mentioned properties: 
//
// 
// The left subtree values are less than the value of their parent (root) node's
// value. 
// The right subtree values are greater than the value of their parent (root) no
//de's value. 
// 
//
// Note: A subtree must include all of its descendants. 
//
// Follow up: Can you figure out ways to solve it with O(n) time complexity? 
//
// 
// Example 1: 
//
// 
//
// 
//Input: root = [10,5,15,1,8,null,7]
//Output: 3
//Explanation: The Largest BST Subtree in this case is the highlighted one. The 
//return value is the subtree's size, which is 3. 
//
// Example 2: 
//
// 
//Input: root = [4,2,7,2,3,5,null,2,null,null,null,null,null,1]
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 104]. 
// -104 <= Node.val <= 104 
// 
// Related Topics Tree 
// 👍 859 👎 80


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
 * solution 1: tree recursion
 * time: O(n)
 * space: O(logn)
 *
 * */
class Solution {
public:
    int largestBSTSubtree(TreeNode* root) {
        int res = 0;
        int tmp = isBST(root, res);

        return res;
    }

    int isBST(TreeNode* root, int &res) {
        if (root == NULL)
            return 0;

        int flag = 0;

        // condition 1 for BST:
        if (root->left != NULL) {
            TreeNode* node = root->left;
            while (node->right != NULL) {
                node = node->right;
            }
            if (node->val >= root->val)
                flag = 1;
        }

        if (root->right != NULL) {
            TreeNode* node = root->right;
            while (node->left != NULL) {
                node = node->left;
            }
            if (node->val <= root->val)
                flag = 1;
        }

        // condition 2: left subtree should be BST
        int leftNum = isBST(root->left, res);

        // condition 3: right subtree should be BST
        int rightNum = isBST(root->right, res);

        if (flag == 1 || leftNum == -1 || rightNum == -1)
            return -1;

        res = max(res, leftNum + rightNum + 1);

        return leftNum + rightNum + 1;
    }
};


/*
 * solution 2: tree recursion
 * time: O(n^2)
 * space: O(logn)
 *
 * */
class Solution {
public:
    int largestBSTSubtree(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }

        //每一次先判定当前树是否为BST，如果是，就数节点个数，同时更新最大节点数。
        if (isValidBST(root, INT_MIN, INT_MAX)) {
            int count = 0;
            countNodes(root, count);
            res = max(res, count);
        }

        // 根节点考虑完毕后，继续考虑左右子树，先序遍历。
        largestBSTSubtree(root->left);
        largestBSTSubtree(root->right);

        return res;
    }

private:
    int res = 0;
    void countNodes(TreeNode* root, int &count) {
        if (root == NULL) {
            return;
        }

        count++;
        countNodes(root->left, count);
        countNodes(root->right, count);
    }

    bool isValidBST(TreeNode* root, int min, int max) {
        if (root == NULL) {
            return true;
        }

        if (root->val <= min) {
            return false;
        }

        if (root->val >= max) {
            return false;
        }

        return isValidBST(root->left, min, root->val) && isValidBST(root->right, root->val, max);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
