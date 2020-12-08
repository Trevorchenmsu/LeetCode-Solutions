/*
time: O(max(m, n))
space: O(max(m, n))
*/
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);        
        ListNode* cur = dummy;
        ListNode* p1 = l1, *p2 = l2;
        int sum = 0;
        
        while(p1 || p2){
            if(p1){
                sum += p1->val;
                p1 = p1->next;
            }
            
            if(p2){
                sum += p2->val;
                p2 = p2->next;
            }
            
            cur->next = new ListNode(sum % 10);
            sum /= 10;
            cur = cur->next;
        }
        
        if(sum == 1){
            cur->next = new ListNode(1);
        }
        
        return dummy->next;
    }
};