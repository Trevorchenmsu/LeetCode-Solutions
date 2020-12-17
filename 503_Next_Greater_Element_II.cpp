class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> stk;
        vector<int> res(nums.size(), -1);
        for(int i = 0; i < nums.size() * 2; i++)
        {
            while(stk.size() && nums[stk.top()] < nums[i%nums.size()])
            {
                if(res[stk.top()] == -1)
                {
                    res[stk.top()] = nums[i%nums.size()];
                }
                stk.pop();
            }
            stk.push(i%nums.size());
        }
        return res;
    }
};
