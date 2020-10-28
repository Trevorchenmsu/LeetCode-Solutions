/*
Solution 1: Brute force. Time Limit Exception
time: O(n*k*logk), as sort() each time takes O(klogk), traverse the array takes n times, so the final is O(N*N*logN)
space: O(k), extra linear space for the window container.
*/
// brute force
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        // edge case
        if (nums.empty() || nums.size() == 0) {
            return res;
        }
        
        // traverse the array
        for (int i = 0; i + k <= nums.size(); ++i) {
            vector<int> window(nums.begin() + i, nums.begin() + i + k);
            sort(window.begin(), window.end());
            
            if (k % 2 != 0) {
                res.push_back((double)window[k / 2]);
            } else {
                res.push_back(((double)window[k / 2 - 1] + (double)window[k / 2]) / 2.0);
            }
        }
                              
        return res;
        
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
        // 维护small和large两个堆，分别保存有序数组的左半段和右半段的数字
        // 这里使用multiset, 便于删除窗口以外的数字
        multiset<int> small, large;
        
        for (int i = 0; i < nums.size(); ++i) {
            // 出窗口的数字，nums[i-k], 从small和large里删除
            // 因为窗口内是排序后的数，nums[i-k]有可能在large，也有可能在small
            if (i >= k) {
                if (small.count(nums[i - k])) 
                    small.erase(small.find(nums[i - k]));
                else if (large.count(nums[i - k])) 
                    large.erase(large.find(nums[i - k]));
            }
            
            // 需要往small里放数字
            if (small.size() <= large.size()) {
                // nums[i]小，直接放
                if (large.empty() || nums[i] <= *large.begin()) 
                    small.insert(nums[i]);
                else {
                    // nums[i]大，从large里往small挪数字，因为较大的要放在large
                    // 所以只能将large开头的给small，把大的加进来large
                    small.insert(*large.begin());
                    large.erase(large.begin());
                    large.insert(nums[i]);
                }
            } else {
                // 需要往large里放数字
            
                // nums[i]大，直接放入large
                if (nums[i] >= *small.rbegin()) 
                    large.insert(nums[i]);
                else {
                    // nums[i]小，从small往large里挪数字
                    large.insert(*small.rbegin());
                    small.erase(--small.end());
                    small.insert(nums[i]);
                }
            }
            // 求median
            if (i >= (k - 1)) {
                if (k % 2) 
                    res.push_back(*small.rbegin());
                else 
                    res.push_back(((double)*small.rbegin() + *large.begin()) / 2);
            }
        }
        
        return res;        
    }
};