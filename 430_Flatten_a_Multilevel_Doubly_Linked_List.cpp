/*
solution 1: iteration
time: O(n)
space: O(1)
*/

class Solution {
public:
    Node* flatten(Node* head) {
        if (!head) return head;
        Node* cur = head;
        
        while (cur) {
            Node* temp = cur->next;
            if (cur->child) {
                // 1 child exists，convert child connection to double connection
                Node* _child = cur->child;
                cur->next = _child;
                _child->prev = cur;
                cur->child = NULL;
                
                // 2. get tail of child linked list. it is used to connect the broken part
                Node* child_tail = _child;
                while (child_tail && child_tail->next) {
                    child_tail = child_tail->next;
                }
                
                // 3. connect the broken part
                child_tail->next = temp;
                if (temp) temp->prev = child_tail;
                
            }
            cur = cur->next;
        }
        
        return head;
    }
};


/*
solution 2: recursion
time: O(n)
space: O(n)
*/


class Solution {
public:
    Node* flatten(Node* head) {
        tail = head;
        dfs(head);
        return head;
    }

private:
    Node* tail;
    void dfs(Node* head) {
        if (!head) return;
        
        Node* temp = head->next;
        if (head->child) {
            head->child->prev = head;
            head->next = head->child;
            tail = head->child;
            dfs(head->child);
            head->child = NULL;
        }
        
        tail->next = temp;
        if (temp) {
            temp->prev = tail;
            tail = temp;
        }
        dfs(temp);
    }
};
