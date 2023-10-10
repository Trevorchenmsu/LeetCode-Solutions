//Given the head of a singly linked list and two integers left and right where l
//eft <= right, reverse the nodes of the list from position left to position right
//, and return the reversed list. 
//
// 
// Example 1: 
//
// 
//Input: head = [1,2,3,4,5], left = 2, right = 4
//Output: [1,4,3,2,5]
// 
//
// Example 2: 
//
// 
//Input: head = [5], left = 1, right = 1
//Output: [5]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the list is n. 
// 1 <= n <= 500 
// -500 <= Node.val <= 500 
// 1 <= left <= right <= n 
// 
//
// 
//Follow up: Could you do it in one pass? Related Topics Linked List 
// 👍 6175 👎 293


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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left >= right || !head) return head;

        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* pre = dummy;

        //i<left是走到left节点，i<left-1则是走到left前一个的节点
        for (int i = 0; i < left-1; ++i) pre = pre->next;

        // left当前所处的节点
        ListNode* cur = pre->next;
        ListNode* temp = nullptr;

        for (int i = left; i < right; ++i)
        {
            //因为要翻转节点，后面的要临时存起来
            temp = cur->next;
            //因为cur->next被临时存起来，它是因为会被修改才要存起来，目的是为了连接
            // 在原本cur->next后面的节点
            cur->next = temp->next;
            //这里不能用cur来赋值，因为cur是固定不移动的，实际上它代表的是pre->next
            //从下面也可以看出只是pre这个头的next每次指定的值都在变化，也就是说这不是普通的
            // 一个pass走过去cur指针一直前进的情况。在后面翻转的节点，都会被pre更新指向
            temp->next = pre->next;
            pre->next = temp;
        }

        return dummy->next;
    }
};

class Solution:
    def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
        if left >= right or not head: return head

        dummy = pre = ListNode()
        dummy.next = head
        pre = dummy

        for i in range(left - 1):
            pre = pre.next

        cur = pre.next

        for i in range(left, right):
            temp = cur.next
            cur.next = temp.next
            temp.next = pre.next
            pre.next = temp

        return dummy.next

//leetcode submit region end(Prohibit modification and deletion)
