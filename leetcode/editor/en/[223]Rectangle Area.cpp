//Given the coordinates of two rectilinear rectangles in a 2D plane, return the 
//total area covered by the two rectangles. 
//
// The first rectangle is defined by its bottom-left corner (A, B) and its top-r
//ight corner (C, D). 
//
// The second rectangle is defined by its bottom-left corner (E, F) and its top-
//right corner (G, H). 
//
// 
// Example 1: 
//
// 
//Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
//Output: 45
// 
//
// Example 2: 
//
// 
//Input: A = -2, B = -2, C = 2, D = 2, E = -2, F = -2, G = 2, H = 2
//Output: 16
// 
//
// 
// Constraints: 
//
// 
// -104 <= A, B, C, D, E, F, G, H <= 104 
// 
// Related Topics Math 
// 👍 527 👎 867


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: standard sweep line
 * time: O(n*nlogn)
 * space: O(n)
 *
 * */
class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int open = 0, close = 1;
        vector<vector<long>> events;

        events.push_back({A, open, B, D});
        events.push_back({C, close, B, D});
        events.push_back({E, open, F, H});
        events.push_back({G, close, F, H});

        sort(events.begin(), events.end());
        vector<vector<long>> intervals;

        long pre_x = events[0][0], res = 0;
        for (const auto &event : events) {
            long cur_x = event[0], status = event[1], y1 = event[2], y2 = event[3];
            res += getArea(intervals, cur_x - pre_x);

            if (status == open) {
                intervals.push_back({y1, y2});
                sort(intervals.begin(), intervals.end());
            }
            else {
                for (int i = 0; i < intervals.size(); i++) {
                    if (intervals[i][0] == y1 && intervals[i][1] == y2) {
                        intervals.erase(intervals.begin() + i);
                        break;
                    }
                }
            }

            pre_x = cur_x;
        }

        return (int) res;
    }

private:
    long getArea(vector<vector<long>> &intervals, long width) {
        long area = 0, bottom = LONG_MIN;
        for (const auto & interval : intervals) {
            long top = interval[1];
            bottom = max(bottom, interval[0]);
            if (top > bottom) {
                area += (long) (top - bottom) * width;
                bottom = interval[1];
            }
        }

        return area;
    }

};


//leetcode submit region end(Prohibit modification and deletion)
