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
        vector<vector<int>> res;
        vector<vector<int>> lines;


        //存储所有矩形左边和右边的xy坐标，左边以负数加入，便于区分左右边，然后以x坐标排序
        for(const auto& b : buildings){
            lines.push_back({b[0], -b[2]});
            lines.push_back({b[1], b[2]});
        }
        sort(lines.begin(), lines.end());

        /*采用有序哈希集存储高度，目的是为了让高度有序，为什么？因为这样我们可以每次都取高度
          的最大值，当较高矩形存在时，这个较大的高度会覆盖很多小矩形，从而不用考虑它们
          预先存入0是防止所有高度被删除后，仍然需要底平面（高度为0）来作为高度的关键点。
         */
        multiset<int> heights{0};

        int curHeight = 0;
        int preHeight = 0;

        /*
         * 遍历所有边。如果遇到高度为负数，表示遇到了矩形左边，将高度插入哈希集中，同时取负还原高度值。
         * 如果遇到高度为负数，表示遇到了矩形右边，即目前这个矩形已经被考虑完毕，它的高度不再被需要，
         * 所以从高度哈希集中删除掉。
         *
         * */
        for(const auto &line : lines){
            if(line[1] < 0) {
                heights.insert(-line[1]);
            }
            else {
                auto it = heights.find(line[1]);
                heights.erase(it);
            }

            /*
             * 最关键的模块：
             * (1)先对高度哈希集取最后一个元素，因为它是有序的，最后一个也是最大的，作为当前高度；
             * (2)如果当前高度不等于之前的高度，即表示当前高度比之前的高度大（因为有序），则把
             *    对应x坐标和当前高度加入结果中，并更新之前高度。只要目前有矩形存在，它就会覆盖其他
             *    小矩形，因此下面的curHeight总是这个高，if也不会执行。只有当走到大矩形的右边界时，
             *    通过上面的erase语句把它从高度哈希集中删除，接下来的curHeight就由第二大高度顶替，
             *    从而加入新的关键点。此时是以被删除矩形的右边界为x坐标，y则为第二大高度。
             * */
            curHeight = *heights.rbegin();
            if(curHeight != preHeight){
                res.push_back({line[0], curHeight});
                preHeight = curHeight;
            }
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
