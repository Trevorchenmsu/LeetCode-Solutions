//You are given the head of a linked list with n nodes. 
//
// For each node in the list, find the value of the next greater node. That is, 
//for each node, find the value of the first node that is next to it and has a str
//ictly larger value than it. 
//
// Return an integer array answer where answer[i] is the value of the next great
//er node of the ith node (1-indexed). If the ith node does not have a next greate
//r node, set answer[i] = 0. 
//
// 
// Example 1: 
//
// 
//Input: head = [2,1,5]
//Output: [5,5,0]
// 
//
// Example 2: 
//
// 
//Input: head = [2,7,4,3,5]
//Output: [7,0,5,5,0]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the list is n. 
// 1 <= n <= 104 
// 1 <= Node.val <= 109 
// 
// Related Topics Array Linked List Stack Monotonic Stack 
// 👍 2267 👎 99


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
如果为7，要遍历到最后面才知道没有比它大的，这怎么解决？
用resize增大数组时默认为0，如果后面没有更新，它就一直为0。题目用的是滞后更新的策略
两个很重要的trick：用nums记录整个链表值，方便后面下标查找。用res逐渐最大结果范围，
初始加入的元素为0，如果还没遇到更大的元素，就一直为0。当遇到不满足单调栈的情况时，弹栈
会一直弹出不满足的情况，所以前面滞后未更新的元素就能被更新，而不需要多余的循环。
*/

/*
 * solution 1 : monotonic decreasing stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> nums, res;
        stack<int> st;
        int cnt = 0;

        while (head)
        {
            nums.push_back(head->val);
            while (!st.empty() && head->val > nums[st.top()])
            {
                res[st.top()] = head->val;
                st.pop();
            }

            st.push(cnt);
            res.resize(++cnt);
            head = head->next;
        }

        return res;
    }
};
class Solution:
    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        nums,res,st = [],[],[]

        while head:
            nums.append(head.val)

            while len(st) > 0 and head.val > nums[st[-1]]:
                res[st[-1]] = head.val
                st.pop()

            st.append(len(nums) - 1);
            res.append(0);
            head = head.next
        return res
/*
 * solution 2: monotonic decreasing stack， 空间节省一点，但是时间慢一点
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> res;
        stack<int> st;

        while (head)
        {
            while (!st.empty() && head->val > res[st.top()])
            {
                res[st.top()] = head->val;
                st.pop();
            }
            st.push(res.size());
            res.push_back(head->val);
            head = head->next;
        }

        while (!st.empty())
        {
            res[st.top()] = 0;
            st.pop();
        }

        return res;
    }
};

class Solution:
    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        res, st = [], []

        while head:
            while len(st) > 0 and head.val > res[st[-1]]:
            res[st.pop()] = head.val

            st.append(len(res));
            res.append(head.val);
            head = head.next

        for i in st: res[i] = 0

        return res
//leetcode submit region end(Prohibit modification and deletion)
