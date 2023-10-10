//You are given an array of points in the X-Y plane points where points[i] = [xi
//, yi]. 
//
// Return the minimum area of a rectangle formed from these points, with sides p
//arallel to the X and Y axes. If there is not any such rectangle, return 0. 
//
// 
// Example 1: 
//
// 
//Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
//Output: 4
// 
//
// Example 2: 
//
// 
//Input: points = [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// 1 <= points.length <= 500 
// points[i].length == 2 
// 0 <= xi, yi <= 4 * 104 
// All the given points are unique. 
// 
// Related Topics Array Hash Table Math Geometry Sorting 
// 👍 1550 👎 238


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: math, TLE
 * time: O(n^2*logn)
 * space: O(n)
 * */

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        set<vector<int>> seen;
        int res = INT_MAX;

        for (auto &p1 : points)
        {
            int x1 = p1[0], y1 = p1[1];
            for (auto &p2 : seen)
            {
                int x2 = p2[0], y2 = p2[1];
                if (seen.count({x1, y2}) && seen.count({x2, y1}))
                {
                    int area = abs((x1 - x2) * (y1 - y2));
                    if (area && area < res) res = area;
                }
            }
            seen.insert(p1);
        }

        return res == INT_MAX ? 0 : res;
    }
};


/*
 * solution 2: math, hash table + hash set
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        unordered_map<int, unordered_set<int>> seen;
        int res = INT_MAX;

        for (auto &p1 : points)
        {
            int x1 = p1[0], y1 = p1[1];
            for (auto &s : seen)
            {
                int x2 = s.first;
                for (auto &y2 : s.second)
                {
                    if (seen[x1].count(y2) && seen[x2].count(y1))
                    {
                        int area = abs((x1 - x2) * (y1 - y2));
                        res = min(area, res);
                    }
                }
            }
            seen[x1].insert(y1);
        }

        return res == INT_MAX ? 0 : res;
    }
};

class Solution:
    def minAreaRect(self, points: List[List[int]]) -> int:
        seen = set()
        res = float('inf')

        for (x1, y1) in points:
            for (x2, y2) in seen:
                if (x1, y2) in seen and (x2, y1) in seen:
                    area = abs((x1 - x2) * (y1 - y2))
                    res = min(area, res)
            seen.add((x1, y1))

        return res if res != float('inf') else 0
//leetcode submit region end(Prohibit modification and deletion)
