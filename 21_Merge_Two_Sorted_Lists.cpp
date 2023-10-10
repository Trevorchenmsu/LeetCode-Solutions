/*
solution: merge sort
time: O(m+n)
space: O(1), because we don't create new nodes to extra space
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr)
            return list2;

        if (list2 == nullptr)
            return list1;

        if (list1 == nullptr && list2 == nullptr)
            return nullptr;

        ListNode* list3 = new ListNode(0);
        ListNode* curr = list3;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                curr->next = list1;
                list1 = list1->next;
            }
            else {
                curr->next = list2;
                list2 = list2->next;
            }
            curr = curr->next;
        }

        if (list1)
            curr->next = list1;

        if (list2)
            curr->next = list2;

        return list3->next;
    }
};