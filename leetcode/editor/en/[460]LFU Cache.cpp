//Design and implement a data structure for a Least Frequently Used (LFU) cache.
// 
//
// Implement the LFUCache class: 
//
// 
// LFUCache(int capacity) Initializes the object with the capacity of the data s
//tructure. 
// int get(int key) Gets the value of the key if the key exists in the cache. Ot
//herwise, returns -1. 
// void put(int key, int value) Update the value of the key if present, or inser
//ts the key if not already present. When the cache reaches its capacity, it shoul
//d invalidate and remove the least frequently used key before inserting a new ite
//m. For this problem, when there is a tie (i.e., two or more keys with the same f
//requency), the least recently used key would be invalidated. 
// 
//
// To determine the least frequently used key, a use counter is maintained for e
//ach key in the cache. The key with the smallest use counter is the least frequen
//tly used key. 
//
// When a key is first inserted into the cache, its use counter is set to 1 (due
// to the put operation). The use counter for a key in the cache is incremented ei
//ther a get or put operation is called on it. 
//
// 
// Example 1: 
//
// 
//Input
//["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "g
//et"]
//[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
//Output
//[null, null, null, 1, null, -1, 3, null, -1, 3, 4]
//
//Explanation
//// cnt(x) = the use counter for key x
//// cache=[] will show the last used order for tiebreakers (leftmost element is
//  most recent)
//LFUCache lfu = new LFUCache(2);
//lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
//lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
//lfu.get(1);      // return 1
//                 // cache=[1,2], cnt(2)=1, cnt(1)=2
//lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalid
//ate 2.
//                 // cache=[3,1], cnt(3)=1, cnt(1)=2
//lfu.get(2);      // return -1 (not found)
//lfu.get(3);      // return 3
//                 // cache=[3,1], cnt(3)=2, cnt(1)=2
//lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1
//.
//                 // cache=[4,3], cnt(4)=1, cnt(3)=2
//lfu.get(1);      // return -1 (not found)
//lfu.get(3);      // return 3
//                 // cache=[3,4], cnt(4)=1, cnt(3)=3
//lfu.get(4);      // return 4
//                 // cache=[3,4], cnt(4)=2, cnt(3)=3
// 
//
// 
// Constraints: 
//
// 
// 0 <= capacity, key, value <= 104 
// At most 105 calls will be made to get and put. 
// 
//
// 
//Follow up: Could you do both operations in O(1) time complexity? Related Topic
//s Design 
// 👍 2014 👎 152


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: design, hash table, doubly linked list.
 * */
class LFUCache {
    // 每个freq都有它的keys列表，所以key_iter的迭代器也是对应这里的列表，不是所有的key整合成一个大list
    unordered_map<int, list<int>> freq_keys;
    unordered_map<int, list<int>::iterator> key_iter;
    unordered_map<int, int> key_val, key_freq;
    int cap, min_freq;
public:
    LFUCache(int capacity) {
        cap = capacity;
        min_freq = 0;
    }

    int get(int key) {
        // key not exist
        auto it = key_val.find(key);
        if (it == key_val.end()) return -1;

        // update the frequence and position
        int freq_del = key_freq[key];

        // 这里没有用到key_list，所以key_iter存的不是它的迭代器，那只能是在特定freq下对应的list的迭代器
        freq_keys[freq_del].erase(key_iter[key]); //因为调用后频率递增，该key已经不属于这个freq了
        ++key_freq[key]; // 频率递增
        freq_keys[key_freq[key]].push_back(key); //当前key被挂在递增后的freq下
        key_iter[key] = --freq_keys[key_freq[key]].end();

        // 在freq_keys中，删除的频率可能是最小频率，则需要将最小频率前进一位
        if (freq_keys[min_freq].size() == 0) ++min_freq;

        return key_val[key];
    }

    void put(int key, int value) {
        if (cap == 0) return;

        if (get(key) != -1)
        {
            key_val[key] = value;
            return;
        }

        if (key_val.size() == cap)
        {
            int key_del = freq_keys[min_freq].front();

            key_val.erase(key_del);
            key_freq.erase(key_del);
            key_iter.erase(key_del);
            freq_keys[min_freq].pop_front();
        }

        min_freq = 1; // 因为这里已经保证之前没有这个key，所以它的频率是1
        key_val[key] = value;
        key_freq[key] = min_freq;
        freq_keys[min_freq].push_back(key);
        key_iter[key] = --freq_keys[min_freq].end();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

/*
题目要求跟LRU基本一致，差别就是满足容量时要删除的元素不同，
LFU指的是最小使用频率的元素，如果使用频率相同，再删除LRU
频率要能够自动排序：freq_list?
*/
//leetcode submit region end(Prohibit modification and deletion)
