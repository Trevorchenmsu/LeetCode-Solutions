//Given the root of a binary search tree, a target value, and an integer k, retu
//rn the k values in the BST that are closest to the target. You may return the an
//swer in any order. 
//
// You are guaranteed to have only one unique set of k values in the BST that ar
//e closest to the target. 
//
// 
// Example 1: 
//
// 
//Input: root = [4,2,5,1,3], target = 3.714286, k = 2
//Output: [4,3]
// 
//
// Example 2: 
//
// 
//Input: root = [1], target = 0.000000, k = 1
//Output: [1]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is n. 
// 1 <= k <= n <= 104. 
// 0 <= Node.val <= 109 
// -109 <= target <= 109 
// 
//
// 
// Follow up: Assume that the BST is balanced. Could you solve it in less than O
//(n) runtime (where n = total nodes)? 
// Related Topics Stack Tree 
// 👍 802 👎 24


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
 * solution 1:
 * time: O(nlogk)
 * space: O(k), O(n) for stack space
 * */
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        priority_queue<pair<double, int>> pq;
        vector<int> res;
        dfs(root, target, k, pq); // O(nlogk)

        while (!pq.empty()) { // O(logk)
            auto val = pq.top(); pq.pop();
            res.push_back(val.second);
        }

        return res;
    }

    void dfs(TreeNode* root, double target, int k,  priority_queue<pair<double, int>> &pq) {
        if (root == NULL) {
            return;
        }

        double diff = abs(target - root->val);

        pq.push({diff, root->val}); // O(logk)
        if (pq.size() > k) {
            pq.pop();
        }

        dfs(root->left, target, k, pq);
        dfs(root->right, target, k, pq);
    }
};


/*
 * solution 2: inorder traversal + binary search + two pointers
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> nums;
        vector<int> res;
        // inorder traversal, O(n)
        inorder(root, nums);

        // binary search, O(logn)
        auto iter = lower_bound(nums.begin(), nums.end(), target);
        if (iter == nums.end()) {
            return vector<int> (nums.end() - k, nums.end());
        }

        if (iter == nums.begin()) {
            return vector<int> (nums.begin(), nums.begin() + k);
        }

        // two pointers, O(k)
        int idx = iter - nums.begin();
        int left = idx - 1, right = idx, n = nums.size();
        while (res.size() < k) {
            if (right >= n || left >= 0 &&  abs(nums[left] - target) <= abs(nums[right] - target)) {
                res.push_back(nums[left--]);
            }
            else if (left < 0 || right < n && abs(nums[left] - target) > abs(nums[right] - target)) {
                res.push_back(nums[right++]);
            }
        }

        return res;
    }

    void inorder(TreeNode* root, vector<int> &nums) {
        if (root == NULL) {
            return;
        }

        inorder(root->left, nums);
        nums.push_back(root->val);
        inorder(root->right, nums);
    }
};


/*
 * solution 3: inorder traversal, recursion
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> res;
        inorder(root, target, k, res);
        return res;
    }

    void inorder(TreeNode* root, double target, int k, vector<int> &res) {
        if (root == NULL) {
            return;
        }

        inorder(root->left, target, k, res);

        if (res.size() < k) {
            res.push_back(root->val);
        }
        else if (abs(root->val - target) < abs(res[0] - target)) {
            res.erase(res.begin());
            res.push_back(root->val);
        }
        else return;

        inorder(root->right, target, k, res);
    }
};



/*
 * solution 4: inorder traversal, iteration
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> res;
        stack<TreeNode*> st;

        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }

            TreeNode* cur = st.top(); st.pop();
            if (res.size() < k) {
                res.push_back(cur->val);
            }
            else if (abs(cur->val - target) < abs(res[0] - target)) {
                res.erase(res.begin());
                res.push_back(cur->val);
            }
            else break;

            root = cur->right;
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
