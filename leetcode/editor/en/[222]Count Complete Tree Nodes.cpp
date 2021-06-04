//Given the root of a complete binary tree, return the number of the nodes in th
//e tree. 
//
// According to Wikipedia, every level, except possibly the last, is completely 
//filled in a complete binary tree, and all nodes in the last level are as far lef
//t as possible. It can have between 1 and 2h nodes inclusive at the last level h.
// 
//
// Design an algorithm that runs in less than O(n) time complexity. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3,4,5,6]
//Output: 6
// 
//
// Example 2: 
//
// 
//Input: root = []
//Output: 0
// 
//
// Example 3: 
//
// 
//Input: root = [1]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 5 * 104]. 
// 0 <= Node.val <= 5 * 104 
// The tree is guaranteed to be complete. 
// 
// Related Topics Binary Search Tree 
// 👍 2916 👎 260


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
 * solution 1: brute force
 * time: O(n)
 * space: O(logn), stack space
 *
 * */
class Solution {
public:
    int countNodes(TreeNode* root) {
        int res = 0;
        dfs(root, res);
        return res;
    }

    void dfs(TreeNode* root, int &res) {
        if (root == NULL) return;
        res++;
        dfs(root->left, res);
        dfs(root->right, res);
    }
};


/*
 * solution 2: binary search, google interview
 * time: O(log(logn))
 * space: O(logn)
 *
 * */
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == NULL) return 0;

        TreeNode* node = root;
        int height = 0;

        // 计算树高，根据树高得到最下层的上下界
        while (node != NULL) {
            height++;
            node = node->left;
        }

        // 套用二分法模板
        int start = 1 << (height - 1), end = (1 << height) - 1;
        while (start + 1 < end) { // O(log(logn))
            int mid = start + (end - start) / 2;
            if (hasNode(root, mid))
                start = mid; // 因为要找到最大值，所以找到这个节点后肯定要往更大的方向走
            else
                end = mid;
        }

        if (hasNode(root, end))
            return end;
        else
            return start;
    }

    /*
    查找完全二叉树中是否存在某节点（只适用于完全二叉树，因为它可以保证除了最后一层，其他层都是满的）：
    (1) 获取从该节点到根节点的逆向路径。从该节点值开始，每一层循环中把该节点值存起来，然后除2更新，这样就
    相当于跳到了上一层，当该值变小到1时，表明抵达了根节点，继续除2就为0，可以跳出循环。
    (2) 得到路径vector后，从尾到头遍历这个path，其实也就相当于从树的根节点往下遍历，如果在遍历过程中发现一个
    节点是空的，就表明树中没有这个节点。为什么？因为路径中是提前假定这个路径是存在的，但是在树遍历过程中却找不到
    其中一个节点，所以这个形成的路径是invalid。
    */

private:
    bool hasNode(TreeNode *root, int val) {
        vector<int> path;

        while (val > 0) { // O(logn)
            path.push_back(val);
            val /= 2;
        }

        for (int i = path.size() - 1; i >= 0; i--) { // O(logn)
            if (root == NULL)
                return false;

            // 为什么要在这里加个？如果不加的话，即使到了i=0时是满足条件的，它会在下面的判定
            // 条件中继续产生i-1，这就成了负值越界了。
            if (i == 0) return true;

            //这里的trick就是利用到了完全二叉树的父节点和子节点两倍的关系
            if (path[i - 1] == 2 * path[i])
                root = root->left;
            else
                root = root->right;
        }

        return true;
    }
};


/*
 * solution 3: recursion
 * time: O(log(logn))
 * space: O(logn)
 *
 * */
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == NULL) return 0;
        int res = 1;

        int h1 = findLeftDepth(root->left);
        int h2 = findRightDepth(root->left);
        int h3 = findLeftDepth(root->right);
        int h4 = findRightDepth(root->right);

        if (h1 == h2) {
            res += (1 << h1) - 1;
            return res + countNodes(root->right);
        }
        else {
            res += (1 << h3) - 1;
            return res + countNodes(root->left);
        }
    }

private:
    int findLeftDepth(TreeNode* node) {
        int res = 0;

        while (node != NULL) {
            res++;
            node = node->left;
        }

        return res;
    }

    int findRightDepth(TreeNode* node) {
        int res = 0;

        while (node != NULL) {
            res++;
            node = node->right;
        }

        return res;
    }

};
//leetcode submit region end(Prohibit modification and deletion)
