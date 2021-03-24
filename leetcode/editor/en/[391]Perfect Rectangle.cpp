//Given N axis-aligned rectangles where N > 0, determine if they all together fo
//rm an exact cover of a rectangular region. 
//
// Each rectangle is represented as a bottom-left point and a top-right point. F
//or example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-lef
//t point is (1, 1) and top-right point is (2, 2)). 
//
// 
//
// Example 1: 
//
// 
//rectangles = [
//  [1,1,3,3],
//  [3,1,4,2],
//  [3,2,4,4],
//  [1,3,2,4],
//  [2,3,3,4]
//]
//
//Return true. All 5 rectangles together form an exact cover of a rectangular re
//gion.
// 
//
// 
//
// 
//
// 
//
// Example 2: 
//
// 
//rectangles = [
//  [1,1,2,3],
//  [1,3,2,4],
//  [3,1,4,2],
//  [3,2,4,4]
//]
//
//Return false. Because there is a gap between the two rectangular regions.
// 
//
// 
//
// 
//
// 
//
// Example 3: 
//
// 
//rectangles = [
//  [1,1,3,3],
//  [3,1,4,2],
//  [1,3,2,4],
//  [3,2,4,4]
//]
//
//Return false. Because there is a gap in the top center.
// 
//
// 
//
// 
//
// 
//
// Example 4: 
//
// 
//rectangles = [
//  [1,1,3,3],
//  [3,1,4,2],
//  [1,3,2,4],
//  [2,2,4,4]
//]
//
//Return false. Because two of the rectangles overlap with each other.
// 
//
// Related Topics Line Sweep 
// 👍 453 👎 86


// Leetcode submit region begin(Prohibit modification and deletion)

/*
 * Solution: math
 * time: O(nlogn)
 * space: O(n)
 * */


class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        if (rectangles.empty()) return false;
        map<pair<int, int>, int> point_cnt;
        int left = INT_MAX, bottom = INT_MAX, right = INT_MIN, upper = INT_MIN;
        int area = 0;

        for (const auto& rec : rectangles) {
            // get the bounding box coords
            bottom = min(bottom, rec[1]);
            left = min(left, rec[0]);
            upper = max(upper, rec[3]);
            right = max(right, rec[2]);

            // get the point frequency. They should be 2 or 4
            point_cnt[make_pair(rec[0], rec[1])]++;
            point_cnt[make_pair(rec[2], rec[1])]++;
            point_cnt[make_pair(rec[0], rec[3])]++;
            point_cnt[make_pair(rec[2], rec[3])]++;

            // compute area sum
            area += (rec[2] - rec[0]) * (rec[3] - rec[1]);
        }

        if (area != (right - left) * (upper - bottom))
            return false;

        // make sure the frequency of bounding box points is 2
        point_cnt[make_pair(left, bottom)]++;
        point_cnt[make_pair(right, bottom)]++;
        point_cnt[make_pair(left, upper)]++;
        point_cnt[make_pair(right, upper)]++;

        for (auto & point : point_cnt) {
            if (point.second % 2 != 0)
                return false;
        }

        return true;

    }
};
//leetcode submit region end(Prohibit modification and deletion)
