/*
solution: hashmap + double linked list
time: O(1)
space: O(n), n is the capacity.
*/

class LRUCache {
public:
    struct Node {
        Node* pre;
        Node* next;
        int key, val;
        Node(int _key, int _val): key(_key), val(_val), pre(nullptr), next(nullptr) {}
    };
    
    LRUCache(int capacity) {
        _capacity = capacity;
        head = nullptr;
        tail = nullptr;
    }
    
    int get(int key) {
        Node* node = map[key];
        if (node == nullptr) return -1;
        if (node != tail) moveToTail(node);
        return node->val;
    }
    
    /*
        There are three conditions in put function:
        (1) key does not exist and the capacity is not full;
        (2) key does not exist and the capacity is full;
        (3) key exists.
    */
    
    void put(int key, int value) {
        Node* node = map[key];
        
        if (node == nullptr) {
            Node* new_node = new Node(key, value); // key does not exist
            
            // condition 2
            if (_capacity == 0) { // capacity is full, delete LRU (the head of the list) first
                int deleted_key = head->key;
                head = head->next;
                map.erase(deleted_key);
                _capacity++;
            }
            
            // insert a new node to the tail. Condition 2 and condition 3
            if (head == nullptr && tail == nullptr) {
                head = new_node;
                tail = new_node;
            }
            else {
                tail->next = new_node;
                new_node->pre = tail;
                new_node->next = nullptr;
                tail = new_node;
            }
            
            _capacity--;
            map[key] = new_node;
        }
        else {
            // condition 3
            node->val = value;
            if (node != tail) moveToTail(node);
        }
    }

private:
    int _capacity;
    Node* head;
    Node* tail;
    unordered_map<int, Node*> map;
    
    void moveToTail(Node* node) {
        if (node == head) head = head->next;

        else {
            node->pre->next = node->next;
            node->next->pre = node->pre;
        }

        tail->next = node;
        node->pre = tail;
        node->next = nullptr;
        tail = node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */