//Given the root of a binary tree and an integer targetSum, return all root-to-l
//eaf paths where each path's sum equals targetSum. 
//
// A leaf is a node with no children. 
//
// 
// Example 1: 
//
// 
//Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
//Output: [[5,4,11,2],[5,8,4,5]]
// 
//
// Example 2: 
//
// 
//Input: root = [1,2,3], targetSum = 5
//Output: []
// 
//
// Example 3: 
//
// 
//Input: root = [1,2], targetSum = 0
//Output: []
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 5000]. 
// -1000 <= Node.val <= 1000 
// -1000 <= targetSum <= 1000 
// 
// Related Topics Tree Depth-first Search 
// 👍 2779 👎 85


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
 * solution 1: dfs/backtracking
 * time: O(V+E), V is the number of vertices, E is the number of edges
 * space: O(V)
 * */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> res;
        if (root == NULL)
            return res;

        vector<int> path;
        backtrack(root, targetSum, res, path);

        return res;
    }

    void backtrack(TreeNode* root, int sum, vector<vector<int>> &res, vector<int> &path) {
        if (root == NULL)
            return;

        path.push_back(root->val);

        if (root->left == NULL && root->right == NULL && root->val == sum) {
            res.push_back(path);
        }

        backtrack(root->left, sum - root->val, res, path);
        backtrack(root->right, sum - root->val, res, path);
        path.pop_back();
    }
};



/*
 * solution 2: iteration + stack
 * time: O(V+E), V is the number of vertices, E is the number of edges
 * space: O(V)
 * */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> res;
        if (root == NULL)
            return res;

        stack<TreeNode*> nodes;
        vector<int> path;
        TreeNode *cur = root, *pre;
        int sum = 0;

        // 中序遍历
        while (cur || !nodes.empty()) {
            // 先获取最左边的节点，同时计算路径和以及路径节点
            while (cur) {
                nodes.push(cur);
                sum += cur->val;
                path.push_back(cur->val);
                cur = cur->left;
            }

            // 检查是否为有效叶子节点。如果路径和满足要求，把该路径加到结果中。
            cur = nodes.top();
            if (cur->left == NULL && cur->right == NULL && sum == targetSum) {
                res.push_back(path);
            }

            // 情况1：右子树不为空，右子树还未被访问过，直接将右子树作为当前节点去遍历
            if (cur->right != NULL && cur->right != pre)
                cur = cur->right;
            else {
                // 右子树不存在或者右子树已经被访问过
                // 这里还可以实现抵达左节点后，把考虑过的左节点情况消除，类似回溯处理
                nodes.pop();
                path.pop_back();
                sum -= cur->val;
                pre = cur;
                cur = NULL; // 在左叶子节点的情况下，将cur置为空相当于剪枝
            }
        }

        return res;
    }
};



/*
 * solution 3: BFS
 * time: O(V+E), V is the number of vertices, E is the number of edges
 * space: O(V)
 * */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (root == NULL)
            return res;

        queue<TreeNode*> qNodes;
        queue<int> qSum;
        qNodes.push(root);
        qSum.push(0);

        while (!qNodes.empty()) {
            TreeNode* node = qNodes.front();
            qNodes.pop();

            int rec = qSum.front() + node->val;
            qSum.pop();

            if (node->left == NULL && node->right == NULL) {
                if (rec == sum) {
                    getPath(node);
                }
            }
            else {
                if (node->left != NULL) {
                    parent[node->left] = node;
                    qNodes.push(node->left);
                    qSum.push(rec);
                }
                if (node->right != NULL) {
                    parent[node->right] = node;
                    qNodes.push(node->right);
                    qSum.push(rec);
                }
            }
        }
        return res;
    }

private:
    vector<vector<int>> res;
    unordered_map<TreeNode*, TreeNode*> parent;

    void getPath(TreeNode* node) {
        vector<int> tmp;

        while (node != NULL) {
            tmp.push_back(node->val);
            node = parent[node];
        }

        reverse(tmp.begin(), tmp.end());
        res.emplace_back(tmp);
    }

};
//leetcode submit region end(Prohibit modification and deletion)
