//Given an array of points where points[i] = [xi, yi] represents a point on the 
//X-Y plane and an integer k, return the k closest points to the origin (0, 0). 
//
// The distance between two points on the X-Y plane is the Euclidean distance (i
//.e., √(x1 - x2)2 + (y1 - y2)2). 
//
// You may return the answer in any order. The answer is guaranteed to be unique
// (except for the order that it is in). 
//
// 
// Example 1: 
//
// 
//Input: points = [[1,3],[-2,2]], k = 1
//Output: [[-2,2]]
//Explanation:
//The distance between (1, 3) and the origin is sqrt(10).
//The distance between (-2, 2) and the origin is sqrt(8).
//Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
//We only want the closest k = 1 points from the origin, so the answer is just [
//[-2,2]].
// 
//
// Example 2: 
//
// 
//Input: points = [[3,3],[5,-1],[-2,4]], k = 2
//Output: [[3,3],[-2,4]]
//Explanation: The answer [[-2,4],[3,3]] would also be accepted.
// 
//
// 
// Constraints: 
//
// 
// 1 <= k <= points.length <= 104 
// -104 < xi, yi < 104 
// 
// Related Topics Array Math Divide and Conquer Geometry Sorting Heap (Priority 
//Queue) Quickselect 
// 👍 3556 👎 170


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: mini heap
 * time: O(nlogk)
 * space: O(k)
 *
 * */
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> res;
        if (points.empty()) return res;
        priority_queue<vector<int>> max_heap;
        vector<int> origin = {0, 0};

        for (auto &point : points)
        {
            int dist = getDistance(point, origin);
            max_heap.push({dist, point[0], point[1]});
            if (max_heap.size() > k) {
                max_heap.pop();
            }
        }

        while (!max_heap.empty())
        {
            auto p = max_heap.top(); max_heap.pop();
            res.push_back({p[1], p[2]});
        }

        return res;
    }

    int getDistance(vector<int> &p1, vector<int> &p2) {
        int dx = p1[0] - p2[0];
        int dy = p1[1] - p2[1];
        return dx * dx + dy * dy;
    }
};

class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        max_heap = []

        for (x, y) in points:
            dist = x ** 2 + y ** 2
            heappush(max_heap, (-dist, x, y))
            if len(max_heap) > k: heappop(max_heap)

        res = [(x, y) for (dist, x, y) in max_heap]
        return res
/*
 * solution 2: quick select
 * time: O(n)
 * space: O(n)
 *
 * */

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> res;
        if (points.empty() || points.size() == 0) {
            return res;
        }

        vector<vector<int>> distances;

        for (const auto &point : points) {
            int dist = point[0] * point[0] + point[1] * point[1];
            distances.push_back({dist, point[0], point[1]});
        }

        int dist_k = quickSelect(distances, 0, distances.size() - 1, k);

        for (const auto &d : distances) {
            if (d[0] <= dist_k) {
                res.push_back({d[1], d[2]});
            }
        }

        return res;
    }

    int quickSelect(vector<vector<int>> &distances, int start, int end, int k) {
        if (start == end) return distances[start][0];

        // partition
        int i = start, j = end;
        int mid = start + (end - start) / 2;
        int pivot = distances[mid][0];

        while (i <= j)
        {
            while (i <= j && distances[i][0] < pivot) ++i;
            while (i <= j && distances[j][0] > pivot) --j;
            if (i <= j) swap(distances[i++], distances[j--]);
        }

        if (start + k - 1 <= j) return quickSelect(distances, start, j, k);
        if (start + k - 1 >= i) return quickSelect(distances, i, end, k - (i - start));

        return distances[j + 1][0];

    }
};

class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        distances = []

        for (x, y) in points:
            dist = x**2 + y**2
            distances.append((dist, x, y))

        def quickSelect(distances, start, end, k):
            if start == end: return distances[start][0]

            i, j = start, end
            mid = start + (end - start) // 2
            pivot = distances[mid][0]

            while i <= j:
                while i <= j and distances[i][0] < pivot: i += 1
                while i <= j and distances[j][0] > pivot: j -= 1
                if i <= j:
                    distances[i], distances[j] = distances[j], distances[i]
                    i += 1
                    j -= 1

            if start + k - 1 <= j: return quickSelect(distances, start, j, k)
            if start + k - 1 >= i: return quickSelect(distances, i, end , k - i + start)

            return distances[j + 1][0]

        dist_k = quickSelect(distances, 0, len(distances) - 1, k)

        res = [(x, y) for (dist, x, y) in distances if dist <= dist_k]

        return res
//leetcode submit region end(Prohibit modification and deletion)
