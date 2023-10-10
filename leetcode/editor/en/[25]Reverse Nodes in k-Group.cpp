//Given the head of a linked list, reverse the nodes of the list k at a time, an
//d return the modified list. 
//
// k is a positive integer and is less than or equal to the length of the linked
// list. If the number of nodes is not a multiple of k then left-out nodes, in the
// end, should remain as it is. 
//
// You may not alter the values in the list's nodes, only nodes themselves may b
//e changed. 
//
// 
// Example 1: 
//
// 
//Input: head = [1,2,3,4,5], k = 2
//Output: [2,1,4,3,5]
// 
//
// Example 2: 
//
// 
//Input: head = [1,2,3,4,5], k = 3
//Output: [3,2,1,4,5]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the list is n. 
// 1 <= k <= n <= 5000 
// 0 <= Node.val <= 1000 
// 
//
// 
// Follow-up: Can you solve the problem in O(1) extra memory space? 
// Related Topics Linked List Recursion 
// 👍 7393 👎 502


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
 * solution: linkedin list reverse iteration
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head) return head;
        vector<int> values, rev;
        ListNode* cur = head;
        ListNode* dummy = new ListNode();
        ListNode* l3 = new ListNode();
        dummy = l3;

        // O(n)
        while (cur)
        {
            values.push_back(cur->val);
            cur = cur->next;
        }

        // O(n)，因为i以k为step，所以即使是逆向避免，最终也只是遍历整个链表
        for (auto i = 0; i < values.size(); )
        {
            if (i + k <= values.size())
            {
                for (int j = i + k - 1; j >= i; --j)
                {
                    rev.push_back(values[j]);
                }
                i = i + k;
            }
            else
            {
                rev.push_back(values[i++]);
            }
        }

        // O(n)
        for (auto i = 0; i < rev.size(); ++i)
        {
            ListNode* node = new ListNode(rev[i]);
            l3->next = node;
            l3 = l3->next;
        }

        return dummy->next;
    }
};


/*
 * solution: linkedin list reverse recursion
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || !head->next) return head; // head->next用来考虑最后一个节点的情况
        ListNode* cur = head;
        int cnt = 0;

        while (cur && cnt != k)
        {
            ++cnt;
            cur = cur->next;
        }

        // 这个等号的判断有必要，因为假如cur从倒数第二个走到最后一个节点，而k=3，此时
        // 不满足翻转的要求，所以不会对剩下的节点进行翻转，直接返回当前的head
        if (cnt == k)
        {
            cur = reverseKGroup(cur, k);
            while (cnt-- > 0) // 漏了循环，因为要进行k翻转
            {
                ListNode* temp = head->next;
                head->next = cur;
                cur = head;
                head = temp;
            }
            head = cur; //漏了这一步，因为当cur翻转以后，要更新当前的head
        }

        return head;
    }
};


class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        if not head or not head.next: return head
        cur = head
        cnt = 0

        while cur and cnt != k:
            cnt += 1
            cur = cur.next

        if cnt == k:
            cur = self.reverseKGroup(cur, k)
            while cnt > 0:
                temp = head.next
                head.next = cur
                cur = head
                head = temp
                cnt -= 1
            head = cur

        return head
//leetcode submit region end(Prohibit modification and deletion)
