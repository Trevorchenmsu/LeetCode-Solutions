/*
solution 1: recursion
time: O(nlogn), find the middle we use O(n) or O(n/2), for each part we use binary search which is O(logn)
so total is (nlogn)
space: O(logn), the maximum we would store is the total tree height, which is logn.
*/
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return NULL;
        return toBST(head, NULL);
    }
    
private:
    TreeNode* toBST(ListNode* head, ListNode* tail) {
        if (head == tail) return NULL;
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != tail && fast->next != tail) {
            slow = slow->next;
            fast = fast->next->next;
        }        
        TreeNode* node = new TreeNode(slow->val);
        node->left = toBST(head, slow);
        node->right = toBST(slow->next, tail);
        return node;
    }
};

/*
solution: recursion
time: O(nlogn), find the middle we use O(n) or O(n/2), for each part we use binary search which is O(logn)
so total is (nlogn)
space: O(logn), the maximum we would store is the total tree height, which is logn.
*/