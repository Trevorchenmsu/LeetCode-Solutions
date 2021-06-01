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
        //插入一个dummy node在list前面，方便后面操作
        cntList.push_back(0);
        cnt2iter[0] = cntList.begin();
    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        // 更新kye2cnt：获得旧的cnt方便下面操作，cnt加1后更新key对应的cnt
        int cnt = key2cnt[key];
        key2cnt[key] = cnt + 1;

        // 更新cnt2keys：新cnt对应的字符串集合中加入key。旧cnt对应的字符串集合中删除key。如果cnt为0，表示第一个插入，不用管。
        cnt2keys[cnt + 1].insert(key);
        if (cnt > 0) cnt2keys[cnt].erase(key);

        /* 如果链表中已经存在cnt+1的话，我们是不需要重复插入这个新cnt到链表中，因为之前已经有其他string操作过。
           如果链表中不存在这个cnt+1的话，我们就需要把这个值插到cnt后面，因为它们刚好相差1，这样可以保证cnt有序递增。
           下面根据size==1来判定是否cnt+1是否已存在。因为上面我们加入key到cnt+1的映射中，所以size至少是1。
        */
        if (cnt2keys[cnt + 1].size() == 1) {
            auto iter = cnt2iter[cnt];
            cntList.insert(next(iter), cnt + 1); //插入cnt+1到链表中，位置为cnt的下一个迭代器
            cnt2iter[cnt + 1] = next(iter); // 更新cnt+1在cnt2iter的迭代器位置。
        }

        /* 当cnt下面的string转移到cnt+1下面去，cnt下面有可能就没有string了，此时这个cnt就需要从list中删除
            下面的cnt>0条件可保证不是第一次添加的情况，因为第一次cnt=0，它下面的string集合size肯定为0
        */
        if (cnt > 0 && cnt2keys[cnt].size() == 0)
            cntList.erase(cnt2iter[cnt]);
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        // 更新kye2cnt：获得旧的cnt方便下面操作，cnt-1后更新key对应的cnt
        int cnt = key2cnt[key];
        key2cnt[key] = cnt - 1;

        // 更新cnt2keys：新cnt对应的字符串集合中加入key。因为是cnt-1，需要保证它大于0，不可以等于0，大于0才有对应的集合
        // 旧cnt对应的字符串集合中删除key，因为cnt可能存在且大于0，直接删除即可。
        if (cnt - 1 > 0)
            cnt2keys[cnt - 1].insert(key);
        cnt2keys[cnt].erase(key);

        // 更新list和cnt2iter，与inc中的同理。但是要注意list的insert方法，表示插入到该迭代器的前一个位置
        if (cnt - 1 > 0 && cnt2keys[cnt - 1].size() == 1) {
            auto iter = cnt2iter[cnt];
            cntList.insert(iter, cnt - 1);
            cnt2iter[cnt - 1] = prev(iter);
        }

        // 当cnt下面的string移到cnt-1后，没有对应字符串了，就得从list中删除
        if (cnt2keys[cnt].size() == 0)
            cntList.erase(cnt2iter[cnt]);
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (cntList.size() == 1)
            return "";

        return *(cnt2keys[cntList.back()].begin());
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (cntList.size() == 1)
            return "";

        return *(cnt2keys[*(++cntList.begin())].begin());
    }

private:
    list<int> cntList; // counts
    unordered_map<string, int> key2cnt; // string-count
    unordered_map<int, unordered_set<string>> cnt2keys; // 具有相同count的所有string
    unordered_map<int, list<int>::iterator> cnt2iter; // count在list中的位置
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
