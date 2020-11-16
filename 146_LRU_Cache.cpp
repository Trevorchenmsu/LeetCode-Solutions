/*
solution: hashmap + double linked list
time: O(1)
space: O(n), n is the capacity.
*/

struct Node 
{
	Node* pre;
	Node* next;
	int key, val;
	Node(int _key, int _val): key(_key), val(_key), pre(NULL), next(NULL) {}
};

class LRUCache {
public:
    LRUCache(int capacity) {
        _capacity = capacity;
        head = NULL;
        tail = NULL;
    }

    void moveTotail(Node* node) {
    	if (node == head) {
    		head = head->next;
    	} else {
    		node->pre->next = node->next;
    		node->next->pre = node->pre;
    	}
    	tail->next = node;
    	node->pre = tail;
    	node->next = NULL;
    	tail = node;
    }
    
    int get(int key) {
        Node* node = map[key];
        if (!node) return -1;
        if (node != tail) moveTotail(node);
        return node->val;
    }

    /*
        There are three conditions in put function:
        (1) key doesn't exist and the capacity is not full.
        (2) key doesn't exist but the capacity is full;
        (3) key already exists;
    */
    
    void put(int key, int value) {
        Node* node = map[key];
        if (!node) {
        	// build a new node since key does not exist
        	Node* newNode = new Node(key, value);
        	// condition 2
        	if (_capacity == 0) {
        		// delete LRU element
        		Node* temp = head;
        		head = head->next;
        		map.erase(temp->key);
        		++_capacity;
        	}
        	// insert a new node to the tail. It works for both condition 2 and condition 3
        	if (!head && !tail) {
        		// the first put() operation
        		head = newNode;
        	} else {
        		tail->next = newNode;
        		newNode->pre = tail;
        		newNode->next = NULL;
        	}
        	tail = newNode;
        	--_capacity;
        	map[key] = newNode;
        } else {
        	// condition 3
        	node->val = value;
        	if (node != tail) {
        		moveTotail(node);
        	}
        }
    }

private:
	int _capacity;
	Node* head;
	Node* tail;
	unordered_map<int, Node*> map;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */