/*
solution: data structure design
time: O(1)
space: O(n)
*/

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (num_index.find(val) != num_index.end())
            return false;
        nums.push_back(val);
        num_index[val] = nums.size() - 1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (num_index.find(val) == num_index.end())
            return false;
        
        // step 1 : move the last element to val position      
        int last_num = nums.back(); // get last number
        int val_idx = num_index[val]; // get val position
        nums[val_idx] = last_num; 
        
        // step 2 : update the index of last time in the hash table
        num_index[last_num] = val_idx; 
        
        // step 3: delete val
        nums.pop_back();
        num_index.erase(val);
        
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
    
private:
    vector<int> nums;
    unordered_map<int, int> num_index;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */