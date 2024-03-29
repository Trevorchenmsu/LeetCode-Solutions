//Given the head of a linked list and an integer val, remove all the nodes of th
//e linked list that has Node.val == val, and return the new head. 
//
// 
// Example 1: 
//
// 
//Input: head = [1,2,6,3,4,5,6], val = 6
//Output: [1,2,3,4,5]
// 
//
// Example 2: 
//
// 
//Input: head = [], val = 1
//Output: []
// 
//
// Example 3: 
//
// 
//Input: head = [7,7,7,7], val = 7
//Output: []
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the list is in the range [0, 104]. 
// 1 <= Node.val <= 50 
// 0 <= val <= 50 
// 
// Related Topics Linked List Recursion 
// 👍 5035 👎 168


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
 * solution: two pointers
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (!head) return nullptr;

        ListNode* dummy = new ListNode();
        ListNode* prev = dummy;
        ListNode* cur = head;

        while (cur)
        {
            if (cur->val == val)
            {
                prev->next = cur->next;
            }
            else {
                prev->next = cur;
                prev = prev->next;
            }

            cur = cur->next;
        }

        return dummy->next;

    }
};


class Solution:
    def removeElements(self, head: Optional[ListNode], val: int) -> Optional[ListNode]:
        if not head: return None

        dummy = pre = ListNode()
        cur = head

        while cur:
            if cur.val == val: pre.next = cur.next
            else:
                pre.next = cur
                pre = pre.next

            cur = cur.next
        return dummy.next
//leetcode submit region end(Prohibit modification and deletion)
