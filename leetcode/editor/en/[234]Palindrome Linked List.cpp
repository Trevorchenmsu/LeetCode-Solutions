//Given the head of a singly linked list, return true if it is a palindrome. 
//
// 
// Example 1: 
//
// 
//Input: head = [1,2,2,1]
//Output: true
// 
//
// Example 2: 
//
// 
//Input: head = [1,2]
//Output: false
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the list is in the range [1, 105]. 
// 0 <= Node.val <= 9 
// 
//
// 
//Follow up: Could you do it in O(n) time and O(1) space? Related Topics Linked 
//List Two Pointers Stack Recursion 
// 👍 9002 👎 556


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
 * solution: two pointers, linked list reverse
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        /*
        Q:链表两端如何同时遍历?找中点进行分段，然后对后半段进行翻转
        2. 求中点。分奇偶
        3. 对后半段翻转
        4. 双指针遍历判断
        */

        if (!head) return true;
        ListNode* mid = getMiddle(head);
        //这是我不会的地方。把mid->next后半部翻转后，传回来还需要和原来的mid->next连接上
        mid->next = reverse(mid->next);
        ListNode* p = head;
        ListNode* q = mid->next;

        while (p && q)
        {
            if (p->val != q->val) return false;
            p = p->next;
            q = q->next;
        }

        return true;
    }

    ListNode* getMiddle(ListNode* head)
    {
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverse(ListNode* head)
    {
        ListNode* new_head = nullptr;
        ListNode* temp;
        while (head)
        {
            temp = head->next;
            head->next = new_head;
            new_head = head;
            head = temp;
        }

        return new_head;
    }
};


class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        if not head: return True

        def getMiddle(node):
            slow, fast = node, node.next
            while fast and fast.next:
                slow = slow.next
                fast = fast.next.next
            return slow

        def reverse(head):
            new_head = None
            while head:
                temp = head.next
                head.next = new_head
                new_head = head
                head = temp

            return new_head

        mid = getMiddle(head)
        mid.next = reverse(mid.next)
        p = mid.next
        q = head

        while p and q:
            if p.val != q.val: return False
            p = p.next
            q = q.next

        return True
//leetcode submit region end(Prohibit modification and deletion)
