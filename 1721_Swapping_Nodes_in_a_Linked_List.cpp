/*
solution 1: multiple iteration
time: O(n)
space: O(1)
*/
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        int len = 0;
        ListNode* cur = head;
        // find the length of the list
        while(cur) {
            len++;
            cur = cur->next;
        }
        // find the front node
        ListNode* frontNode = head;
        for (int i = 1; i < k; ++i) {
            frontNode = frontNode->next;
        }
        // find the ende node
        ListNode* endNode = head;
        for (int i = 0; i < len - k; ++i) {
            endNode = endNode->next;
        }
        
        swap(frontNode->val, endNode->val);
        return head;
    }
};