//You are given an array points, an integer angle, and your location, where loca
//tion = [posx, posy] and points[i] = [xi, yi] both denote integral coordinates on
// the X-Y plane. 
//
// Initially, you are facing directly east from your position. You cannot move f
//rom your position, but you can rotate. In other words, posx and posy cannot be c
//hanged. Your field of view in degrees is represented by angle, determining how w
//ide you can see from any given view direction. Let d be the amount in degrees th
//at you rotate counterclockwise. Then, your field of view is the inclusive range 
//of angles [d - angle/2, d + angle/2]. 
//
// 
// Your browser does not support the video tag or this video format. 
// 
//
// You can see some set of points if, for each point, the angle formed by the po
//int, your position, and the immediate east direction from your position is in yo
//ur field of view. 
//
// There can be multiple points at one coordinate. There may be points at your l
//ocation, and you can always see these points regardless of your rotation. Points
// do not obstruct your vision to other points. 
//
// Return the maximum number of points you can see. 
//
// 
// Example 1: 
//
// 
//Input: points = [[2,1],[2,2],[3,3]], angle = 90, location = [1,1]
//Output: 3
//Explanation: The shaded region represents your field of view. All points can b
//e made visible in your field of view, including [3,3] even though [2,2] is in fr
//ont and in the same line of sight.
// 
//
// Example 2: 
//
// 
//Input: points = [[2,1],[2,2],[3,4],[1,1]], angle = 90, location = [1,1]
//Output: 4
//Explanation: All points can be made visible in your field of view, including t
//he one at your location.
// 
//
// Example 3: 
//
// 
//Input: points = [[1,0],[2,1]], angle = 13, location = [1,1]
//Output: 1
//Explanation: You can only see one of the two points, as shown above.
// 
//
// 
// Constraints: 
//
// 
// 1 <= points.length <= 105 
// points[i].length == 2 
// location.length == 2 
// 0 <= angle < 360 
// 0 <= posx, posy, xi, yi <= 100 
// 
// Related Topics Array Math Geometry Sliding Window Sorting 
// 👍 271 👎 356


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sorting + sliding window
 * time: O(nlogn)
 * space: O(n)
 * */
class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        double pi = 3.1415926;
        vector<double> angles;

        int self = 0;
        for (const auto& point : points) {
            double dx = point[0] - location[0];
            double dy = point[1] - location[1];

            if (dx == 0 && dy == 0) {
                self++;
                continue;
            }

            double degree = atan2(dy, dx) + pi;
            angles.push_back(degree);
        }

        sort(angles.begin(), angles.end());

        int n = angles.size();
        for (int i = 0; i < n; i++) {
            angles.push_back(angles[i] + 2 * pi);
        }

        int res = 0, left = 0;
        for (int right = 0; right < 2 * n; right++) {
            while (left < 2 * n && angles[left] - angles[right] <= angle * pi / 180 +0.0000001) {
                left++;
            }
            res = max(res, left - right);
        }

        return res + self;
    }

};
//leetcode submit region end(Prohibit modification and deletion)
