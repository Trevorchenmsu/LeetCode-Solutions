//There are n buildings in a line. You are given an integer array heights of siz
//e n that represents the heights of the buildings in the line. 
//
// The ocean is to the right of the buildings. A building has an ocean view if t
//he building can see the ocean without obstructions. Formally, a building has an 
//ocean view if all the buildings to its right have a smaller height. 
//
// Return a list of indices (0-indexed) of buildings that have an ocean view, so
//rted in increasing order. 
//
// 
// Example 1: 
//
// 
//Input: heights = [4,2,3,1]
//Output: [0,2,3]
//Explanation: Building 1 (0-indexed) does not have an ocean view because buildi
//ng 2 is taller.
// 
//
// Example 2: 
//
// 
//Input: heights = [4,3,2,1]
//Output: [0,1,2,3]
//Explanation: All the buildings have an ocean view.
// 
//
// Example 3: 
//
// 
//Input: heights = [1,3,2,4]
//Output: [3]
//Explanation: Only building 3 has an ocean view.
// 
//
// 
// Constraints: 
//
// 
// 1 <= heights.length <= 105 
// 1 <= heights[i] <= 109 
// 
// Related Topics Array Stack Monotonic Stack 
// 👍 614 👎 92


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: one pass max
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        int n = heights.size();
        vector<int> res, right_max(n);
        int max_val = heights[n - 1];

        for (int i = heights.size() - 2; i >= 0; --i) {
            right_max[i] = max_val;
            max_val = max(max_val, heights[i]);
        }

        for (int i = 0; i < n; ++i) {
            if (heights[i] > right_max[i])
                res.push_back(i);
        }

        return res;
    }
};

/*
 * solution 2: one pass max
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        int n = heights.size();
        vector<int> res {n - 1}; //最后一个元素索引总是会在答案中，因为右侧没有元素
        for (int i = n - 2; i >= 0; --i) {
            if (heights[i] > heights[res.back()]) {
                res.push_back(i);
            }
        }
        reverse(begin(res), end(res));
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
