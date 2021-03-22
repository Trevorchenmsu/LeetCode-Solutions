/*
solution: greedy + sort, sweep line
time: O(nlogn)
time: O(logn), stack space for quick sort in C++
*/

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;
        
        sort(points.begin(), points.end(), [](const vector<int> & v1, const vector<int> &v2){
            return v1[1] < v2[1];
        });
        
        int end = points[0][1], res = 1;
        
        for (const auto& point : points) {
            if (point[0] > end) {
                res++;
                end = point[1];
            }
        }
        
        return res;
    }
};