//Implement the RandomizedSet class: 
//
// 
// RandomizedSet() Initializes the RandomizedSet object. 
// bool insert(int val) Inserts an item val into the set if not present. Returns
// true if the item was not present, false otherwise. 
// bool remove(int val) Removes an item val from the set if present. Returns tru
//e if the item was present, false otherwise. 
// int getRandom() Returns a random element from the current set of elements (it
//'s guaranteed that at least one element exists when this method is called). Each
// element must have the same probability of being returned. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert
//", "getRandom"]
//[[], [1], [2], [2], [], [1], [2], []]
//Output
//[null, true, false, true, 2, true, false, 2]
//
//Explanation
//RandomizedSet randomizedSet = new RandomizedSet();
//randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was insert
//ed successfully.
//randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
//randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contai
//ns [1,2].
//randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly
//.
//randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now cont
//ains [2].
//randomizedSet.insert(2); // 2 was already in the set, so return false.
//randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom
//() will always return 2.
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
// 👍 3518 👎 207


//leetcode submit region begin(Prohibit modification and deletion)
class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (val_index.count(val))
            return false;
        val_arr.push_back(val);
        val_index[val] = val_arr.size() - 1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (!val_index.count(val))
            return false;

        // get the index of remove element
        int idx = val_index[val];
        // move last element to the new index, the deleted element will be replaced
        int last_element = val_arr.back();
        val_arr[idx] = last_element;
        // since we already replace the deleted element and the size of array reduce 1
        // and the last element has been moved, so the current last element is useless.
        val_arr.pop_back();

        val_index[last_element] = idx;
        val_index.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int idx = rand() % val_arr.size();
        return val_arr[idx];
    }

private:
    vector<int> val_arr;
    unordered_map<int, int> val_index;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
//leetcode submit region end(Prohibit modification and deletion)
