/*
solution: merge sort
time: O(m+n)
space: O(1), because we don't create new nodes to extra space
*/

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        if (l1 == nullptr && l2 == nullptr) return nullptr;
        
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;
        
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            }
            else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        
        if (l1 != nullptr) 
            cur->next = l1;
        if (l2 != nullptr) 
            cur->next = l2;
        
        return dummy->next;
    }
};