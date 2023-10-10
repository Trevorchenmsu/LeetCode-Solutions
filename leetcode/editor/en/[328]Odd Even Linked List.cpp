//Given the head of a singly linked list, group all the nodes with odd indices t
//ogether followed by the nodes with even indices, and return the reordered list. 
//
//
// The first node is considered odd, and the second node is even, and so on. 
//
// Note that the relative order inside both the even and odd groups should remai
//n as it was in the input. 
//
// You must solve the problem in O(1) extra space complexity and O(n) time compl
//exity. 
//
// 
// Example 1: 
//
// 
//Input: head = [1,2,3,4,5]
//Output: [1,3,5,2,4]
// 
//
// Example 2: 
//
// 
//Input: head = [2,1,3,5,6,4,7]
//Output: [2,3,6,7,1,5,4]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the linked list is in the range [0, 104]. 
// -106 <= Node.val <= 106 
// 
// Related Topics Linked List 
// 👍 5373 👎 386


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
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return head;

        ListNode* dummy1 = new ListNode();
        ListNode* odd = dummy1;
        ListNode* dummy2 = new ListNode();
        ListNode* even = dummy2;
        ListNode* cur = head;

        int count = 0;
        while (cur)
        {
            if (count % 2 == 0)
            {
                odd->next = cur;
                odd = odd->next;
            }
            else
            {
                even->next = cur;
                even = even->next;
            }
            cur = cur->next;
            ++count;
        }
        even->next = nullptr;
        odd->next = dummy2->next;

        return dummy1->next;
    }
};

class Solution:
    def oddEvenList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head: return head

        dum1 = odd = ListNode()
        dum2 = even = ListNode()

        cur = head
        count = 0

        while cur:
            if count % 2 == 0:
                odd.next = cur
                odd = odd.next
            else:
                even.next =cur
                even = even.next

            cur = cur.next
            count += 1

        even.next = None
        odd.next = dum2.next

        return dum1.next
//leetcode submit region end(Prohibit modification and deletion)
