//Given the coordinates of four points in 2D space p1, p2, p3 and p4, return tru
//e if the four points construct a square. 
//
// The coordinate of a point pi is represented as [xi, yi]. The input is not giv
//en in any order. 
//
// A valid square has four equal sides with positive length and four equal angle
//s (90-degree angles). 
//
// 
// Example 1: 
//
// 
//Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
//Output: true
// 
//
// Example 2: 
//
// 
//Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,12]
//Output: false
// 
//
// Example 3: 
//
// 
//Input: p1 = [1,0], p2 = [-1,0], p3 = [0,1], p4 = [0,-1]
//Output: true
// 
//
// 
// Constraints: 
//
// 
// p1.length == p2.length == p3.length == p4.length == 2 
// -104 <= xi, yi <= 104 
// 
// Related Topics Math Geometry 
// 👍 573 👎 670


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: math
 * time: O(1)
 * space: O(1)
 * */
class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        unordered_set<int> edge_set;
        int edge_1 = getEdge(p1, p2);
        int edge_2 = getEdge(p1, p3);
        int edge_3 = getEdge(p1, p4);
        int edge_4 = getEdge(p2, p3);
        int edge_5 = getEdge(p2, p4);
        int edge_6 = getEdge(p3, p4);

        edge_set.insert(edge_1);
        edge_set.insert(edge_2);
        edge_set.insert(edge_3);
        edge_set.insert(edge_4);
        edge_set.insert(edge_5);
        edge_set.insert(edge_6);

        return !edge_set.count(0) && edge_set.size() == 2;
    }

    int getEdge(vector<int>& p1, vector<int>& p2) {
        return (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
