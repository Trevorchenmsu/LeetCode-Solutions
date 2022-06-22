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
 * solution 1: merge sort + divide and conquer
 * time: O(Nlogk), k is the number of lists. N is the total number of nodes in all the lists
 * space: O(1), merge list in-place, we don't generate new nodes. O(logk) for recursion stack space
 *
 * */

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty() || lists.size() == 0) return nullptr;
        return mergeKL(0, lists.size() - 1, lists);
    }

    ListNode* mergeKL(int start, int end, vector<ListNode*>& lists) {
        if (start == end) return lists[start];

        int mid = start + (end - start) / 2;

        ListNode* left = mergeKL(start, mid, lists);
        ListNode* right = mergeKL(mid + 1, end, lists);

        return mergeTwoList(left, right);
    }


    ListNode* mergeTwoList(ListNode* l1, ListNode* l2) {
        ListNode* l3 = new ListNode();
        ListNode* cur = l3;

        while (l1 && l2) {
            if (l1->val <= l2->val) {
                cur->next = l1;
                l1 = l1->next;
            }
            else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }

        if (l1) {
            cur->next = l1;
        }

        if (l2) {
            cur->next = l2;
        }

        return l3->next;
    }
};


/*
 * solution 1: merge sort + divide and conquer, Python解法
 * time: O(Nlogk), k is the number of lists. N is the total number of nodes in all the lists
 * space: O(1), merge list in-place, we don't generate new nodes. O(logk) for recursion stack space
 *
 * */
class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
            if lists is None or len(lists) == 0: return None

            def mergeKL(start, end, lists):
                if start == end: return lists[start]

                mid = start + (end - start) // 2
                left = mergeKL(start, mid, lists)
                right = mergeKL(mid + 1, end, lists)

                return mergeTwoList(left, right)


            def mergeTwoList(l1, l2):
                l3 = cur = ListNode()

                while l1 and l2:
                    if l1.val <= l2.val:
                        cur.next = l1
                        l1 = l1.next
                    else:
                        cur.next = l2
                        l2 = l2.next
                    cur = cur.next


                if l1: cur.next = l1
                if l2: cur.next = l2

                return l3.next


            return mergeKL(0, len(lists) - 1, lists)


/*
 * solution 2: mini heap
 * time: O(Nlogk), N is the total number of nodes in all lists
 * space: O(k)
 * */


class Solution {
public:

    struct cmp {
        bool operator() (const ListNode* L1, const ListNode* L2) {
            return L1->val > L2->val; //最小堆，堆顶最小，可以理解为从下到上为降序，所以是大于号，跟vector排序相反
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return NULL;
        }

        priority_queue<ListNode*, vector<ListNode*>, cmp> minPQ;

        for (auto &list : lists) { //O(nlogk), n is the number of lists
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

/*
 * solution 2: mini heap，python解法
 * time: O(Nlogk), N is the total number of nodes in all lists
 * space: O(k)
 * */
class Solution:
   def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        if lists is None or len(lists) == 0: return None

        # 这里的i是必要的，因为当val相同时，需要考虑优先添加哪个idx，否则下一个比较就是节点的比较，不合法
        min_heap = [(l.val, i, l) for i, l in enumerate(lists) if l]
        heapify(min_heap)

        l3 = cur = ListNode()

        while len(min_heap) > 0:
            val, idx, node = min_heap[0]
            heapq.heappop(min_heap)

            cur.next = node
            cur = cur.next

            if node.next:
                heapq.heappush(min_heap, (cur.next.val, idx, cur.next))

        return l3.next
//leetcode submit region end(Prohibit modification and deletion)
