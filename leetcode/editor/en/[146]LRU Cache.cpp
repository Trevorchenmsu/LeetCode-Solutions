//Design a data structure that follows the constraints of a Least Recently Used 
//(LRU) cache. 
//
// Implement the LRUCache class: 
//
// 
// LRUCache(int capacity) Initialize the LRU cache with positive size capacity. 
//
// int get(int key) Return the value of the key if the key exists, otherwise ret
//urn -1. 
// void put(int key, int value) Update the value of the key if the key exists. O
//therwise, add the key-value pair to the cache. If the number of keys exceeds the
// capacity from this operation, evict the least recently used key. 
// 
//
// Follow up: 
//Could you do get and put in O(1) time complexity? 
//
// 
// Example 1: 
//
// 
//Input
//["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
//[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
//Output
//[null, null, null, 1, null, -1, null, -1, 3, 4]
//
//Explanation
//LRUCache lRUCache = new LRUCache(2);
//lRUCache.put(1, 1); // cache is {1=1}
//lRUCache.put(2, 2); // cache is {1=1, 2=2}
//lRUCache.get(1);    // return 1
//lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
//lRUCache.get(2);    // returns -1 (not found)
//lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
//lRUCache.get(1);    // return -1 (not found)
//lRUCache.get(3);    // return 3
//lRUCache.get(4);    // return 4
// 
//
// 
// Constraints: 
//
// 
// 1 <= capacity <= 3000 
// 0 <= key <= 3000 
// 0 <= value <= 104 
// At most 3 * 104 calls will be made to get and put. 
// 
// Related Topics Design 
// 👍 8292 👎 341


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: single linked list + hash table
 * time: O(1)
 * space: O(n)
 * */
class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        auto it = key2val.find(key);
        if (it == key2val.end()) {
            return -1;
        }

        auto iter = key2iter[key];
        keyList.erase(iter);
        keyList.push_back(key);
        key2iter[key] = --keyList.end();

        return key2val[key];
    }

    void put(int key, int value) {
        if (get(key) != -1) {
            key2val[key] = value;
            return;
        }

        if (keyList.size() == cap) {
            int key_del = *keyList.begin();
            key2val.erase(key_del);
            key2iter.erase(key_del);
            keyList.erase(keyList.begin());
        }


        key2val[key] = value;
        keyList.push_back(key);
        key2iter[key] = --keyList.end();
    }

private:
    int cap;
    unordered_map<int, int> key2val;
    list<int> keyList;
    unordered_map<int, list<int>::iterator> key2iter;

};


/*
 * solution 1: single linked list + hash table，另一种写法
 * time: O(1)
 * space: O(n)
 * */

class LRUCache {
public:
    int cap_;
    unordered_map<int, int> key_to_val;
    unordered_map<int, list<int>::iterator> keys_iter;
    list<int> keys_list;

    LRUCache(int capacity) {
        cap_ = capacity;
    }

    int get(int key) {
        auto it = key_to_val.find(key);
        if (it == key_to_val.end()) return -1;

        // update the position
        keys_list.erase(keys_iter[key]);
        keys_list.push_back(key);
        auto iter = --keys_list.end();
        keys_iter[key] = iter;

        return key_to_val[key];
    }

    void put(int key, int value) {
        if (get(key) != -1) {
            key_to_val[key] = value;
        }
        else {
            if (cap_ == 0) {
                int key_del = *keys_list.begin();
                keys_list.erase(keys_list.begin());
                key_to_val.erase(key_del);
                keys_iter.erase(key_del);
                ++cap_;
            }

            keys_list.push_back(key);
            key_to_val[key] = value;
            keys_iter[key] = --keys_list.end();

            --cap_;
        }
    }
};




/*
 * solution 2: double linked list + hash table
 * time: O(1)
 * space: O(n)
 * */
class LRUCache {
public:
    struct Node {
        int val, key;
        Node* prev;
        Node* next;
        Node(int _key, int _val): key(_key), val(_val), prev(NULL), next(NULL) {}
    };


    LRUCache(int capacity) {
        _capacity = capacity;
        head = NULL;
        tail = NULL;
    }

    int get(int key) { // O(1)
        Node* node = key2nodes[key];
        if (node == NULL) return -1;
        if (node != tail)
            move2end(node);

        return node->val;
    }

    void put(int key, int value) { // O(1)
        Node* node = key2nodes[key];
        if (node != NULL) {
            // key exists
            node->val = value;
            if (node != tail)
                move2end(node);
        }
        else {
            Node* new_node = new Node(key, value);

            // initial case
            if (head == NULL && tail == NULL) {
                head = new_node;
                tail = new_node;
            }
            else {

                if (_capacity == 0) {
                    int delete_key = head->key;
                    key2nodes.erase(delete_key);
                    head = head->next;
                    _capacity++;
                }

                tail->next = new_node;
                new_node->prev = tail;
                new_node->next = NULL;
                tail = new_node;
            }

            key2nodes[key] = new_node;
            _capacity--;
        }
    }

    void move2end(Node* node) { // O(1)
        if (node == head) {
            head = head->next;
        }
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        tail->next = node;
        node->prev = tail;
        node->next = NULL;
        tail = node;
    }

private:
    int _capacity;
    Node* head;
    Node* tail;
    unordered_map<int, Node*> key2nodes;

};


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */





/*
 * python 解法
 * solution: 双向链表+哈希表
 * time: O(1)
 * space: O(n)
 * */


class Node:
        def __init__(self, k, v):
self.key = k
self.val = v
self.prev = None
self.next = None

class LRUCache:

        def __init__(self, capacity: int):
self.cap = capacity
self.dict = dict() # key-nodes dictionary
self.head = Node(0, 0)
self.tail = Node(0, 0)
self.head.next = self.tail
self.tail.prev = self.head


def get(self, key: int) -> int:
if key not in self.dict: return -1

node = self.dict[key]
self.remove_from_dict(node)
self.add_to_dict(node)

return node.val



        def put(self, key: int, value: int) -> None:
if key in self.dict: # 只要存在就删除，要替换的话后面重新新建node替换，反正要插到末端
        self.remove_from_dict(self.dict[key])

node = Node(key, value)
self.add_to_dict(node)
self.dict[key] = node
if len(self.dict) > self.cap:
node = self.head.next # 因为head是dummy node，第二个才是真正的head
        self.remove_from_dict(node)
del self.dict[node.key]


def remove_from_dict(self, node: Node):
prev_node = node.prev
next_node = node.next
prev_node.next = next_node
next_node.prev = prev_node


def add_to_dict(self, node: Node):
prev_node = self.tail.prev # 因为tail是dummy node
prev_node.next = node
node.prev = prev_node
self.tail.prev = node
node.next = self.tail



# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
//leetcode submit region end(Prohibit modification and deletion)
