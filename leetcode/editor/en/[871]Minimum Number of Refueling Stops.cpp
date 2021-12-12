//A car travels from a starting position to a destination which is target miles 
//east of the starting position. 
//
// There are gas stations along the way. The gas stations are represented as an 
//array stations where stations[i] = [positioni, fueli] indicates that the ith gas
// station is positioni miles east of the starting position and has fueli liters o
//f gas. 
//
// The car starts with an infinite tank of gas, which initially has startFuel li
//ters of fuel in it. It uses one liter of gas per one mile that it drives. When t
//he car reaches a gas station, it may stop and refuel, transferring all the gas f
//rom the station into the car. 
//
// Return the minimum number of refueling stops the car must make in order to re
//ach its destination. If it cannot reach the destination, return -1. 
//
// Note that if the car reaches a gas station with 0 fuel left, the car can stil
//l refuel there. If the car reaches the destination with 0 fuel left, it is still
// considered to have arrived. 
//
// 
// Example 1: 
//
// 
//Input: target = 1, startFuel = 1, stations = []
//Output: 0
//Explanation: We can reach the target without refueling.
// 
//
// Example 2: 
//
// 
//Input: target = 100, startFuel = 1, stations = [[10,100]]
//Output: -1
//Explanation: We can not reach the target (or even the first gas station).
// 
//
// Example 3: 
//
// 
//Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,4
//0]]
//Output: 2
//Explanation: We start with 10 liters of fuel.
//We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters
// to 60 liters of gas.
//Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
//and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the
// target.
//We made 2 refueling stops along the way, so we return 2.
// 
//
// 
// Constraints: 
//
// 
// 1 <= target, startFuel <= 109 
// 0 <= stations.length <= 500 
// 0 <= positioni <= positioni+1 < target 
// 1 <= fueli < 109 
// 
// Related Topics Array Dynamic Programming Greedy Heap (Priority Queue) 
// 👍 2052 👎 41


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: 1维DP，坐标型
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();
        vector<long> dp (n + 1, startFuel);

        /*
        状态转移方程：dp[i]表示加了i次油时所能抵达的最远距离。为了抵达当前加油站i，dp[i-1]必须大于等于当前油站的起点。
        那么最远距离就相当于从i前面的所有满足条件的油站选一个最远距离。
        */
        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j >= 0; --j)
            {
                if (dp[j] >= stations[i][0])
                {
                    dp[j + 1] = max(dp[j + 1], dp[j] + stations[i][1]);
                }
            }
        }

        // 最后从满足抵达target的最大距离中选一个最小的油站个数。
        for (int i = 0; i <= n; ++i)
        {
            if (dp[i] >= target)
            {
                return i;
            }
        }

        return -1;
    }
};

/*
 * solution 2: 最大堆，最优解
 * time: O(nlogn)
 * space: O(n)
 * */

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int num_refuel = 0, idx = 0, n = stations.size();
        priority_queue<int> max_heap;

        while (startFuel < target) {
            // idx表示当前加油站位置。如果当前油量能够开到i站，就把它加到最大堆中。
            // 贪心的思想，目的就是为了每次都能得到最大的加油位置，开最远的路。
            while (idx < n && stations[idx][0] <= startFuel) {
                max_heap.push(stations[idx][1]);
                idx++;
            }

            // 如果堆里为空，则表示上面while循环中无法加入元素，也就是当前油量无法抵达任何一个加油站
            if (max_heap.empty()) {
                return -1;
            }

            startFuel += max_heap.top();
            max_heap.pop();

            num_refuel++;
        }

        return num_refuel;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
