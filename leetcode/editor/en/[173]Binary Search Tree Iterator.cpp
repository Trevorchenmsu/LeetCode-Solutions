//Implement the BSTIterator class that represents an iterator over the in-order 
//traversal of a binary search tree (BST): 
//
// 
// BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. Th
//e root of the BST is given as part of the constructor. The pointer should be ini
//tialized to a non-existent number smaller than any element in the BST. 
// boolean hasNext() Returns true if there exists a number in the traversal to t
//he right of the pointer, otherwise returns false. 
// int next() Moves the pointer to the right, then returns the number at the poi
//nter. 
// 
//
// Notice that by initializing the pointer to a non-existent smallest number, th
//e first call to next() will return the smallest element in the BST. 
//
// You may assume that next() calls will always be valid. That is, there will be
// at least a next number in the in-order traversal when next() is called. 
//
// 
// Example 1: 
//
// 
//Input
//["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext
//", "next", "hasNext"]
//[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
//Output
//[null, 3, 7, true, 9, true, 15, true, 20, false]
//
//Explanation
//BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
//bSTIterator.next();    // return 3
//bSTIterator.next();    // return 7
//bSTIterator.hasNext(); // return True
//bSTIterator.next();    // return 9
//bSTIterator.hasNext(); // return True
//bSTIterator.next();    // return 15
//bSTIterator.hasNext(); // return True
//bSTIterator.next();    // return 20
//bSTIterator.hasNext(); // return False
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 105]. 
// 0 <= Node.val <= 106 
// At most 105 calls will be made to hasNext, and next. 
// 
//
// 
// Follow up: 
//
// 
// Could you implement next() and hasNext() to run in average O(1) time and use 
//O(h) memory, where h is the height of the tree? 
// 
// Related Topics Stack Tree Design 
// 👍 3760 👎 329


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
 * solution 1: tree inorder traversal
 * time: O(1) for next() and hasNext()
 * space: O(n) for queue storage
 * */
class BSTIterator {
public:
    queue<int> q;
    BSTIterator(TreeNode* root) {
        inorder(root, q);
    }

    int next() {
        int res = q.front(); q.pop();
        return res;
    }

    bool hasNext() {
        return !q.empty();
    }

    void inorder(TreeNode* root, queue<int> &q) {
        if (root == NULL) return;
        inorder(root->left, q);
        q.push(root->val);
        inorder(root->right, q);
    }
};


/*
 * solution 2: tree inorder traversal
 * time: worst O(h) for next(), average O(1) for next(), O(1) for hasNext()
 * space: O(h) for stack storage
 * */
class BSTIterator {
public:
    TreeNode* root;
    stack<TreeNode*> st;

    BSTIterator(TreeNode* root) {
        this->root = root;
    }

    int next() {
        while (root) { // O(h)
            st.push(root);
            root = root->left;
        }

        TreeNode* cur = st.top(); st.pop();
        root = cur->right;
        return cur->val;

    }

    bool hasNext() {
        return (root || !st.empty());
    }
};

/*
 * solution 3: tree inorder traversal, optimal
 * time: worst O(h) for next(), average O(1) for next(), O(1) for hasNext()
 * space: O(h) for stack storage
 * */
class BSTIterator {
public:
    stack<TreeNode*> st;
    BSTIterator(TreeNode* root) {
        pushAllLeft(root);
    }

    int next() {
        TreeNode* node = st.top(); st.pop();
        pushAllLeft(node->right);
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
};


/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
//leetcode submit region end(Prohibit modification and deletion)
