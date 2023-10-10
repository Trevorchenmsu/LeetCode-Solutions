//Given the root of a Binary Search Tree and a target number k, return true if t
//here exist two elements in the BST such that their sum is equal to the given tar
//get. 
//
// 
// Example 1: 
//
// 
//Input: root = [5,3,6,2,4,null,7], k = 9
//Output: true
// 
//
// Example 2: 
//
// 
//Input: root = [5,3,6,2,4,null,7], k = 28
//Output: false
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 104]. 
// -104 <= Node.val <= 104 
// root is guaranteed to be a valid binary search tree. 
// -105 <= k <= 105 
// 
// Related Topics Hash Table Two Pointers Tree Depth-First Search Breadth-First 
//Search Binary Search Tree Binary Tree 
// 👍 3068 👎 189


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
 * solution 1: inorder traversal + two pointers
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> nums;
        inorder(root, nums);

        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == k) return true;
            else if (sum < k) left++;
            else right--;
        }

        return false;
    }

    void inorder(TreeNode* root, vector<int> &nums) {
        if (root == NULL) return;
        inorder(root->left, nums);
        nums.push_back(root->val);
        inorder(root->right, nums);
    }
};

/*
 * solution 1: hashset + dfs
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> node_set;
        return dfs(root, node_set, k);
    }

    bool dfs(TreeNode* root, unordered_set<int> &node_set, int k) {
        if (root == NULL) return false;
        auto it = node_set.find(k - root->val);
        if (it != node_set.end()) return true;
        node_set.insert(root->val);
        return dfs(root->left, node_set, k) || dfs(root->right, node_set, k);
    }
};


/*
 * solution 3: BST iterator + two pointers
 * time: O(n)
 * space: O(h)
 * */
class BSTIterator {
public:
    stack<TreeNode*> st;
    bool forward;
    BSTIterator(TreeNode* root, bool forward) {
        this->forward = forward;
        if (forward) pushAllLeft(root);
        else pushAllRight(root);
    }

    int next() {
        TreeNode* node = st.top(); st.pop();
        if (forward) pushAllLeft(node->right);
        else  pushAllRight(node->left);
        return node->val;
    }

    bool hasNext() {
        return !st.empty();
    }

    void pushAllLeft(TreeNode* root) {
        while (root) {
            st.push(root);
            root = root->left;
        }
    }

    void pushAllRight(TreeNode* root) {
        while (root) {
            st.push(root);
            root = root->right;
        }
    }
    int top() {
        return st.top()->val;
    }
};


class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        BSTIterator* left = new BSTIterator(root, true);
        BSTIterator* right = new BSTIterator(root, false);

        while (left->hasNext() && right->hasNext()) {
            int l = left->top(), r = right->top();
            if (l >= r) return false;
            if (l + r == k) return true;
            else if (l + r < k) left->next();
            else right->next();
        }

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
