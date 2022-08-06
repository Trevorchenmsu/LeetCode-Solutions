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
 * 具体思路: https://github.com/wisdompeak/LeetCode/tree/master/Math/1610.Maximum-Number-of-Visible-Points
 * */

/*
 * 为什么会应用到滑窗的思路？当求得所有点的角度并排序后，可以得到一系列角度，这些角度本质上也是从起点发射出去的一堆射线，绕着点旋转着特定角度
 * 而指定的angle实际上就是把这些角度限定在这个区域内，跟数组指定窗口长度k本质上是一样的。
 * */
class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        double pi = 3.1415926;
        vector<double> angles;

        int extra = 0;
        for (const auto& point : points) {
            double dx = point[0] - location[0];
            double dy = point[1] - location[1];

            if (dx == 0 && dy == 0) {
                extra++;
                continue;
            }
            // atan(dy/dx)得到的值域其实是[-pi/2,pi/2]，要根据(x,y)的具体的象限位置再做调整
            // 另外一种方法是利用函数atan2(dy,dx)，得到是(x,y)这个点相对于x正轴的“辐角主值”，值域范围是[-pi,pi].
            // 因为圆周对称，我们可以将这个“视野角度”整体加上pi转换成[0,2*pi]，并不影响结果。
            double degree = atan2(dy, dx) + pi;
            angles.push_back(degree);
        }

        sort(angles.begin(), angles.end());

        /*
         * 本题的第二个考点是“首尾相接”。因为视野角度接近360度的目标点，与视野角度接近0度的目标点，
         * 其真实角度差范围并不大。那么我们如果寻找一个滑窗使得能够同时覆盖这两部分的点呢？
         * 处理的方法很常见，那就是将所有目标点的视野角度复制一遍、加上2pi、并拼接在angles数组后面。
         * 这样相当于angles数组里面有2n个目标点，视野范围是[0,4pi]。
         * 对于任何跨越过360角的滑窗，都可以覆盖到原先接近0度角的那些点。*/
        int n = angles.size();
        for (int i = 0; i < n; i++) {
            angles.push_back(angles[i] + 2 * pi);
        }

        /*
         * 此题的第三个考点是：如果目标点与观测点完全重合，它可以算作任意的视野范围，
         * 所以我们需要把它们单独处理，不能放入angles数组内。我们要把这些点另外计入angles的最大滑窗里。*/
        int res = 0, left = 0;
        for (int right = 0; right < 2 * n; right++) {
            while (left < 2 * n && angles[left] - angles[right] <= angle * pi / 180 +0.0000001) {
                left++;
            }
            res = max(res, left - right);
        }

        return res + extra;
    }

};
//leetcode submit region end(Prohibit modification and deletion)
