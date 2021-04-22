//Create a timebased key-value store class TimeMap, that supports two operations
//. 
//
// 1. set(string key, string value, int timestamp) 
//
// 
// Stores the key and value, along with the given timestamp. 
// 
//
// 2. get(string key, int timestamp) 
//
// 
// Returns a value such that set(key, value, timestamp_prev) was called previous
//ly, with timestamp_prev <= timestamp. 
// If there are multiple such values, it returns the one with the largest timest
//amp_prev. 
// If there are no values, it returns the empty string (""). 
// 
//
// 
//
// 
// Example 1: 
//
// 
//Input: inputs = ["TimeMap","set","get","get","set","get","get"], inputs = [[],
//["foo","bar",1],["foo",1],["foo",3],["foo","bar2",4],["foo",4],["foo",5]]
//Output: [null,null,"bar","bar",null,"bar2","bar2"]
//Explanation:   
//TimeMap kv;   
//kv.set("foo", "bar", 1); // store the key "foo" and value "bar" along with tim
//estamp = 1   
//kv.get("foo", 1);  // output "bar"   
//kv.get("foo", 3); // output "bar" since there is no value corresponding to foo
// at timestamp 3 and timestamp 2, then the only value is at timestamp 1 ie "bar" 
//  
//kv.set("foo", "bar2", 4);   
//kv.get("foo", 4); // output "bar2"   
//kv.get("foo", 5); //output "bar2"   
//
// 
//
// 
// Example 2: 
//
// 
//Input: inputs = ["TimeMap","set","set","get","get","get","get","get"], inputs 
//= [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["
//love",20],["love",25]]
//Output: [null,null,null,"","high","high","low","low"]
// 
// 
// 
//
// 
//
// Note: 
//
// 
// All key/value strings are lowercase. 
// All key/value strings have length in the range [1, 100] 
// The timestamps for all TimeMap.set operations are strictly increasing. 
// 1 <= timestamp <= 10^7 
// TimeMap.set and TimeMap.get functions will be called a total of 120000 times 
//(combined) per test case. 
// 
// Related Topics Hash Table Binary Search 
// 👍 1196 👎 143


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table + binary search
 * time: O(logn)
 * space: O(n)
 * */
class TimeMap {
private:
    unordered_map<string, unordered_map<int, string>> Map;// (key, timestamp-value)
    unordered_map<string, vector<int>> key2times;

public:
    /** Initialize your data structure here. */
    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        key2times[key].push_back(timestamp);
        Map[key][timestamp] = value;
    }

    string get(string key, int timestamp) {
        // get the largest timestamp
        int ts = binarySearch(key2times[key], timestamp);
        string value = ts == -1 ? "" : Map[key][ts];
        return value;
    }

    int binarySearch(vector<int> &nums, int target) {
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] > target)
                end = mid;
            else
                start = mid;
        }

        if (nums[end] <= target)
            return nums[end];

        if (nums[start] <= target)
            return nums[start];

        return -1;
    }
};


/*
 * solution 2: hash table + binary search (STL)
 * time: O(logn)
 * space: O(n)
 * */
class TimeMap {
private:
    unordered_map<string, map<int, string>> Map;// (key, timestamp-value)

public:
    /** Initialize your data structure here. */
    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        Map[key].insert({timestamp, value});
    }

    string get(string key, int timestamp) {
        auto iter = Map[key].upper_bound(timestamp);
        return iter == Map[key].begin() ? "" : prev(iter)->second;
    }


};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
//leetcode submit region end(Prohibit modification and deletion)
