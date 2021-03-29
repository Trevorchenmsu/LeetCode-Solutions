//We are given a list of (axis-aligned) rectangles. Each rectangle[i] = [xi1, yi
//1, xi2, yi2] , where (xi1, yi1) are the coordinates of the bottom-left corner, a
//nd (xi2, yi2) are the coordinates of the top-right corner of the ith rectangle. 
//
//
// Find the total area covered by all rectangles in the plane. Since the answer 
//may be too large, return it modulo 109 + 7. 
//
// 
// Example 1: 
//
// 
//Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
//Output: 6
//Explanation: As illustrated in the picture.
// 
//
// Example 2: 
//
// 
//Input: rectangles = [[0,0,1000000000,1000000000]]
//Output: 49
//Explanation: The answer is 1018 modulo (109 + 7), which is (109)2 = (-7)2 = 49
//.
// 
//
// 
// Constraints: 
//
// 
// 1 <= rectangles.length <= 200 
// rectanges[i].length = 4 
// 0 <= rectangles[i][j] <= 109 
// The total area covered by all rectangles will never exceed 263 - 1 and thus w
//ill fit in a 64-bit signed integer. 
// 
// Related Topics Segment Tree Line Sweep 
// 👍 443 👎 32


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution 1: sweep line in x direction
 * time:O(n*nlogn)
 * space:O(n)
 *
 * */
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int start = 0, end = 1;
        int n = rectangles.size();
        vector<vector<long>> events; // O(2n*4)=O(n)

        for (const auto& rec : rectangles) { //O(n)
            int x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
            events.push_back({x1, start, y1, y2}); // left edge of the rectangle
            events.push_back({x2, end, y1, y2}); // right edge of the rectangle
        }
        // consider all the left edges first, then the right edges
        sort(events.begin(), events.end()); //O(nlogn)

        long res = 0;
        long pre_x = 0, MOD = 1000000007;
        vector<vector<long>> intervals; // O(n)

        for (const auto& event : events) { // O(n*nlogn)
            long cur_x = event[0], status = event[1], y1 = event[2], y2 = event[3];
            res += getArea(cur_x - pre_x, intervals); // O(n)

            if (status == start) {
                intervals.push_back({y1, y2});
                sort(intervals.begin(), intervals.end()); //O(nlogn)
            }
            else {
                // remove the considered interval
                for (int i = 0; i < intervals.size(); ++i) { // O(n)
                    if (intervals[i][0] == y1 && intervals[i][1] == y2) {
                        intervals.erase(intervals.begin() + i);
                        break;
                    }
                }
            }

            pre_x = cur_x;
        }

        return (int) (res % MOD);
    }

private:
    long getArea(long width, vector<vector<long>> &intervals) {
        long area = 0;
        long prev = 0;

        for (const auto& interval : intervals) {
            long bottom = interval[0], top = interval[1];
            bottom = max(bottom, prev);
            if (top > bottom) {
                area += (top - bottom) * width;
                prev = top;
            }
        }

        return area;
    }
};




/*
 * Solution 2: sweep line in y direction
 * time:O(n*nlogn)
 * space:O(n)
 *
 * */
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int start = 0, end = 1;
        int n = rectangles.size();
        vector<vector<long>> events;

        for (const auto& rec : rectangles) {
            int x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
            events.push_back({y1, start, x1, x2}); // left edge of the rectangle
            events.push_back({y2, end, x1, x2}); // right edge of the rectangle
        }
        // consider all the left edges first, then the right edges
        sort(events.begin(), events.end());

        long res = 0;
        long pre_y = 0, MOD = 1000000007;
        vector<vector<long>> intervals;

        for (const auto& event : events) {
            long cur_y = event[0], status = event[1], x1 = event[2], x2 = event[3];
            res += getArea(cur_y - pre_y, intervals);

            if (status == start) {
                intervals.push_back({x1, x2});
                sort(intervals.begin(), intervals.end());
            }
            else {
                for (int i = 0; i < intervals.size(); ++i) {
                    if (intervals[i][0] == x1 && intervals[i][1] == x2) {
                        intervals.erase(intervals.begin() + i);
                        break;
                    }
                }
            }

            pre_y = cur_y;
        }

        return (int) (res % MOD);
    }

private:
    long getArea(long width, vector<vector<long>> &intervals) {
        long area = 0;
        long prev = 0;

        for (const auto& interval : intervals) {
            long left = interval[0], right = interval[1];
            left = max(left, prev);
            if (right > left) {
                area += (right - left) * width;
                prev = right;
            }
        }

        return area;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
