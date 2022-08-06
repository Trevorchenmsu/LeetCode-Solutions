//Given an array of meeting time intervals intervals where intervals[i] = [start
//i, endi], return the minimum number of conference rooms required. 
//
// 
// Example 1: 
// Input: intervals = [[0,30],[5,10],[15,20]]
//Output: 2
// Example 2: 
// Input: intervals = [[7,10],[2,4]]
//Output: 1
// 
// 
// Constraints: 
//
// 
// 1 <= intervals.length <= 104 
// 0 <= starti < endi <= 106 
// 
// Related Topics Array Two Pointers Greedy Sorting Heap (Priority Queue) 
// 👍 4146 👎 74


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: mini heap
 * time: O(nlogn)
 * space: O(n)
 *
 * */
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> min_heap;

        for (auto itv : intervals)
        {
            if (!min_heap.empty() && itv[0] >= min_heap.top())
                min_heap.pop();
            min_heap.push(itv[1]);
        }

        return min_heap.size();
    }
};


class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort(key=lambda x : (x[0], x[1]))
        min_heap = []

        for itv in intervals:
            if len(min_heap) > 0 and itv[0] >= min_heap[0]:
                heappop(min_heap)
            heappush(min_heap, itv[1])

        return len(min_heap)

/*
 * solution 2: sweep line
 * time: O(nlogn)
 * space: O(n)
 *
 * */
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<pair<int, int>> room;

        for (auto itv : intervals)
        {
            room.push_back({itv[0], 1});
            room.push_back({itv[1], -1});
        }

        sort(room.begin(), room.end());

        int res = 0, cnt = 0;
        for (auto r : room)
        {
            cnt += r.second;
            res = max(res, cnt);
        }

        return res;
    }
};

class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        room = []
        for itv in intervals:
            room.append((itv[0], 1))
            room.append((itv[1], -1))

        room.sort(key=lambda x : (x[0], x[1]))

        res, cnt = 0, 0
        for r in room:
            cnt += r[1]
            res = max(res, cnt)

        return res
//leetcode submit region end(Prohibit modification and deletion)
