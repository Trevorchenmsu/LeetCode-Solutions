/*
Solution 1: two heaps
time: O(nlogk)
space: O(n) 
*/
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> medians;
        priority_queue<int> lo; // max heap
        priority_queue<int, vector<int>, greater<int>> hi; // min heap
        unordered_map<int, int> hash_table;
        
        // initilaze heaps with first window elements, lo has more elements than hi
        // so lo-hi=1 for odd, lo-hi=0 for even
        int i = 0;
        for (; i < k; i++) {
            lo.push(nums[i]);
        }
        for (int j = 0; j < k / 2; j++) {
            hi.push(lo.top());
            lo.pop();
        }
        
        double median;
        
        while (true) {
            median = k & 1 ? (double)lo.top() : ((double)lo.top() + (double)hi.top()) * 0.5;
            medians.push_back(median);
            
            if (i == nums.size()) break;
            
            int out_num = nums[i - k],
                in_num = nums[i++],
                balance = 0; 
            
            // determine whether the out_num belongs to hi or low, then update balance
            balance += (out_num > lo.top()) ? 1 : -1;
            hash_table[out_num]++; // indicate out_num has been deleted
            
            // window moves
            if (!lo.empty() && in_num <= lo.top()) {
                lo.push(in_num);
                balance++;
            } else {
                hi.push(in_num);
                balance--;
            }
            
            // adjust the balance of two heaps
            if (balance < 0){ // lo need more elements
                lo.push(hi.top());
                hi.pop();
                balance++;
            } 
            if (balance > 0) {
                hi.push(lo.top());
                lo.pop();
                balance--;
            }
            
            // if reach balance, delete the element in hash table
            // we only care about the element in the heap top as it will affect the median resutls
            // if the element has been removed, we need to remove it from the heap top
            while (!lo.empty() && hash_table[lo.top()]){
                hash_table[lo.top()]--;
                lo.pop();
            }
            while (!hi.empty() && hash_table[hi.top()]){
                hash_table[hi.top()]--;
                hi.pop();
            }
        }
        return medians;
    }
};

/*
Solution 2: two heaps
time: O(nlogk)
space: O(k)
*/
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        multiset<int> small, large;
        
        for (int i = 0; i < nums.size(); ++i) {
            // delete left boundary of the window
            if (i >= k) {
                if (small.count(nums[i - k])) 
                    small.erase(small.find(nums[i - k]));
                else if (large.count(nums[i - k])) 
                    large.erase(large.find(nums[i - k]));
            }
            
            // add new element to the window
            if (small.size() <= large.size()) { // insert to small
                if (large.empty() || nums[i] <= *large.begin()) 
                    small.insert(nums[i]);
                else {
                    small.insert(*large.begin());
                    large.erase(large.begin());
                    large.insert(nums[i]);
                }
            } 
            else { // insert to large
                if (nums[i] >= *small.rbegin()) 
                    large.insert(nums[i]);
                else {
                    large.insert(*small.rbegin());
                    small.erase(--small.end());
                    small.insert(nums[i]);
                }
            }
            
            if (i >= (k - 1)) {
                double median = k & 1 ? (double)*small.rbegin() : 
                                        ((double)*small.rbegin() + (double)*large.begin()) / 2;
                res.push_back(median);
            }
        }
        
        return res;        
    }
};

/*
Solution 3: two heaps
time: O(nlogk)
space: O(k)
*/
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> medians;
        multiset<int> window(nums.begin(), nums.begin() + k);

        auto mid = next(window.begin(), k / 2);

        int i = k;
        while (true) {
            // Push the current median
            medians.push_back(((double)(*mid) + *next(mid, k % 2 - 1)) * 0.5);

            // If all done, break
            if (i == nums.size())
                break;

            // Insert incoming element
            window.insert(nums[i]);
            if (nums[i] < *mid)
                mid--;                  // same as mid = prev(mid)

            // Remove outgoing element
            if (nums[i - k] <= *mid)
                mid++;                  // same as mid = next(mid)

            window.erase(window.lower_bound(nums[i++ - k]));
        }

        return medians;

    }
};
