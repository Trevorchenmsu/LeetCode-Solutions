/*
solution: sliding window with deque (monotonic queue)
time: O(n), each element is added and deleted to deque.
space: O(n), O(n-k+1) to store the result, O(k) to store the deque. 
*/
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if (nums.empty() || nums.size() == 0) 
            return res;
        
        deque<int> dq;
        for (int i = 0; i < nums.size(); i++) {
            while(!dq.empty() && nums[i] > dq.back())
                dq.pop_back();
            dq.push_back(nums[i]);
            
            if (i < k - 1) 
                continue;
            
            res.push_back(dq.front());
            int out_num = nums[i - k + 1];
            
            if (dq.front() == out_num)
                dq.pop_front();
        }
        return res;
    }
};