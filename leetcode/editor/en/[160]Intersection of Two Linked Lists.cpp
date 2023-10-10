//Given the heads of two singly linked-lists headA and headB, return the node at
// which the two lists intersect. If the two linked lists have no intersection at 
//all, return null. 
//
// For example, the following two linked lists begin to intersect at node c1: 
//
// The test cases are generated such that there are no cycles anywhere in the en
//tire linked structure. 
//
// Note that the linked lists must retain their original structure after the fun
//ction returns. 
//
// Custom Judge: 
//
// The inputs to the judge are given as follows (your program is not given these
// inputs): 
//
// 
// intersectVal - The value of the node where the intersection occurs. This is 0
// if there is no intersected node. 
// listA - The first linked list. 
// listB - The second linked list. 
// skipA - The number of nodes to skip ahead in listA (starting from the head) t
//o get to the intersected node. 
// skipB - The number of nodes to skip ahead in listB (starting from the head) t
//o get to the intersected node. 
// 
//
// The judge will then create the linked structure based on these inputs and pas
//s the two heads, headA and headB to your program. If you correctly return the in
//tersected node, then your solution will be accepted. 
//
// 
// Example 1: 
//
// 
//Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2
//, skipB = 3
//Output: Intersected at '8'
//Explanation: The intersected node's value is 8 (note that this must not be 0 i
//f the two lists intersect).
//From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [
//5,6,1,8,4,5]. There are 2 nodes before the intersected node in A; There are 3 no
//des before the intersected node in B.
// 
//
// Example 2: 
//
// 
//Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skip
//B = 1
//Output: Intersected at '2'
//Explanation: The intersected node's value is 2 (note that this must not be 0 i
//f the two lists intersect).
//From the head of A, it reads as [1,9,1,2,4]. From the head of B, it reads as [
//3,2,4]. There are 3 nodes before the intersected node in A; There are 1 node bef
//ore the intersected node in B.
// 
//
// Example 3: 
//
// 
//Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
//Output: No intersection
//Explanation: From the head of A, it reads as [2,6,4]. From the head of B, it r
//eads as [1,5]. Since the two lists do not intersect, intersectVal must be 0, whi
//le skipA and skipB can be arbitrary values.
//Explanation: The two lists do not intersect, so return null.
// 
//
// 
// Constraints: 
//
// 
// The number of nodes of listA is in the m. 
// The number of nodes of listB is in the n. 
// 1 <= m, n <= 3 * 104 
// 1 <= Node.val <= 105 
// 0 <= skipA < m 
// 0 <= skipB < n 
// intersectVal is 0 if listA and listB do not intersect. 
// intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect. 
// 
//
// 
//Follow up: Could you write a solution that runs in O(m + n) time and use only 
//O(1) memory? Related Topics Hash Table Linked List Two Pointers 
// 👍 8884 👎 880


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/*
Q:
1. 两个链表头距离交点的长度不同，双指针如何前进？
A:由于相交后的那部分节点数都相等，所以长度差别体现在相交前。因为题目提到了skipA和skipB，所以交点会是在链表中间的某一位置，不可能是链表头。因此，求出两个链表的长度差，让长的链表先走这个差值，当双指针对齐后，就可以同步前进。
2. 用什么标准判断该节点为两个链表的交点？
用节点地址进行判定，即直接用节点判定是否相等，不要用val。
*/

/*
 * solution: two pointers
 * time: O(m+n)
 * space: O(1)
 * */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;

        ListNode* la = headA;
        ListNode* lb = headB;
        int len_a = getLen(la);
        int len_b = getLen(lb);

        if (len_a > len_b) la = move(la, len_a, len_b);
        else lb = move(lb, len_b, len_a);

        for (int i = 0; i < min(len_a, len_b); ++i)
        {
            if (la == lb) return la;
            la = la->next;
            lb = lb->next;
        }

        return nullptr;

    }

    ListNode* move(ListNode* node, int num1, int num2)
    {
        for (int i = 0; i < num1 - num2; ++i)
        {
            node = node->next;
        }

        return node;
    }

    int getLen(ListNode* node)
    {
        int len = 0;
        while (node)
        {
            ++len;
            node = node->next;
        }

        return len;
    }
};

class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> Optional[ListNode]:
        if not headA or not headB: return None

        def getLen(node):
            len = 0
            while node:
                len += 1
                node = node.next
            return len

        def move(node, num):
            for i in range(num):
                node = node.next
            return node

        len_a = getLen(headA)
        len_b = getLen(headB)

        if len_a > len_b: headA = move(headA, len_a - len_b)
        else: headB = move(headB, len_b - len_a)

        for i in range(min(len_a, len_b)):
            if headA == headB: return headA
            headA = headA.next
            headB = headB.next

        return None

//leetcode submit region end(Prohibit modification and deletion)
