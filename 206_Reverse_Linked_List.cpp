/*
solution: iteration
time: O(n)
space: O(1)
*/
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next)
            return head;
        
        ListNode* newHead = NULL;
        while(head){
            ListNode* next = head->next; // backup the rest of the linked list
            head->next = newHead; // connect the newHead with the previous head
            newHead = head; // update the rear part of the linked list
            head = next;  // update the head, use the backup linked list elements
        }
        return newHead;
    }
};