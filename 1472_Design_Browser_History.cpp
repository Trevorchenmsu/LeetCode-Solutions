/*
solution: double linked list
time: O(n)
space: O(1)
*/
class BrowserHistory {
private:
    struct LinkNode {
        LinkNode *prev, *next;
        string val;
        LinkNode(): prev(NULL), next(NULL) {}
        LinkNode(string _val): val(_val), prev(NULL), next(NULL) {}
    };
    
    LinkNode *head, *tail, *cur = NULL;

public:
    BrowserHistory(string homepage) {
        head = new LinkNode();
        tail = new LinkNode();
        LinkNode *p = new LinkNode(homepage);
        head->next = p;
        p->prev = head;
        p->next = tail;
        tail->prev = p;
        cur = p;
    }
    
    void visit(string url) {
        LinkNode *p = new LinkNode(url);
        head->next = p;
        p->prev = head;
        p->next = cur;
        cur->prev = p;
        cur = p;
    }
    
    string back(int steps) {
        while (steps-- && cur->next != tail)
            cur = cur->next;
        return cur->val;
        
    }
    
    string forward(int steps) {
        while (steps-- && cur->prev != head)
            cur = cur->prev;
        return cur->val;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */