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
        if (points.empty() || points.size() == 0) {
            return res;
        }

        priority_queue<vector<double>> pq;

        for (const auto &point : points) {
            double dist = sqrt(point[0] * point[0] + point[1] * point[1]);
            pq.push({dist, (double) point[0], (double) point[1]});
            if (pq.size() > k) {
                pq.pop();
            }
        }

        while (!pq.empty()) {
            auto point = pq.top(); pq.pop();
            res.push_back({(int) point[1], (int) point[2]});
        }

        return res;
    }
};

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

        vector<double> distances;
        vector<vector<double>> dist2points;

        for (const auto &point : points) {
            double dist = sqrt(point[0] * point[0] + point[1] * point[1]);
            distances.push_back(dist);
            dist2points.push_back({dist, (double) point[0], (double) point[1]});
        }

        double dist_k = quickSelect(distances, 0, distances.size() - 1, k);

        for (const auto &p : dist2points) {
            if (p[0] <= dist_k) {
                res.push_back({(int) p[1], (int) p[2]});
            }
        }

        return res;
    }

private:
    double quickSelect(vector<double> &distances, int start, int end, int k) {
        if (start == end) {
            return distances[start];
        }

        // partition
        int i = start, j = end;
        int mid = start + (end -start) / 2;
        double pivot = distances[mid];
        while (i <= j) {
            while (i <= j && distances[i] < pivot) {
                i++;
            }

            while (i <= j && distances[j] > pivot) {
                j--;
            }

            if (i <= j) {
                swap(distances[i++], distances[j--]);
            }
        }

        if (start + k - 1 <= j) {
            return quickSelect(distances, start, j, k);
        }

        if (start + k - 1 >= i) {
            return quickSelect(distances, i, end, k - (i - start));
        }

        return distances[j + 1];
    }
};


//leetcode submit region end(Prohibit modification and deletion)
