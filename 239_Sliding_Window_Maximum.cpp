/*
solution: sliding window with deque (monotonic queue)
time: O(n), since each elelemt enter the deque one time
space: O(n), maximum number in the deque will only be n. 
*/
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if (nums.empty() || nums.size() == 0)
            return res;
        
        deque<int> dq;
        for (int i = 0; i < nums.size(); ++i) {
            // maintain monotonic queue
            while (!dq.empty() && nums[i] > nums[dq.back()]) {
                dq.pop_back();
            }
            
            // maintain the length of window
            if (!dq.empty() && i - dq.front() >= k) {
                dq.pop_front();
            }
            
            dq.push_back(i);
            
            // get the maximum value
            if (i >= k - 1) {
                res.push_back(nums[dq.front()]);
            }
        }
        return res;                              
    }
};