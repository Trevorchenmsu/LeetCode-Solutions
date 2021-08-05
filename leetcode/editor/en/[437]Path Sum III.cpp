//Given the root of a binary tree and an integer targetSum, return the number of
// paths where the sum of the values along the path equals targetSum. 
//
// The path does not need to start or end at the root or a leaf, but it must go 
//downwards (i.e., traveling only from parent nodes to child nodes). 
//
// 
// Example 1: 
//
// 
//Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
//Output: 3
//Explanation: The paths that sum to 8 are shown.
// 
//
// Example 2: 
//
// 
//Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 1000]. 
// -109 <= Node.val <= 109 
// -1000 <= targetSum <= 1000 
// 
// Related Topics Tree 
// 👍 5134 👎 323


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
 * solution 1 : dfs， postorder traversal
 * time: O(n^2)
 * space: O(n)
 *
 * */
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        int res = 0;
        traverseTree(root, targetSum, res);
        return res;
    }

private:
    void traverseTree(TreeNode* root, int sum, int &res) {
        if (root == NULL)
            return;

        // 目的是保证遍历每个节点，先用后序遍历走到树的最深处
        traverseTree(root->left, sum, res);
        traverseTree(root->right, sum, res);
        res += pathSumNum(root, sum);
    }

    int pathSumNum(TreeNode* root, int sum) {
        if (root == NULL)
            return 0;

        if (root->val == sum)
            return 1 + pathSumNum(root->left, 0) + pathSumNum(root->right, 0);
        else
            return pathSumNum(root->left, sum - root->val) + pathSumNum(root->right, sum - root->val);
    }
};

/*
 * solution 2: dfs + preorder traversal
 * time: O(n^2)
 * space: O(n)
 *
 * */
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        vector<TreeNode*> path;
        int res = 0, sum = 0;
        dfs(root, targetSum, sum, res, path);
        return res;
    }

    //先序遍历
    void dfs(TreeNode* root, int targetSum, int curSum, int &res, vector<TreeNode*> &path) {
        if (root == NULL)
            return;

        path.push_back(root);
        curSum += root->val;
        if (targetSum == curSum)
            res++;

        /* 如果上述if判定成立，表明根节点到当前节点的路径和是满足要求的。那么现在我们需要考虑从非根节点出发抵达当前
           节点的路径，看它们是否也满足这个target sum。因此下面的for循环逐渐删除上面的节点值。为什么不从下面删减？
           因为如果从下面删减，就变成了从根节点到删减后节点的路径，这是已考虑过的路径，如果该路径满足要求，不用在这个递归
           处理，而是在上一个递归处理。注意：这里i并没有抵达数组的末端，因为考虑到了target sum可能为0的情况，如果把最后一个删
           了，会加入错误的路径。
           为什么要考虑sum为0的情况？例如有条路径为[-7,3,4]，targetSum=0，那么这是条合理路径，当我们逐渐删除元素，最终剩下的sum=0，
           刚好等于targetSum，这时候又会错误的计入一条路径，所以我们不能让路径删除到底。
        */
        int sum = curSum;
        for (int i = 0; i < path.size() - 1; i++) {
            sum -= path[i]->val;
            if (sum == targetSum) res++;
        }

        //上部分处理完毕后就可以进行先序遍历，然后左右子树，最后结束后进行回溯。
        dfs(root->left, targetSum, curSum, res, path);
        dfs(root->right, targetSum, curSum, res, path);
        path.pop_back();
        curSum -= root->val;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
