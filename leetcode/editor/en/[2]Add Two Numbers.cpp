//You are given two non-empty linked lists representing two non-negative integer
//s. The digits are stored in reverse order, and each of their nodes contains a si
//ngle digit. Add the two numbers and return the sum as a linked list. 
//
// You may assume the two numbers do not contain any leading zero, except the nu
//mber 0 itself. 
//
// 
// Example 1: 
//
// 
//Input: l1 = [2,4,3], l2 = [5,6,4]
//Output: [7,0,8]
//Explanation: 342 + 465 = 807.
// 
//
// Example 2: 
//
// 
//Input: l1 = [0], l2 = [0]
//Output: [0]
// 
//
// Example 3: 
//
// 
//Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
//Output: [8,9,9,9,0,0,0,1]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in each linked list is in the range [1, 100]. 
// 0 <= Node.val <= 9 
// It is guaranteed that the list represents a number that does not have leading
// zeros. 
// 
// Related Topics Linked List Math Recursion 
// 👍 13225 👎 2981


//leetcode submit region begin(Prohibit modification and deletion)
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

/*
 * solution 1: linked list iteration
 * time: O(n)
 * spaceL O(n)
 *
 * */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode();
        ListNode* prev = dummy;

        int sum = 0;
        while (l1 != NULL && l2 != NULL) {
            sum += l1->val + l2->val;
            ListNode* node = new ListNode(sum % 10);
            sum /= 10;

            prev->next = node;
            prev = prev->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1 != NULL) {
            sum += l1->val;
            ListNode* node = new ListNode(sum % 10);
            sum /= 10;

            prev->next = node;
            prev = prev->next;
            l1 = l1->next;
        }

        while (l2 != NULL) {
            sum += l2->val;
            ListNode* node = new ListNode(sum % 10);
            sum /= 10;

            prev->next = node;
            prev = prev->next;
            l2 = l2->next;
        }

        if (sum == 1) {
            ListNode* node = new ListNode(sum % 10);
            prev->next = node;
            prev = prev->next;
        }

        prev->next = NULL;

        return dummy->next;
    }
};

/*
 * solution 2: linked list iteration
 * time: O(n)
 * spaceL O(n)
 *
 * */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        cout << dummy->next;
        ListNode *cur = dummy, *p1 = l1, *p2 = l2;
        int sum = 0;

        while (p1 != nullptr || p2 != nullptr ) {
            if (p1 != nullptr) {
                sum += p1->val;
                p1 = p1->next;
            }

            if (p2 != nullptr) {
                sum += p2->val;
                p2 = p2->next;
            }

            cur->next = new ListNode(sum % 10);
            sum /= 10;
            cur = cur->next;
        }

        if (sum == 1) cur->next = new ListNode(1);

        return dummy->next;

    }
};
//leetcode submit region end(Prohibit modification and deletion)
