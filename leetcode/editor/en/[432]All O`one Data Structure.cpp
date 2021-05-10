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
public:
    /** Initialize your data structure here. */
    AllOne() {
        // build a dummy node
        List.push_back(0);
        cnt2iter[0] = List.begin();
    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        int cnt = key2cnt[key];
        key2cnt[key] = cnt + 1; // add the count

        cnt2set[cnt + 1].insert(key); // add key to new count
        if (cnt > 0) cnt2set[cnt].erase(key); // delete key from old count; when cnt==0, we don't have key in cnt2set

        // when val + 1 is not on the list, we need to add it to the position in front of val
        if (cnt2set[cnt + 1].size() == 1) {
            List.insert(next(cnt2iter[cnt]), cnt + 1); // insert val + 1 to the list
            cnt2iter[cnt + 1] = next(cnt2iter[cnt]); // it is single linked list
        }

        // when we move the key from count to count + 1, the sets corresponding to count might be empty
        if (cnt > 0 && cnt2set[cnt].size() == 0) // cnt > 0 is to make sure it is not the dummy node
            List.erase(cnt2iter[cnt]);

    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        int cnt = key2cnt[key];

        if (cnt == 0) return; // dummy node

        key2cnt[key] = cnt - 1;
        if (cnt - 1 > 0) cnt2set[cnt - 1].insert(key);
        cnt2set[cnt].erase(key);

        if (cnt - 1 > 0 && cnt2set[cnt - 1].size() == 1) {
            List.insert(cnt2iter[cnt], cnt - 1); // default insert into the current position
            cnt2iter[cnt - 1] = prev(cnt2iter[cnt]);
        }

        if (cnt2set[cnt].size() == 0)
            List.erase(cnt2iter[cnt]);
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        // only the dummy node
        if (List.size() == 1)
            return "";

        return *(cnt2set[List.back()].begin());
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        // only the dummy node
        if (List.size() == 1)
            return "";

        return *(cnt2set[*(++List.begin())].begin());
    }

private:
    list<int> List; // store all the counts
    unordered_map<int, list<int>::iterator> cnt2iter; // get the position of count in the list
    unordered_map<string, int> key2cnt; // key-value pair
    unordered_map<int, unordered_set<string>> cnt2set; // get all the keys under that count

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
