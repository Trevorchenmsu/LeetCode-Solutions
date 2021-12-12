//Given the head of a linked list, find all the values that appear more than onc
//e in the list and delete the nodes that have any of those values. 
//
// Return the linked list after the deletions. 
//
// 
// Example 1: 
//
// 
//Input: head = [1,2,3,2]
//Output: [1,3]
//Explanation: 2 appears twice in the linked list, so all 2's should be deleted.
// After deleting all 2's, we are left with [1,3].
// 
//
// Example 2: 
//
// 
//Input: head = [2,1,1,2]
//Output: []
//Explanation: 2 and 1 both appear twice. All the elements should be deleted.
// 
//
// Example 3: 
//
// 
//Input: head = [3,2,2,1,3,2,4]
//Output: [1,4]
//Explanation: 3 appears twice and 2 appears three times. After deleting all 3's
// and 2's, we are left with [1,4].
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the list is in the range [1, 105] 
// 1 <= Node.val <= 105 
// Related Topics Hash Table Linked List 
// 👍 58 👎 4


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
 * solution: iteration
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        if (head == NULL) {
            return head;
        }

        unordered_map<int, int> cnts;
        ListNode* cur = head;
        while (cur) {
            cnts[cur->val]++;
            cur = cur->next;
        }

        // 这个写法为什么不会错？因为cur和prev,dummy都是独立的，dummy用来保持prev的起点，而prev用来跟cur进行同步遍历
        // 它们的链接是在while循环中建立的
        ListNode* dummy = new ListNode();
        ListNode* prev = dummy;
        cur = head;

        /* 注意下面写法的错误点：虽然设置dummy和prev为辅助点，但实际上可以看到dummy和prev都是cur，
           一开始就已经有链接。在while循环中，如果再让prev->next=cur,prev自身就形成了一个环，陷入死循环。
             ListNode* dummy = new ListNode(-1);
             ListNode* prev = cur;
             dummy = prev;
         */
        while (cur) {
            if (cnts[cur->val] <= 1) {
                prev->next = cur;
                prev = prev->next;
            }

            cur = cur->next;
        }

        prev->next = NULL;

        return dummy->next;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
