//Implement the RandomizedCollection class: 
//
// 
// RandomizedCollection() Initializes the RandomizedCollection object. 
// bool insert(int val) Inserts an item val into the multiset if not present. Re
//turns true if the item was not present, false otherwise. 
// bool remove(int val) Removes an item val from the multiset if present. Return
//s true if the item was present, false otherwise. Note that if val has multiple o
//ccurrences in the multiset, we only remove one of them. 
// int getRandom() Returns a random element from the current multiset of element
//s (it's guaranteed that at least one element exists when this method is called).
// The probability of each element being returned is linearly related to the numbe
//r of same values the multiset contains. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", 
//"getRandom"]
//[[], [1], [1], [2], [], [1], []]
//Output
//[null, true, false, true, 2, true, 1]
//
//Explanation
//RandomizedCollection randomizedCollection = new RandomizedCollection();
//randomizedCollection.insert(1);   // return True. Inserts 1 to the collection.
// Returns true as the collection did not contain 1.
//randomizedCollection.insert(1);   // return False. Inserts another 1 to the co
//llection. Returns false as the collection contained 1. Collection now contains [
//1,1].
//randomizedCollection.insert(2);   // return True. Inserts 2 to the collection,
// returns true. Collection now contains [1,1,2].
//randomizedCollection.getRandom(); // getRandom should return 1 with the probab
//ility 2/3, and returns 2 with the probability 1/3.
//randomizedCollection.remove(1);   // return True. Removes 1 from the collectio
//n, returns true. Collection now contains [1,2].
//randomizedCollection.getRandom(); // getRandom should return 1 and 2 both equa
//lly likely.
// 
//
// 
// Constraints: 
//
// 
// -231 <= val <= 231 - 1 
// At most 105 calls will be made to insert, remove, and getRandom. 
// There will be at least one element in the data structure when getRandom is ca
//lled. 
// 
//
// 
//Follow up: Could you implement the functions of the class with each function w
//orks in average O(1) time? Related Topics Array Hash Table Design 
// 👍 1127 👎 90


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: vector + hash table
 * time: O(1)
 * space: O(n)
 * */
class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        // 因为还没给num插入新元素，所以这里用nums.size()。
        val_index[val].push_back(nums.size());
        // nums存的是pair:当前元素值，以及对应的索引
        nums.push_back({val, val_index[val].size() - 1});
        return val_index[val].size() == 1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (!val_index.count(val))
            return false;

        // 获得元素数组的最后一个元素的pair
        auto last = nums.back();
        // 把最后一个元素移动到被删除元素的位置。last.first表示最后一个元素，last.second表示最后一个元素索引数组的末端
        // 目的就是更新这个末端索引值，即当前被删除元素的索引末端位置。
        val_index[last.first][last.second] = val_index[val].back();
        // 更新最后一个元素在元素数组的位置
        nums[val_index[val].back()] = last;
        // 弹出被删除元素对应索引数组的末端
        val_index[val].pop_back();
        // 删除掉最后一个元素，因为已经被移动到被删除元素的位置，长度需要减一。
        nums.pop_back();

        // 如果删除后索引数组为空，表示没有元素了，直接删除key
        if (val_index[val].empty())
            val_index.erase(val);

        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return nums[rand() % nums.size()].first;
    }

private:
    vector<pair<int,int>> nums;
    unordered_map<int, vector<int>> val_index;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
//leetcode submit region end(Prohibit modification and deletion)
