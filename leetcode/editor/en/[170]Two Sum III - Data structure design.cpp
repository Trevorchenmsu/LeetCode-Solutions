//Design a data structure that accepts a stream of integers and checks if it has
// a pair of integers that sum up to a particular value. 
//
// Implement the TwoSum class: 
//
// 
// TwoSum() Initializes the TwoSum object, with an empty array initially. 
// void add(int number) Adds number to the data structure. 
// boolean find(int value) Returns true if there exists any pair of numbers whos
//e sum is equal to value, otherwise, it returns false. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["TwoSum", "add", "add", "add", "find", "find"]
//[[], [1], [3], [5], [4], [7]]
//Output
//[null, null, null, null, true, false]
//
//Explanation
//TwoSum twoSum = new TwoSum();
//twoSum.add(1);   // [] --> [1]
//twoSum.add(3);   // [1] --> [1,3]
//twoSum.add(5);   // [1,3] --> [1,3,5]
//twoSum.find(4);  // 1 + 3 = 4, return true
//twoSum.find(7);  // No two integers sum up to 7, return false
// 
//
// 
// Constraints: 
//
// 
// -105 <= number <= 105 
// -231 <= value <= 231 - 1 
// At most 5 * 104 calls will be made to add and find. 
// 
// Related Topics Hash Table Design 
// 👍 404 👎 294


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table
 * time: O(n) for find(), O(1) for add()
 * space: O(n)
 * */
class TwoSum {
private:
    unordered_map<int, int> cnt_map;

public:
    /** Initialize your data structure here. */
    TwoSum() {
        
    }
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        cnt_map[number]++;
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        for (auto &[val, cnt] : cnt_map) {
            if ((long) value - (long) val < INT_MIN)
                return false;
            if (cnt_map.count(value - val)) {
                if (value - val != val)
                    return true;
                else {
                    if (cnt == 1)
                        continue;
                    else
                        return true;
                }
            }
        }

        return false;

    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */
//leetcode submit region end(Prohibit modification and deletion)
