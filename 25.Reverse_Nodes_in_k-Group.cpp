/*
solution 1: iteration
time:
space:
*/
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;
        ListNode *dummy = new ListNode(-1), *pre = dummy, *cur = head;
        dummy->next = head;
        for (int i = 1; cur; ++i) {
            if (i % k == 0) {
                pre = reverseOneGroup(pre, cur->next);
                cur = pre->next;
            } else {
                cur = cur->next;
            }
        }
        return dummy->next;
    }
    ListNode* reverseOneGroup(ListNode* pre, ListNode* next) {
        ListNode *last = pre->next, *cur = last->next;
        while(cur != next) {
            last->next = cur->next;
            cur->next = pre->next;
            pre->next = cur;
            cur = last->next;
        }
        return last;
    }
};

/*
solution 2: recursion
time:
space:
*/
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || !head->next) return head;
        ListNode* cur = head;
        int count = 0;
        while(cur && count != k){
            count++;
            cur = cur->next;
        }
        if(count == k){
            cur = reverseKGroup(cur, k);
            while(count-- > 0){
                ListNode* temp = head->next;
                head->next =cur;
                cur = head;
                head = temp;
            }
            head = cur;
        }
        return head;
    }
};

