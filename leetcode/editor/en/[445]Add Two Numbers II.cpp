//You are given two non-empty linked lists representing two non-negative integer
//s. The most significant digit comes first and each of their nodes contains a sin
//gle digit. Add the two numbers and return the sum as a linked list. 
//
// You may assume the two numbers do not contain any leading zero, except the nu
//mber 0 itself. 
//
// 
// Example 1: 
//
// 
//Input: l1 = [7,2,4,3], l2 = [5,6,4]
//Output: [7,8,0,7]
// 
//
// Example 2: 
//
// 
//Input: l1 = [2,4,3], l2 = [5,6,4]
//Output: [8,0,7]
// 
//
// Example 3: 
//
// 
//Input: l1 = [0], l2 = [0]
//Output: [0]
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
//
// 
// Follow up: Could you solve it without reversing the input lists? 
// Related Topics Linked List Math Stack 
// 👍 3555 👎 227


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

//这个方法过不了在head前面进位的情况
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        ListNode* list1 = l1, *list2 = l2;
        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;

        int len1 = getLength(list1);
        int len2 = getLength(list2);

        if (len1 > len2)
        {
            for (int i = 0; i < len1 - len2; ++i)
            {
                cur->next = list1;
                list1 = list1->next;
                cur = cur->next;
            }
        }
        else {
            for (int i = 0; i < len2 - len1; ++i)
            {
                cur->next = list2;
                list2 = list2->next;
                cur = cur->next;
            }
        }

        int carry = 0;
        while (list1 && list2)
        {
            int sum = list1->val + list2->val;
            ListNode* node = new ListNode(sum % 10);
            carry = sum / 10;
            cur->val += carry;

            cur->next = node;
            cur = cur->next;
            list1 = list1->next;
            list2 = list2->next;
        }

        cur = dummy->next;
        while (cur)
        {
            if (cur->next && cur->next->val > 9)
            {
                cur->val += cur->next->val / 10;
                cur->next->val %= 10;
            }
            cur = cur->next;
        }

        return dummy->next;
    }


    int getLength(ListNode* node) {
        int len = 0;
        while (node)
        {
            ++len;
            node = node->next;
        }

        return len;
    }
};

/*
 * solution 1: stack to reversely iterate linked list
 * time: O(m+n)
 * space: O(m+n)
 * */
//结构清晰的解法
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1 = getValues(l1);
        stack<int> s2 = getValues(l2);

        ListNode* cur = nullptr;
        int sum = 0, carry = 0;

        while (!s1.empty() && !s2.empty())
        {
            sum = s1.top() + s2.top() + carry;
            cur = forward(sum, carry, cur);
            s1.pop(), s2.pop();
        }

        while (!s1.empty())
        {
            sum = s1.top() + carry;
            cur = forward(sum, carry, cur);
            s1.pop();
        }


        while (!s2.empty())
        {
            sum = s2.top() + carry;
            cur = forward(sum, carry, cur);
            s2.pop();
        }

        if (carry > 0)
        {
            ListNode* node = new ListNode(carry);
            node->next = cur;
            cur = node;
        }

        return cur;

    }

    ListNode* forward(int sum, int& carry, ListNode* cur) {
        ListNode* node = new ListNode(sum % 10);
        carry = sum / 10;
        node->next = cur;
        cur = node;
        return cur;
    }

    stack<int> getValues(ListNode* head)
    {
        stack<int> stk;
        while (head)
        {
            stk.push(head->val);
            head = head->next;
        }

        return stk;
    }
};

class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        def getValues(head):
            st = []
            while head:
                st.append(head.val)
                head = head.next
            return st

        def forward(sum, carry, cur):
            node = ListNode(sum % 10)
            carry = sum // 10
            node.next = cur
            cur = node
            return cur, carry

        s1 = getValues(l1)
        s2 = getValues(l2)

        cur = None
        sum = carry = 0
        while s1 and s2:
            sum = s1.pop() + s2.pop() + carry
            cur, carry = forward(sum, carry, cur)

        while s1:
            sum = s1.pop() + carry
            cur, carry = forward(sum, carry, cur)

        while s2:
            sum = s2.pop() + carry
            cur, carry = forward(sum, carry, cur)

        if carry > 0:
            node = ListNode(carry)
            node.next = cur
            cur = node

        return cur


/*
 * solution 2: stack to reversely iterate linked list
 * time: O(m+n)
 * space: O(m+n)
 * */
//原理与解法1相同，但是因为后面两个循环的处理都放在了一个循环里面，速度更快
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1 = getValues(l1);
        stack<int> s2 = getValues(l2);

        int carry = 0;
        ListNode* l3 = nullptr;

        while (!s1.empty() or !s2.empty() or carry != 0)
        {
            int val1 = s1.empty() ? 0 : s1.top();
            int val2 = s2.empty() ? 0 : s2.top();

            if (!s1.empty()) s1.pop();
            if (!s2.empty()) s2.pop();

            int sum = val1 + val2 + carry;
            ListNode* node = new ListNode(sum % 10);
            carry = sum / 10;

            node->next = l3;
            l3 = node;
        }

        return l3;

    }

    stack<int> getValues(ListNode* head)
    {
        stack<int> stk;
        while (head)
        {
            stk.push(head->val);
            head = head->next;
        }

        return stk;
    }
};


class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        def getValues(head):
            st = []
            while head:
                st.append(head.val)
                head = head.next
            return st

        s1 = getValues(l1)
        s2 = getValues(l2)
        carry = 0
        l3 = None

        while s1 or s2 or carry:
            val1 = 0 if not s1 else s1.pop()
            val2 = 0 if not s2 else s2.pop()

            sum = val1 + val2 + carry
            node = ListNode(sum % 10)
            carry = sum // 10

            node.next = l3
            l3 = node

        return l3

//leetcode submit region end(Prohibit modification and deletion)
