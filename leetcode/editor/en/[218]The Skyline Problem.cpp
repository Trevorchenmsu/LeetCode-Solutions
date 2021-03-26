//A city's skyline is the outer contour of the silhouette formed by all the buil
//dings in that city when viewed from a distance. Given the locations and heights 
//of all the buildings, return the skyline formed by these buildings collectively.
// 
//
// The geometric information of each building is given in the array buildings wh
//ere buildings[i] = [lefti, righti, heighti]: 
//
// 
// lefti is the x coordinate of the left edge of the ith building. 
// righti is the x coordinate of the right edge of the ith building. 
// heighti is the height of the ith building. 
// 
//
// You may assume all buildings are perfect rectangles grounded on an absolutely
// flat surface at height 0. 
//
// The skyline should be represented as a list of "key points" sorted by their x
//-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoi
//nt of some horizontal segment in the skyline except the last point in the list, 
//which always has a y-coordinate 0 and is used to mark the skyline's termination 
//where the rightmost building ends. Any ground between the leftmost and rightmost
// buildings should be part of the skyline's contour. 
//
// Note: There must be no consecutive horizontal lines of equal height in the ou
//tput skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acc
//eptable; the three lines of height 5 should be merged into one in the final outp
//ut as such: [...,[2 3],[4 5],[12 7],...] 
//
// 
// Example 1: 
//
// 
//Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
//Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
//Explanation:
//Figure A shows the buildings of the input.
//Figure B shows the skyline formed by those buildings. The red points in figure
// B represent the key points in the output list.
// 
//
// Example 2: 
//
// 
//Input: buildings = [[0,2,3],[2,5,3]]
//Output: [[0,3],[5,0]]
// 
//
// 
// Constraints: 
//
// 
// 1 <= buildings.length <= 104 
// 0 <= lefti < righti <= 231 - 1 
// 1 <= heighti <= 231 - 1 
// buildings is sorted by lefti in non-decreasing order. 
// 
// Related Topics Divide and Conquer Heap Binary Indexed Tree Segment Tree Line 
//Sweep 
// 👍 2766 👎 155


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution: sweep line
 * time: O(nlogn)
 * space: O(n)
 *
 * */
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> lines;
        vector<vector<int>> res;

        // sweep line
        for (const auto& b : buildings) {
            lines.push_back({b[0], -b[2]}); // left edge of rectangle
            lines.push_back({b[1], b[2]}); // right edge of rectangle
        }
        sort(lines.begin(), lines.end());

        multiset<int> heights{0};
        int curHeight = 0;
        int preHeight = 0;

        for (const auto& line : lines) {
            if (line.second < 0) // encounter left edge
                heights.insert(-line.second);
            else
                // encounter right edge, the height is no longer useful
                heights.erase(heights.find(line.second));
            curHeight = *heights.rbegin();
            if (curHeight != preHeight) {
                res.push_back({line.first, curHeight});
                preHeight = curHeight;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
