//Given an array of integers heights representing the histogram's bar height whe
//re the width of each bar is 1, return the area of the largest rectangle in the h
//istogram. 
//
// 
// Example 1: 
//
// 
//Input: heights = [2,1,5,6,2,3]
//Output: 10
//Explanation: The above is a histogram where width of each bar is 1.
//The largest rectangle is shown in the red area, which has an area = 10 units.
// 
//
// Example 2: 
//
// 
//Input: heights = [2,4]
//Output: 4
// 
//
// 
// Constraints: 
//
// 
// 1 <= heights.length <= 105 
// 0 <= heights[i] <= 104 
// 
// Related Topics Array Stack Monotonic Stack 
// 👍 7365 👎 118


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: monotonic increasing stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if (heights.empty() || heights.size() == 0) {
            return 0;
        }

        int res = 0, n = heights.size();
        stack<int> st;

        for (int i = 0; i <= n; i++) {
            int cur_h = i == n ? -1 : heights[i];
            while (!st.empty() && cur_h  < heights[st.top()]) {
                int h = heights[st.top()]; st.pop();
                int start = st.empty()? -1 : st.top();
                int w = i - 1 - start;
                res = max(res, h * w);
            }
            st.push(i);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
