//We are given a binary tree (with root node root), a target node, and an intege
//r value k. 
//
// Return a list of the values of all nodes that have a distance k from the targ
//et node. The answer can be returned in any order. 
//
// 
//
// 
// 
//
// 
// Example 1: 
//
// 
//Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
//
//Output: [7,4,1]
//
//Explanation: 
//The nodes that are a distance 2 from the target node (with value 5)
//have values 7, 4, and 1.
//
//
//
//Note that the inputs "root" and "target" are actually TreeNodes.
//The descriptions of the inputs above are just serializations of these objects.
//
// 
//
// 
//
// Note: 
//
// 
// The given tree is non-empty. 
// Each node in the tree has unique values 0 <= node.val <= 500. 
// The target node is a node in the tree. 
// 0 <= k <= 1000. 
// 
// 
// Related Topics Tree Depth-first Search Breadth-first Search 
// 👍 3610 👎 73


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
 * solution 1: dfs + bfs
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        // dfs: get the parents map
        findParent(root, NULL);

        // bfs: find the nodes with distance k from target
        return bfs(target, child2parent, k);
    }

private:
    unordered_map<TreeNode*, TreeNode*> child2parent;
    void findParent(TreeNode* child, TreeNode* parent) {
        if (child == NULL) return;

        child2parent[child] = parent;
        findParent(child->left, child);
        findParent(child->right, child);
    }

    vector<int> bfs(TreeNode* target, unordered_map<TreeNode*, TreeNode*> &child2parent, int k) {
        unordered_set<TreeNode*> visited;
        visited.insert(target);
        queue<TreeNode*> q;
        q.push(target);

        int dist = 0;

        while (!q.empty()) {
            int size = q.size();
            vector<int> res;
            while (size--) {
                TreeNode* node = q.front(); q.pop();
                res.push_back(node->val);

                if (node->left != NULL && !visited.count(node->left)) {
                    visited.insert(node->left);
                    q.push(node->left);
                }

                if (node->right != NULL && !visited.count(node->right)) {
                    visited.insert(node->right);
                    q.push(node->right);
                }

                if (child2parent[node] != NULL && !visited.count(child2parent[node])) {
                    visited.insert(child2parent[node]);
                    q.push(child2parent[node]);
                }

            }

            if (dist == k) return res;

            dist++;
        }

        return {};
    }
};


/*
 * solution 2: dfs + bfs
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<TreeNode*, TreeNode*> parents;
        parents[root] = NULL;
        preorderDFS(parents, root);
        vector<int> res;
        BFS(root, parents, target, k, res);
        return res;
    }

    void preorderDFS(unordered_map<TreeNode*, TreeNode*> &parents, TreeNode* root) {
        if (root == NULL)
            return;

        if (root->left != NULL)
            parents[root->left] = root;
        if (root->right != NULL)
            parents[root->right] = root;

        preorderDFS(parents, root->left);
        preorderDFS(parents, root->right);
    }

    void BFS(TreeNode* root,  unordered_map<TreeNode*, TreeNode*> &parents, TreeNode* target, int k, vector<int> &res) {
        queue<TreeNode*> q;
        unordered_set<TreeNode*> visited;
        q.push(target);
        visited.insert(target);

        int step = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                TreeNode* cur = q.front(); q.pop();
                if (step == k)
                    res.push_back(cur->val);

                TreeNode* parent = parents[cur];
                if (parent != NULL && !visited.count(parent)) {
                    q.push(parent);
                    visited.insert(parent);
                }

                if (cur->left != NULL && !visited.count(cur->left)) {
                    q.push(cur->left);
                    visited.insert(cur->left);
                }

                if (cur->right != NULL && !visited.count(cur->right)) {
                    q.push(cur->right);
                    visited.insert(cur->right);
                }

            }
            step++;
            if (step > k) break;
        }
    }
};

/*
 * solution 3: dfs + bfs
 * time: O(n)
 * space: O(n)
 * */class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> res;

        unordered_map<TreeNode*, TreeNode*> parents;
        parents[root] = NULL;
        findParents(parents, root);

        unordered_set<TreeNode*> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited.insert(target);

        int step = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                TreeNode* cur = q.front(); q.pop();
                visited.insert(cur);

                if (step == k) {
                    res.push_back(cur->val);
                }
                if (cur->left != NULL && !visited.count(cur->left)) {
                    q.push(cur->left);
                }
                if (cur->right != NULL && !visited.count(cur->right)) {
                    q.push(cur->right);
                }
                if (parents[cur] != NULL && !visited.count(parents[cur])) {
                    q.push(parents[cur]);
                }
            }

            step++;
            if (step == k+1) {
                break;
            }
        }

        return res;
    }

    void findParents(unordered_map<TreeNode*, TreeNode*> &parents, TreeNode* root) {
        if (root == NULL) {
            return;
        }

        if (root->left != NULL) {
            parents[root->left] = root;
        }

        if (root->right != NULL) {
            parents[root->right] = root;
        }

        findParents(parents, root->left);
        findParents(parents, root->right);
    }
};

//leetcode submit region end(Prohibit modification and deletion)
