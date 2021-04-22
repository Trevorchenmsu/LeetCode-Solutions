//Design a data structure to store the strings' count with the ability to return
// the strings with minimum and maximum counts. 
//
// Implement the AllOne class: 
//
// 
// AllOne() Initializes the object of the data structure. 
// inc(String key) Increments the count of the string key by 1. If key does not 
//exist in the data structure, insert it with count 1. 
// dec(String key) Decrements the count of the string key by 1. If the count of 
//key is 0 after the decrement, remove it from the data structure. It is guarantee
//d that key exists in the data structure before the decrement. 
// getMaxKey() Returns one of the keys with the maximal count. If no element exi
//sts, return an empty string "". 
// getMinKey() Returns one of the keys with the minimum count. If no element exi
//sts, return an empty string "". 
// 
//
// 
// Example 1: 
//
// 
//Input
//["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMin
//Key"]
//[[], ["hello"], ["hello"], [], [], ["leet"], [], []]
//Output
//[null, null, null, "hello", "hello", null, "hello", "leet"]
//
//Explanation
//AllOne allOne = new AllOne();
//allOne.inc("hello");
//allOne.inc("hello");
//allOne.getMaxKey(); // return "hello"
//allOne.getMinKey(); // return "hello"
//allOne.inc("leet");
//allOne.getMaxKey(); // return "hello"
//allOne.getMinKey(); // return "leet"
// 
//
// 
// Constraints: 
//
// 
// 1 <= key.length <= 10 
// key consists of lowercase English letters. 
// It is guaranteed that for each call to dec, key is existing in the data struc
//ture. 
// At most 3 * 104 calls will be made to inc, dec, getMaxKey, and getMinKey. 
// 
//
// 
// Follow up: Could you apply all the operations in O(1) time complexity? 
// Related Topics Design 
// 👍 781 👎 94


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: list + hash table + hash set
 * time: O(1)
 * space: O(n)
 * */
class AllOne {
private:
    list<int> List; // store all the values
    unordered_map<int, list<int>::iterator> val2iter; // get the position of value in the list based on iterator
    unordered_map<string, int> key2val; // key-value pair
    unordered_map<int, unordered_set<string>> val2set; // get all the keys under that value


public:
    /** Initialize your data structure here. */
    AllOne() {
        // build a dummy node
        List.push_back(0);
        val2iter[0] = List.begin();
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        int val = key2val[key];

        key2val[key] = val + 1; // add the count
        val2set[val + 1].insert(key); // for new value, add its key
        if (val > 0) val2set[val].erase(key); // when val==0, we don't have key in val2set

        // when val + 1 is not on the list, we need to add it to the position in front of val
        if (val2set[val + 1].size() == 1) {
            List.insert(next(val2iter[val]), val + 1); // insert val + 1 to the list
            val2iter[val + 1] = next(val2iter[val]); // it is single linked list
        }

        // when we move the key in val to val + 1, the sets corresponding to val might be empty
        if (val > 0 && val2set[val].size() == 0) // val > 0 is to make sure it is not the dummy node
            List.erase(val2iter[val]);

    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        int val = key2val[key];

        if (val == 0) return; // dummy node

        key2val[key] = val - 1;
        if (val - 1 > 0) val2set[val - 1].insert(key);
        val2set[val].erase(key);

        if (val - 1 > 0 && val2set[val - 1].size() == 1) {
            List.insert(val2iter[val], val - 1); // default insert into the current position
            val2iter[val - 1] = prev(val2iter[val]);
        }

        if (val2set[val].size() == 0)
            List.erase(val2iter[val]);
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        // only the dummy node
        if (List.size() == 1)
            return "";

        return *(val2set[List.back()].begin());
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        // only the dummy node
        if (List.size() == 1)
            return "";

        return *(val2set[*(++List.begin())].begin());
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
//leetcode submit region end(Prohibit modification and deletion)
