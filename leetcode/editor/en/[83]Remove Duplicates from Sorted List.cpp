//Given the head of a sorted linked list, delete all duplicates such that each e
//lement appears only once. Return the linked list sorted as well. 
//
// 
// Example 1: 
//
// 
//Input: head = [1,1,2]
//Output: [1,2]
// 
//
// Example 2: 
//
// 
//Input: head = [1,1,2,3,3]
//Output: [1,2,3]
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
// Related Topics Linked List 
// 👍 2860 👎 154


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
 * solution 1: iteration
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        unordered_set<int> visited;
        ListNode* prev = new ListNode(0);
        ListNode* dummy = prev;

        ListNode* cur = head;
        while (cur != NULL) {
            if (visited.find(cur->val) == visited.end()) {
                prev->next = cur;
                prev = prev->next;
                visited.insert(cur->val);
            }
            cur = cur->next;
        }

        prev->next = NULL;

        return dummy->next;
    }
};

/*
 * solution 2: iteration, optimal
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* cur = head;
        while(cur->next){
            if(cur->next->val == cur->val){ //因为链表有序，所以不用set判定是否重复，可以直接从相邻节点判定
                cur->next = cur->next->next;
            } else{
                cur = cur->next;
            }
        }
        return head;
    }
};


/*
 * solution 3: iteration, easier to understand
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL) {
            return head;
        }

        ListNode* cur = head;
        ListNode* dummy = new ListNode();
        ListNode* prev = dummy;

        while (cur) {
            if (cur->next && cur->val == cur->next->val) {
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
//leetcode submit region end(Prohibit modification and deletion)
