//Design a HashMap without using any built-in hash table libraries. 
//
// Implement the MyHashMap class: 
//
// 
// MyHashMap() initializes the object with an empty map. 
// void put(int key, int value) inserts a (key, value) pair into the HashMap. If
// the key already exists in the map, update the corresponding value. 
// int get(int key) returns the value to which the specified key is mapped, or -
//1 if this map contains no mapping for the key. 
// void remove(key) removes the key and its corresponding value if the map conta
//ins the mapping for the key. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
//[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
//Output
//[null, null, null, 1, -1, null, 1, null, -1]
//
//Explanation
//MyHashMap myHashMap = new MyHashMap();
//myHashMap.put(1, 1); // The map is now [[1,1]]
//myHashMap.put(2, 2); // The map is now [[1,1], [2,2]]
//myHashMap.get(1);    // return 1, The map is now [[1,1], [2,2]]
//myHashMap.get(3);    // return -1 (i.e., not found), The map is now [[1,1], [2
//,2]]
//myHashMap.put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existi
//ng value)
//myHashMap.get(2);    // return 1, The map is now [[1,1], [2,1]]
//myHashMap.remove(2); // remove the mapping for 2, The map is now [[1,1]]
//myHashMap.get(2);    // return -1 (i.e., not found), The map is now [[1,1]]
// 
//
// 
// Constraints: 
//
// 
// 0 <= key, value <= 106 
// At most 104 calls will be made to put, get, and remove. 
// 
// Related Topics Array Hash Table Linked List Design Hash Function 
// 👍 3243 👎 315


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: vector to hash table
 * time: O(1)
 * space: O(n)
 * */
class MyHashMap {
public:
    vector<int> key_val;
    MyHashMap() {
        key_val.resize(10e6+1, -1)
    }

    void put(int key, int value) {
        key_val[key] = value;
    }

    int get(int key) {
        return key_val[key];
    }

    void remove(int key) {
        key_val[key] = -1;
    }
};


class MyHashMap:
    def __init__(self):
        self.data = [-1] * 1000001
    def put(self, key: int, val: int) -> None:
        self.data[key] = val
    def get(self, key: int) -> int:
        return self.data[key]
    def remove(self, key: int) -> None:
        self.data[key] = -1

/*
 * solution 2: vector to hash table, better than solution 1
 * time: O(1)
 * space: O(n)
 * */
class MyHashMap {
public:
    MyHashMap() {
        data.resize(1001, vector<int>());
    }
    void put(int key, int value) {
        int hashKey = key % 1000;
        if (data[hashKey].empty()) {
            data[hashKey].resize(1001, -1);
        }
        data[hashKey][key / 1000] = value;
    }
    int get(int key) {
        int hashKey = key % 1000;
        if (!data[hashKey].empty()) {
            return data[hashKey][key / 1000];
        }
        return -1;
    }
    void remove(int key) {
        int hashKey = key % 1000;
        if (!data[hashKey].empty()) {
            data[hashKey][key / 1000] = -1;
        }
    }

private:
    vector<vector<int>> data;
};

/*
 * solution 3: vector to hash table, better than solution 1,2
 * time: average O(1)
 * space: O(1)
 * */
struct Node {
    int key;
    int value;
    Node* next;
    Node(): key(-1), value(-1), next(nullptr) {}
    Node(int key_, int val_): key(key_), value(val_), next(nullptr) {}
};

class MyHashMap {
public:
    const int LEN = 1000;
    vector<Node*> arr;
    MyHashMap() {
        arr.resize(LEN, new Node());
    }

    //创建连接链表节点
    void put(int key, int value) {
        int hash = key % LEN;
        Node* head = arr[hash];
        Node* prev;
        /*
        求模找到hash位置，遍历链表找到对应key的位置
        */
        while (head)
        {
            // 如果找到就直接更新value后返回
            if (head->key == key)
            {
                head->value = value;
                return;
            }
            // 如果没找到的话，最后是要创建新节点的，但是新节点的上一个节点需要指定是哪个
            // 这样才可以实现链表连接
            prev = head;
            head = head->next;
        }
        //没找到，建立节点并进行连接
        Node* node = new Node(key, value);
        prev->next = node;
    }
    // 查找链表节点
    int get(int key) {
        int hash = key % LEN;
        Node* head = arr[hash];
        while (head)
        {
            if (head->key == key) return head->value;
            head = head->next;
        }
        return -1;
    }
    // 删除链表节点
    void remove(int key) {
        int hash = key % LEN;
        Node* head = arr[hash];
        while (head) {
            if (head->key == key)
            {
                head->value = -1;
            }
            head = head->next;
        }
    }
};

class Node:
    def __init__(self, key, val):
        self.key = key
        self.val = val
        self.next = None

class MyHashMap:

    def __init__(self):
        self.LEN = 1000
        self.arr = [Node(-1, -1)] * self.LEN

    def put(self, key: int, value: int) -> None:
        hash = key % self.LEN
        head = self.arr[hash]
        prev = None
        while head:
            if head.key == key:
                head.val = value
                return
            prev = head
            head = head.next
        node = Node(key, value);
        prev.next = node

    def get(self, key: int) -> int:
        hash = key % self.LEN
        head = self.arr[hash]
        while head:
            if head.key == key: return head.val
            head = head.next
        return -1

    def remove(self, key: int) -> None:
        hash = key % self.LEN
        head = self.arr[hash]
        while head:
            if head.key == key:
                head.val = -1
            head = head.next

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
//leetcode submit region end(Prohibit modification and deletion)
