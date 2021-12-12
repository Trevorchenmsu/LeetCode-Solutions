//Given an array of integers temperatures represents the daily temperatures, ret
//urn an array answer such that answer[i] is the number of days you have to wait a
//fter the ith day to get a warmer temperature. If there is no future day for whic
//h this is possible, keep answer[i] == 0 instead. 
//
// 
// Example 1: 
// Input: temperatures = [73,74,75,71,69,72,76,73]
//Output: [1,1,4,2,1,1,0,0]
// Example 2: 
// Input: temperatures = [30,40,50,60]
//Output: [1,1,1,0]
// Example 3: 
// Input: temperatures = [30,60,90]
//Output: [1,1,0]
// 
// 
// Constraints: 
//
// 
// 1 <= temperatures.length <= 105 
// 30 <= temperatures[i] <= 100 
// 
// Related Topics Array Stack Monotonic Stack 
// 👍 5152 👎 139


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: monotonic decreasing stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        if (temperatures.empty() || temperatures.size() == 0) {
            return {};
        }

        int size = temperatures.size();
        vector<int> res(size);
        stack<int> st;

        for (int i = 0; i < size; i++) {
            int cur_temp = temperatures[i];
            while (!st.empty() && cur_temp > temperatures[st.top()]) {
                int pre_temp_idx = st.top(); st.pop();
                res[pre_temp_idx] = i - pre_temp_idx;
            }
            st.push(i);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
