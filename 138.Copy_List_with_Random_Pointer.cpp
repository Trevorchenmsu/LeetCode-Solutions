/*
solution 1: hash table + iterative 
time: O(n)
space: O(n)
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr)
            return head;
        
        // use hash table to store the original nodes(key) and new nodes(value)
        unordered_map<Node*, Node*> listMap;
        Node* cur = head;
        while (cur != nullptr) {
            Node* newNode = new Node(cur->val);
            listMap[cur] = newNode;
            cur = cur->next;
        }
        
        // build the connections for next and random pointers
        cur = head;
        while (cur != nullptr) {
            listMap[cur]->next = listMap[cur->next];
            listMap[cur]->random = listMap[cur->random];
            cur = cur->next;
        }
        
        return listMap[head];
    }
};

/*
solution 2: in-place + iterative 
time: O(n)
space: O(1)
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr)
            return head;
        
        // step1: copy node
        // +------+, this represents random pointer
        // 1->1'->2->2'->3->3'
        Node* cur = head;
        while (cur != nullptr) {
            Node* copy = new Node(cur->val);
            copy->next = cur->next;
            cur->next = copy;
            cur = cur->next->next;
        }

        // step2: copy random link
        // +------+
        // 1->1'->2->2'->3->3'
        //    +------+
        cur = head;
        while (cur != nullptr) {
            if (cur->random != nullptr)
                cur->next->random = cur->random->next;
            cur = cur->next->next;
        }

        // step3: split two lists
        // +--+    
        // 1->2->3
        // +---+    
        // 1'->2'->3'
        cur = head;
        Node* newHead = cur->next;
        Node* newCur = newHead;
        while (cur != nullptr) {
            cur->next = cur->next->next;
            if (newCur->next != nullptr)
                newCur->next = newCur->next->next; 
            cur = cur->next;
            newCur = newCur->next;
        }
        
        return newHead;
    }
};       