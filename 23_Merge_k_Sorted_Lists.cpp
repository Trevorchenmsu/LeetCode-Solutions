/*
solution: divide and conquer
time: O(nlogk), n is the number of the lists, k is the length of each list
space: O(nlogk)?
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return NULL;
        if(lists.size() == 1) return lists[0];
        if(lists.size() == 2){
            return mergeTwoLists(lists[0], lists[1]);
        }
        int mid = lists.size() / 2;
        vector<ListNode*> sub_l1;
        vector<ListNode*> sub_l2;
        for(int i = 0; i < mid; i++){
            sub_l1.push_back(lists[i]);
        }
        for(int i = mid; i < lists.size(); i++){
            sub_l2.push_back(lists[i]);
        }
        ListNode *l1 = mergeKLists(sub_l1);
        ListNode *l2 = mergeKLists(sub_l2);
        return mergeTwoLists(l1, l2);
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode temp_head(0);
        ListNode *pre = &temp_head;
        while(l1 && l2){
            if(l1->val < l2->val){
                pre->next = l1;
                l1 = l1->next;
            }
            else{
                pre->next = l2;
                l2 = l2->next;
            }
            pre = pre->next;
        }
        if(l1){
            pre->next = l1;
        }
        if(l2){
            pre->next = l2;
        }
        return temp_head.next;
    }
};