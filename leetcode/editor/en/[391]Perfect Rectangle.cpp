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
 * Solution 1: math
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

            // 为什么要求每个点的频率？因为如果全部矩形加起来刚好可以覆盖这个矩形区域的话，除了四个角，其他点都会出现两次
            // 这是因为那些重叠的边，在计算点的时候就会重复计算一次。而四个角没有重复边，所以只有一次。在循环结束后把他们的频率加1
            // 就可以保证所有点的频率都是2.
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

/*
 * solution 2: sweep line
 * time:
 * space:
 *
 * */
class Solution {
public:
    struct Event {
        int tm; // x-axis position.
        int index; // pointer to the rectangle in the given array.
        bool isStart; // This is the left edge of the rectangle, otherwise, right edge.
        Event(int t, int id, bool isS): tm(t), index(id), isStart(isS) {}
    };

    bool isRectangleCover(vector<vector<int>>& rectangles) {

        auto compPQ = [&](Event* e1, Event* e2) {
            if(e1->tm != e2->tm) return e1->tm > e2->tm;
            else return rectangles[e1->index][0] > rectangles[e2->index][0];
        };

        priority_queue<Event*, vector<Event*>, decltype(compPQ)> pq(compPQ);

        int bottom = INT_MAX, roof = INT_MIN;
        for(int i = 0; i < rectangles.size(); i++) {
            const vector<int>& rec = rectangles[i];
            Event* e1 = new Event(rec[0], i, true);
            Event* e2 = new Event(rec[2], i, false);
            pq.push(e1); pq.push(e2);
            bottom = min(bottom, rec[1]);
            roof = max(roof, rec[3]);
        }

        auto compSet = [&](Event* e1, Event* e2) {
            if(rectangles[e1->index][3] <= rectangles[e2->index][1]) return true;
            else return false;
        };

        set<Event*, decltype(compSet)> mySet(compSet);
        int yRange = 0;
        while(!pq.empty()) {
            int tm = pq.top()->tm;
            while(!pq.empty() && tm == pq.top()->tm) {
                Event* event = pq.top(); pq.pop();
                const vector<int>& rec = rectangles[event->index];
                if(event->isStart) {
                    auto rt = mySet.insert(event);
                    if(!rt.second) return false; // overlapping!!!
                    yRange += rec[3] - rec[1];
                }
                else {
                    mySet.erase(event);
                    yRange -= rec[3] - rec[1];
                }
            }
            if(!pq.empty() && yRange != roof - bottom) return false;
        }
        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
