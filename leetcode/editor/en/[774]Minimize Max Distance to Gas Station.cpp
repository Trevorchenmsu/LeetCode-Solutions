//You are given an integer array stations that represents the positions of the g
//as stations on the x-axis. You are also given an integer k. 
//
// You should add k new gas stations. You can add the stations anywhere on the x
//-axis, and not necessarily on an integer position. 
//
// Let penalty() be the maximum distance between adjacent gas stations after add
//ing the k new stations. 
//
// Return the smallest possible value of penalty(). Answers within 10-6 of the a
//ctual answer will be accepted. 
//
// 
// Example 1: 
// Input: stations = [1,2,3,4,5,6,7,8,9,10], k = 9
//Output: 0.50000
// Example 2: 
// Input: stations = [23,24,36,39,46,56,57,65,84,98], k = 1
//Output: 14.00000
// 
// 
// Constraints: 
//
// 
// 10 <= stations.length <= 2000 
// 0 <= stations[i] <= 108 
// stations is sorted in a strictly increasing order. 
// 1 <= k <= 106 
// 
// Related Topics Binary Search 
// 👍 425 👎 64


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: binary search
 * time: O(n*log(1e8))
 * space: O(1)
 * */
class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int k) {
        double start = 0, end = 1e8;
        while (start + 1e-6 < end) {
            double mid = start + (end - start) / 2;
            if (helper(stations, mid, k))
                end = mid;
            else
                start = mid;
        }

        return start;
    }

private:
    int helper(vector<int> &stations, double delta, int k) {
        int cnt = 0;
        for (int i = 1; i < stations.size(); i++) {
            cnt += (stations[i] - stations[i - 1]) / delta;
        }

        /*
         * 如果这里采用cnt<k，即等号是在start=mid的情况。当前mid满足k个时，我们会把start变为k，后面的查找
         * 会以这个mid/start为起点进行查找，下界被扩大了，而我们的目的是要最小penalty，即满足k的情况下找出
         * 更小的值，而应该往左边搜索。所以当求和个数满足k个时，应让end=mid，这样会往更小的方向查找。
         * */
        return cnt <= k;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
