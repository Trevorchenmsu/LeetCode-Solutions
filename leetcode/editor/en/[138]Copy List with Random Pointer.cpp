//A linked list of length n is given such that each node contains an additional 
//random pointer, which could point to any node in the list, or null. 
//
// Construct a deep copy of the list. The deep copy should consist of exactly n 
//brand new nodes, where each new node has its value set to the value of its corre
//sponding original node. Both the next and random pointer of the new nodes should
// point to new nodes in the copied list such that the pointers in the original li
//st and copied list represent the same list state. None of the pointers in the ne
//w list should point to nodes in the original list. 
//
// For example, if there are two nodes X and Y in the original list, where X.ran
//dom --> Y, then for the corresponding two nodes x and y in the copied list, x.ra
//ndom --> y. 
//
// Return the head of the copied linked list. 
//
// The linked list is represented in the input/output as a list of n nodes. Each
// node is represented as a pair of [val, random_index] where: 
//
// 
// val: an integer representing Node.val 
// random_index: the index of the node (range from 0 to n-1) that the random poi
//nter points to, or null if it does not point to any node. 
// 
//
// Your code will only be given the head of the original linked list. 
//
// 
// Example 1: 
//
// 
//Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
//Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
// 
//
// Example 2: 
//
// 
//Input: head = [[1,1],[2,1]]
//Output: [[1,1],[2,1]]
// 
//
// Example 3: 
//
// 
//
// 
//Input: head = [[3,null],[3,0],[3,null]]
//Output: [[3,null],[3,0],[3,null]]
// 
//
// Example 4: 
//
// 
//Input: head = []
//Output: []
//Explanation: The given linked list is empty (null pointer), so return null.
// 
//
// 
// Constraints: 
//
// 
// 0 <= n <= 1000 
// -10000 <= Node.val <= 10000 
// Node.random is null or is pointing to some node in the linked list. 
// 
// Related Topics Hash Table Linked List 
// 👍 5935 👎 862


//leetcode submit region begin(Prohibit modification and deletion)
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

/*
 * solution 1: iteration + hash table
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return head;

        unordered_map<Node*, Node*> old_to_new;

        Node* cur = head;

        while (cur) {
            Node* node = new Node(cur->val);
            old_to_new[cur] = node;
            cur = cur->next;
        }

        cur = head;

        while (cur) {
            old_to_new[cur]->next = old_to_new[cur->next];
            old_to_new[cur]->random = old_to_new[cur->random];
            cur = cur->next;
        }

        return old_to_new[head];
    }
};

/*
 * solution 1: iteration + hash table， python解法
 * time: O(n)
 * space: O(n)
 * */

class Solution:
        def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
            if not head: return head

                    old_to_new = dict()

            cur = head

            while cur:
                node = Node(cur.val)
                old_to_new[cur] = node
                cur = cur.next

            cur = head

            while cur:
                if cur.next:
                    old_to_new[cur].next = old_to_new[cur.next]

                if cur.random:
                    old_to_new[cur].random = old_to_new[cur.random]

                cur = cur.next

            return old_to_new[head]


/*
 * solution 2: recursion + hash table
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) {
            return head;
        }

        unordered_map<Node*, Node*> old2new;
        return helper(head, old2new);
    }

    Node* helper(Node* node, unordered_map<Node*, Node*> &old2new) {
        if (node == NULL) {
            return node;
        }

        auto it = old2new.find(node);
        if (it != old2new.end()) {
            return old2new[node];
        }

        Node* node_new = new Node(node->val);
        old2new[node] = node_new;

        node_new->next= helper(node->next, old2new);
        node_new->random = helper(node->random, old2new);

        return node_new;
    }
};

/*
 * solution 3: iteration + constant space, optimal
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) {
            return head;
        }

        /*
         * step 1: 复制节点及next链接，下面加号的位置表示random指针指向的位置，如1指向2
         * +------+
         * 1->1'->2->2'->3->3'
         * */
        Node* cur = head;
        while (cur) {
            Node* copy = new Node(cur->val);
            //第一轮：让1'指向2，即1'->2；第二轮：让2’指向3，即2'->3；第三轮：3’指向null
            copy->next= cur->next;
            //第一轮：让1指向1‘,即1->1'->2；第二轮：让2指向2'，即2->2'->3；第三轮：3指向3’，即3->3'
            cur->next= copy;
            //第一轮：指针移动到下个旧节点去创建新节点，即2；第二轮：走到3；第三轮：走到null
            cur = cur->next->next;
        }

        /*
         * step 2: 复制random链接
         * +------+，旧节点的random链接
         * 1->1'->2->2'->3->3'
         *    +------+，新节点的random链接
         * */
        cur = head;
        while (cur) {
            if (cur->random != NULL) {
                /* cur->next->random就是指1‘的random指针。
                   cur->random就是2，cur->random->next就是2’
                   所以下面的赋值就相当于把1'指向2‘链接上了。
                 */
                cur->next->random = cur->random->next;
            }
            // 从1移到2继续考虑
            cur = cur->next->next;
        }

        /*
         * step 3: 分离两个链表
         * +--+
         * 1->2->3
         * +---+
         * 1'->2'->3'
         * */
        cur = head;
        Node* head_new = cur->next;
        Node* cur_new = head_new;
        while (cur != NULL) {
            cur->next = cur->next->next; //链接1->2->3
            if (cur_new->next != NULL) {
                cur_new->next = cur_new->next->next;//链接1'->2'->3'
            }

            cur = cur->next;
            cur_new = cur_new->next;
        }

        return head_new;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
