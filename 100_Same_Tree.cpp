/*
solution 1 : recursion
time: O(n)
space: O(log(N)) in the best case of completely balanced tree and
		O(N) in the worst case of completely unbalanced tree,
		to keep a recursion stack.
*/

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if (!p || !q) {
            return false;
        }
        if (p->val != q->val) {
            return false;
        }
        
        return isSameTree(p->left, q->left) && 
               isSameTree(p->right, q->right);
    }
};

/*
solution 2 : iteration
time: O(n)
space: O(log(N)) in the best case of completely balanced tree and
		O(N) in the worst case of completely unbalanced tree,
		to keep a recursion stack.
*/

class Solution {
private:
    bool check(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if (!p || !q) {
            return false;
        }
        if (p->val != q->val) {
            return false;
        }
        return true;
    }
    
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if (!check(p, q)) {
            return false;
        }
        
        // initialize deque
        deque<TreeNode*> DQ_p;
        deque<TreeNode*> DQ_q;
        DQ_p.push_back(p);
        DQ_q.push_back(q);
        
        while (!DQ_p.empty()) {
            p = DQ_p.front();
            DQ_p.pop_front();
            q = DQ_q.front();
            DQ_q.pop_front();
            
            if (!check(p, q)) {
                return false;
            }
            
            if (!check(p->left, q->left)) {
                return false;
            }
            if (p->left) {
                DQ_p.push_back(p->left);
                DQ_q.push_back(q->left);
            }
            if (!check(p->right, q->right)) {
                return false;
            }
            if (p->right) {
                DQ_p.push_back(p->right);
                DQ_q.push_back(q->right);
            }
        }
        return true;
    }
};