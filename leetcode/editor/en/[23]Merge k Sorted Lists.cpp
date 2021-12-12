//You are given an array of k linked-lists lists, each linked-list is sorted in 
//ascending order. 
//
// Merge all the linked-lists into one sorted linked-list and return it. 
//
// 
// Example 1: 
//
// 
//Input: lists = [[1,4,5],[1,3,4],[2,6]]
//Output: [1,1,2,3,4,4,5,6]
//Explanation: The linked-lists are:
//[
//  1->4->5,
//  1->3->4,
//  2->6
//]
//merging them into one sorted list:
//1->1->2->3->4->4->5->6
// 
//
// Example 2: 
//
// 
//Input: lists = []
//Output: []
// 
//
// Example 3: 
//
// 
//Input: lists = [[]]
//Output: []
// 
//
// 
// Constraints: 
//
// 
// k == lists.length 
// 0 <= k <= 10^4 
// 0 <= lists[i].length <= 500 
// -10^4 <= lists[i][j] <= 10^4 
// lists[i] is sorted in ascending order. 
// The sum of lists[i].length won't exceed 10^4. 
// 
// Related Topics Linked List Divide and Conquer Heap (Priority Queue) Merge Sor
//t 
// 👍 7757 👎 365


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
 * solution: merge sort + divide and conquer
 * time: O(nklogk), k is the number of lists. divide and conquer will take O(logk).
 *      merge k lists will take O(nk), n is the maximum length of the list.
 * space: O(1), merge list in-place, we don't generate new nodes. O(logk) for recursion stack space
 *
 * */

class Solution {
public:
    /**
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     */
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) {
            return NULL;
        }

        return mergeList(lists, 0, lists.size() - 1);
    }

    ListNode* mergeList (vector<ListNode *> &lists, int start, int end) {
        if (start == end) {
            return lists[start];
        }

        int mid = start + (end - start) / 2;
        ListNode* left = mergeList(lists, start, mid);
        ListNode* right = mergeList(lists, mid + 1, end);

        ListNode* res = mergeTwoList(left, right);

        return res;
    }

    ListNode* mergeTwoList(ListNode* L1, ListNode* L2) {
        ListNode* L3 = new ListNode();
        ListNode* cur = L3;
        while (L1 != NULL && L2 != NULL) {
            if (L1->val >= L2->val) {
                cur->next = L2;
                L2 = L2->next;
            }
            else {
                cur->next = L1;
                L1 = L1->next;
            }
            cur = cur->next;
        }

        if (L1 != NULL) {
            cur->next = L1;
        }

        if (L2 != NULL) {
            cur->next = L2;
        }

        return L3->next;
    }

};

/*
 * solution 2: mini heap
 * time: O(nklogk), nk is the total number of nodes in all lists
 * space: O(k)
 * */


class Solution {
public:

    struct cmp {
        bool operator() (const ListNode* L1, const ListNode* L2) {
            return L1->val > L2->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return NULL;
        }

        priority_queue<ListNode*, vector<ListNode*>, cmp> minPQ;

        for (auto &list : lists) { //O(klogk)
            if (list != NULL) {
                minPQ.push(list);
            }
        }

        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;

        while (!minPQ.empty()) {
            auto node = minPQ.top();
            minPQ.pop();

            cur->next = node;
            cur = cur->next;

            if (node->next != NULL) {
                minPQ.push(node->next);
            }
        }

        return dummy->next;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
