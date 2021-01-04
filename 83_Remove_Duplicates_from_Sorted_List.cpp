/*
Solution 1: iterative
time: O(n)
space: O(1)
*/

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr)
            return head;
        
        ListNode* dummy = new ListNode();
        dummy->next = head;
        
        while (head != nullptr && head->next != nullptr) {
            if (head->val == head->next->val) {
                head->next = head->next->next;
            } else head = head->next;
        }
        
        return dummy->next;
    }
};

/*
Solution 2: iterative
time: O(n)
space: O(1)
*/

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* cur = head;
        while(cur->next){
            if(cur->next->val == cur->val){
                cur->next = cur->next->next;
            } else{
                cur = cur->next;
            }
        }
        return head;
    }
};