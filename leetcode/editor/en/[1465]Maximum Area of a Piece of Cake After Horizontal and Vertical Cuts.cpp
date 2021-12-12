//You are given a rectangular cake of size h x w and two arrays of integers hori
//zontalCuts and verticalCuts where: 
//
// 
// horizontalCuts[i] is the distance from the top of the rectangular cake to the
// ith horizontal cut and similarly, and 
// verticalCuts[j] is the distance from the left of the rectangular cake to the 
//jth vertical cut. 
// 
//
// Return the maximum area of a piece of cake after you cut at each horizontal a
//nd vertical position provided in the arrays horizontalCuts and verticalCuts. Sin
//ce the answer can be a large number, return this modulo 109 + 7. 
//
// 
// Example 1: 
//
// 
//Input: h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
//Output: 4 
//Explanation: The figure above represents the given rectangular cake. Red lines
// are the horizontal and vertical cuts. After you cut the cake, the green piece o
//f cake has the maximum area.
// 
//
// Example 2: 
//
// 
//Input: h = 5, w = 4, horizontalCuts = [3,1], verticalCuts = [1]
//Output: 6
//Explanation: The figure above represents the given rectangular cake. Red lines
// are the horizontal and vertical cuts. After you cut the cake, the green and yel
//low pieces of cake have the maximum area.
// 
//
// Example 3: 
//
// 
//Input: h = 5, w = 4, horizontalCuts = [3], verticalCuts = [3]
//Output: 9
// 
//
// 
// Constraints: 
//
// 
// 2 <= h, w <= 109 
// 1 <= horizontalCuts.length <= min(h - 1, 105) 
// 1 <= verticalCuts.length <= min(w - 1, 105) 
// 1 <= horizontalCuts[i] < h 
// 1 <= verticalCuts[i] < w 
// All the elements in horizontalCuts are distinct. 
// All the elements in verticalCuts are distinct. 
// 
// Related Topics Array Greedy Sorting 
// 👍 781 👎 192


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: greedy + sorting
 * time: O(nlogn + mlogm)
 * space: O(logn + logm)
 * */
class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        int h_top, h_bottom, v_left, v_right;
        int h_max = 0, v_max = 0, mod = 1e9 + 7;

        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());

        if (horizontalCuts.size() == 1) {
            h_top = horizontalCuts[0];
            h_bottom = horizontalCuts[0];
        }
        else {
            h_top = horizontalCuts[0];
            h_bottom = horizontalCuts[horizontalCuts.size() - 1];

            for (int i = 1; i < horizontalCuts.size(); i++) {
                h_max = max(h_max, (horizontalCuts[i] - horizontalCuts[i - 1]));
            }
        }
        h_max = max(max(h_top, h - h_bottom), h_max);

        if (verticalCuts.size() == 1) {
            v_left = verticalCuts[0];
            v_right = verticalCuts[0];
        }
        else {
            v_left = verticalCuts[0];
            v_right = verticalCuts[verticalCuts.size() - 1];

            for (int i = 1; i < verticalCuts.size(); i++) {
                v_max = max(v_max, (verticalCuts[i] - verticalCuts[i - 1]));
            }
        }

        v_max = max(max(v_left, w - v_right), v_max);

        long long res = ((long long) h_max * v_max) % mod;
        return (int) res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
