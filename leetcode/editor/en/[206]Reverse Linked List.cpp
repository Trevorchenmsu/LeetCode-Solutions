//Given the head of a singly linked list, reverse the list, and return the rever
//sed list. 
//
// 
// Example 1: 
//
// 
//Input: head = [1,2,3,4,5]
//Output: [5,4,3,2,1]
// 
//
// Example 2: 
//
// 
//Input: head = [1,2]
//Output: [2,1]
// 
//
// Example 3: 
//
// 
//Input: head = []
//Output: []
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the list is the range [0, 5000]. 
// -5000 <= Node.val <= 5000 
// 
//
// 
// Follow up: A linked list can be reversed either iteratively or recursively. C
//ould you implement both? 
// Related Topics Linked List Recursion 
// 👍 11998 👎 207


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
 * solution 1: 链表翻转, iteration
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* new_head = nullptr;
        ListNode* cur = head;
        ListNode* temp = nullptr;

        while (cur)
        {
            temp = cur->next;
            cur->next = new_head;
            new_head = cur;
            cur = temp;
        }

        return new_head;
    }
};

class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        new_head = temp = None
        cur = head

        while cur:
            temp = cur.next
            cur.next= new_head
            new_head = cur
            cur = temp

        return new_head


/*
 * solution 2: 链表翻转, recursive
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    ListNode* new_head = nullptr;
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;
        ListNode* temp = nullptr;

        reverse(cur, temp);

        return new_head;
    }

    void reverse(ListNode* cur, ListNode* temp) {
        if (cur == nullptr) return;

        temp = cur->next;
        cur->next = new_head;
        new_head = cur;
        cur = temp;

        reverse(cur, temp);
    }
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        return reverse(head, nullptr);
    }

    ListNode* reverse(ListNode* head, ListNode* node) {
        if (head == nullptr) return node;

        ListNode* temp = head->next;
        head->next = node;

        return reverse(temp, head);
    }
};

class Solution:
def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
    return self.reverse(head, None)

    def reverse(self, head, node):
        if not head: return node

        temp = head.next
        head.next = node

        return self.reverse(temp, head)

//leetcode submit region end(Prohibit modification and deletion)
