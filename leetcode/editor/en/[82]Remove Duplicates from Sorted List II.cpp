//Given the head of a sorted linked list, delete all nodes that have duplicate n
//umbers, leaving only distinct numbers from the original list. Return the linked 
//list sorted as well. 
//
// 
// Example 1: 
//
// 
//Input: head = [1,2,3,3,4,4,5]
//Output: [1,2,5]
// 
//
// Example 2: 
//
// 
//Input: head = [1,1,1,2,3]
//Output: [2,3]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the list is in the range [0, 300]. 
// -100 <= Node.val <= 100 
// The list is guaranteed to be sorted in ascending order. 
// 
// Related Topics Linked List Two Pointers 
// 👍 3287 👎 130


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
  * solution 1: iteration + hash table
  * time: O(n)
  * space: O(1)
  * */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL) {
            return NULL;
        }

        ListNode* cur = head;
        unordered_map<int, int> count;

        while (cur) {
            count[cur->val]++;
            cur = cur->next;
        }

        ListNode* prev = new ListNode(-1);
        ListNode* dummy = prev;
        cur = head;
        while (cur) {
            if(count[cur->val] > 1) {
                cur = cur->next;
                continue;
            }
            prev->next = cur;
            prev = prev->next;
            cur = cur->next;
        }

        prev->next = NULL;

        return dummy->next;
    }
};

/*
 * solution 2: iteration
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL) {
            return NULL;
        }

        ListNode* prev = new ListNode(-1);
        ListNode* dummy = prev;
        ListNode* cur = head;

        while (cur) {
            if (cur->next && cur->val == cur->next->val) {
                int sameVal = cur->val;
                while(cur && cur->val == sameVal) {
                    cur = cur->next;
                }
            }
            else {
                prev->next = cur;
                prev = prev->next;
                cur = cur->next;
            }
        }

        prev->next = NULL;

        return dummy->next;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
