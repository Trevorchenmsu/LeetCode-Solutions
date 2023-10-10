//Given an array of points where points[i] = [xi, yi] represents a point on the 
//X-Y plane, return the maximum number of points that lie on the same straight lin
//e. 
//
// 
// Example 1: 
//
// 
//Input: points = [[1,1],[2,2],[3,3]]
//Output: 3
// 
//
// Example 2: 
//
// 
//Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
//Output: 4
// 
//
// 
// Constraints: 
//
// 
// 1 <= points.length <= 300 
// points[i].length == 2 
// -104 <= xi, yi <= 104 
// All the points are unique. 
// 
// Related Topics Array Hash Table Math Geometry 
// 👍 1303 👎 216


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: math
 * time: O(n^2)
 * space: O(1)
 * */

/*
 * 卡点：我的思路把问题想复杂了，考虑了线垂直/水平的情况，然后要如何做key。同时在考虑点的遍历时，第二层遍历则是从0开始，认为这样
 * 会双向考虑，有重复最后再除以2，否则点会考虑不全面。实际上不需要，因为在第一层遍历考虑每一个点与其它点的关系后，线上点最多的情况
 * 就已经被考虑了，后面的继续在i以后再点对点判断即可。
 * */
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int res = 0, n = points.size();

        for (int i = 0; i < n; ++i)
        {
            unordered_map<double, int> slope_to_cnt;
            int cnt = 0;
            for (int j = i + 1; j < n; ++j)
            {
                double slope = get_slope(points[i], points[j]);
                ++slope_to_cnt[slope];
                cnt = max(cnt, slope_to_cnt[slope]);
            }
            res = max(res, cnt);
        }

        return res + 1;
    }

    double get_slope(const vector<int> &p1, const vector<int> &p2)
    {
        double den = p1[0] - p2[0];
        return den == 0 ? INT_MAX : (p1[1] - p2[1]) / den;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
