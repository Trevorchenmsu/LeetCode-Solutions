//Given n non-negative integers a1, a2, ..., an , where each represents a point 
//at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of
// the line i is at (i, ai) and (i, 0). Find two lines, which, together with the x
//-axis forms a container, such that the container contains the most water. 
//
// Notice that you may not slant the container. 
//
// 
// Example 1: 
//
// 
//Input: height = [1,8,6,2,5,4,8,3,7]
//Output: 49
//Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,
//3,7]. In this case, the max area of water (blue section) the container can conta
//in is 49.
// 
//
// Example 2: 
//
// 
//Input: height = [1,1]
//Output: 1
// 
//
// Example 3: 
//
// 
//Input: height = [4,3,2,1,4]
//Output: 16
// 
//
// Example 4: 
//
// 
//Input: height = [1,2,1]
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// n == height.length 
// 2 <= n <= 105 
// 0 <= height[i] <= 104 
// 
// Related Topics Array Two Pointers Greedy 
// 👍 11138 👎 764


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: two pointers
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    int maxArea(vector<int>& height) {
        if (height.empty() || height.size() == 0) {
            return 0;
        }

        int left = 0, right = height.size() - 1, res = 0;
        while (left < right) {
            int width_cur = right - left;
            int height_cur = min(height[left], height[right]);
            res = max(res, width_cur * height_cur);

            if (height[left] < height[right]) {
                left++;
            }
            else {
                right--;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
