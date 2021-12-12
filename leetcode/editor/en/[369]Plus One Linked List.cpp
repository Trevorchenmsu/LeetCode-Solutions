//Given a non-negative integer represented as a linked list of digits, plus one 
//to the integer. 
//
// The digits are stored such that the most significant digit is at the head of 
//the list. 
//
// 
// Example 1: 
// Input: head = [1,2,3]
//Output: [1,2,4]
// Example 2: 
// Input: head = [0]
//Output: [1]
// 
// 
// Constraints: 
//
// 
// The number of nodes in the linked list is in the range [1, 100]. 
// 0 <= Node.val <= 9 
// The number represented by the linked list does not contain leading zeros exce
//pt for the zero itself. 
// 
// Related Topics Linked List Math 
// 👍 700 👎 38


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
 * solution 1: reverse linked list + traversal
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    ListNode* plusOne(ListNode* head) {
        if (head == NULL) {
            return head;
        }

        ListNode* head_new = reverseList(head);
        ListNode* cur = head_new;
        ListNode* pre = cur;

        int carry = 1;
        while (cur) {
            pre = cur;
            int num = cur->val + carry;
            cur->val = num % 10;
            carry = num / 10;
            if (carry == 0) {
                break;
            }
            cur = cur->next;
        }

        if (carry == 1) {
            pre->next = new ListNode(1);
        }

        return reverseList(head_new);

    }

    ListNode* reverseList(ListNode* head) {
        ListNode* new_head = NULL;

        while (head) {
            ListNode* temp = head->next;
            head->next = new_head;
            new_head = head;
            head = temp;
        }

        return new_head;
    }
};

/*
 * solution 2: recursion, optimal
 * time: O(n)
 * space: O(n)，栈空间
 * */
class Solution {
public:
    ListNode* plusOne(ListNode* head) {
        if (head == NULL) {
            return head;
        }

        int carry = recursion(head);

        if (carry == 1) {
            ListNode* res = new ListNode(1);
            res->next = head;
            return res;
        }

        return head;
    }

    int recursion(ListNode* node) {
        if (node == NULL) {
            return 1;
        }

        int num = node->val + recursion(node->next);
        node->val = num % 10;
        return num / 10;
    }
};


/*
 * solution 3: iteration
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    ListNode* plusOne(ListNode* head) {
        stack<ListNode*> s;
        ListNode *cur = head;

        while (cur) {
            s.push(cur);
            cur = cur->next;
        }

        int carry = 1;
        while (!s.empty() && carry) {
            ListNode *t = s.top(); s.pop();
            int sum = t->val + carry;
            t->val = sum % 10;
            carry = sum / 10;
        }

        if (carry) {
            ListNode *new_head = new ListNode(1);
            new_head->next = head;
            head = new_head;
        }

        return head;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
