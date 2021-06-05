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
        if (key2val.find(key) == key2val.end())
            return -1;

        //在链表中查找key的位置。因为是单向链表，所以iter的prev要连接iter的next。这样就相当于删除了这个节点
        auto iter = key2iter[key];
        List.erase(iter);

        // 把key插到链表末端
        List.push_back(key);
        key2iter[key] = --List.end();

        return key2val[key];
    }

    void put(int key, int value) {
        //因为这里先采用了get函数，所以这个存在的节点已经被移动到了链表的末端，不用再移动操作
        if (get(key) != -1) {
            key2val[key] = value;
            return;
        }

        // 如果链表满了，先删除链表头
        if (List.size() == cap) {
            int key_delete = *List.begin();
            key2val.erase(key_delete);
            key2iter.erase(key_delete);
            List.erase(List.begin());
        }

        //链表尾插入新节点，同时更新两个哈希表
        key2val[key] = value;
        List.push_back(key);
        key2iter[key] = --List.end();
    }

private:
    unordered_map<int, int> key2val; //记录 key -> val
    list<int> List; //把所有key按照recently visited的先后顺序排列
    unordered_map<int, list<int>::iterator> key2iter; //记录key对应的在List中的迭代器位置
    int cap;
};


/*
 * solution 2: double linked list + hash table
 * time: O(1)
 * space: O(n)
 * */
//class LRUCache {
//public:
//    struct Node {
//        int val, key;
//        Node* prev;
//        Node* next;
//        Node(int _key, int _val): key(_key), val(_val), prev(NULL), next(NULL) {}
//    };
//
//
//    LRUCache(int capacity) {
//        _capacity = capacity;
//        head = NULL;
//        tail = NULL;
//    }
//
//    int get(int key) { // O(1)
//        Node* node = key2nodes[key];
//        if (node == NULL) return -1;
//        if (node != tail)
//            move2end(node);
//
//        return node->val;
//    }
//
//    void put(int key, int value) { // O(1)
//        Node* node = key2nodes[key];
//        if (node != NULL) {
//            // key exists
//            node->val = value;
//            if (node != tail)
//                move2end(node);
//        }
//        else {
//            Node* new_node = new Node(key, value);
//
//            // initial case
//            if (head == NULL && tail == NULL) {
//                head = new_node;
//                tail = new_node;
//            }
//            else {
//
//                if (_capacity == 0) {
//                    int delete_key = head->key;
//                    key2nodes.erase(delete_key);
//                    head = head->next;
//                    _capacity++;
//                }
//
//                tail->next = new_node;
//                new_node->prev = tail;
//                new_node->next = NULL;
//                tail = new_node;
//            }
//
//            key2nodes[key] = new_node;
//            _capacity--;
//        }
//    }
//
//    void move2end(Node* node) { // O(1)
//        if (node == head) {
//            head = head->next;
//        }
//        else {
//            node->prev->next = node->next;
//            node->next->prev = node->prev;
//        }
//
//        tail->next = node;
//        node->prev = tail;
//        node->next = NULL;
//        tail = node;
//    }
//
//private:
//    int _capacity;
//    Node* head;
//    Node* tail;
//    unordered_map<int, Node*> key2nodes;
//
//};


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
//leetcode submit region end(Prohibit modification and deletion)
