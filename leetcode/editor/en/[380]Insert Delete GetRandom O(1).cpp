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
        auto it = val2idx.find(val);
        if (it != val2idx.end()) {
            return false;
        }

        val2idx[val] = nums.size();
        nums.push_back(val);

        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto it = val2idx.find(val);
        if (it == val2idx.end()) {
            return false;
        }

        int idx = val2idx[val];
        int last = nums.back();
        nums[idx] = last;
        val2idx[last] = idx;
        val2idx.erase(val);
        nums.pop_back();

        return true;
    }

    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }

private:
    vector<int> nums;
    unordered_map<int, int> val2idx;
};



class RandomizedSet:

    def __init__(self):
        self.nums = []
        self.val2idx = {}

    def insert(self, val: int) -> bool:
        if val in self.val2idx.keys(): return False

        self.val2idx[val] = len(self.nums)
        self.nums.append(val)
        return True

    def remove(self, val: int) -> bool:
        if val not in self.val2idx.keys():
            return False

        idx = self.val2idx[val]
        last = self.nums[-1]
        self.nums[idx] = last
        self.val2idx[last] = idx
        del self.val2idx[val]
        self.nums.pop()
        return True


    def getRandom(self) -> int:
        return choice(self.nums)
/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
//leetcode submit region end(Prohibit modification and deletion)
