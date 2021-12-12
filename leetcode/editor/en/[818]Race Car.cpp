//Your car starts at position 0 and speed +1 on an infinite number line. Your ca
//r can go into negative positions. Your car drives automatically according to a s
//equence of instructions 'A' (accelerate) and 'R' (reverse): 
//
// 
// When you get an instruction 'A', your car does the following:
//
// 
// position += speed 
// speed *= 2 
// 
// 
// When you get an instruction 'R', your car does the following:
// 
// If your speed is positive then speed = -1 
// otherwise speed = 1 
// 
// Your position stays the same. 
// 
//
// For example, after commands "AAR", your car goes to positions 0 --> 1 --> 3 -
//-> 3, and your speed goes to 1 --> 2 --> 4 --> -1. 
//
// Given a target position target, return the length of the shortest sequence of
// instructions to get there. 
//
// 
// Example 1: 
//
// 
//Input: target = 3
//Output: 2
//Explanation: 
//The shortest instruction sequence is "AA".
//Your position goes from 0 --> 1 --> 3.
// 
//
// Example 2: 
//
// 
//Input: target = 6
//Output: 5
//Explanation: 
//The shortest instruction sequence is "AAARA".
//Your position goes from 0 --> 1 --> 3 --> 7 --> 7 --> 6.
// 
//
// 
// Constraints: 
//
// 
// 1 <= target <= 104 
// 
// Related Topics Dynamic Programming 
// 👍 752 👎 81


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1： BFS
 * time: O(nlogn), n为target的值
 * space: O(n)
 * */
class Solution {
public:
    int racecar(int target) {
        queue<pair<int, int>> q{{{0, 1}}};
        unordered_set<string> visited{{"0,1"}};

        int res = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                auto cur = q.front(); q.pop();
                int pos = cur.first, speed = cur.second;

                if (pos == target) {
                    return res;
                }

                int pos_next = pos + speed;
                int speed_next = speed * 2;
                string state_next = to_string(pos_next) + "," + to_string(speed_next);

                auto it = visited.find(state_next);
                /*
                 * 宽搜的范围：显然，进入负的位置是没有意义的，因为总可以找到一个更快得不进入负位置的答案。进入位置大于 2 * target
                 * 也是没有意义的，因为我们倒车不可能超过之前一步走的距离。所以搜索的范围被限制在了 [0, 2 * target] 中。
                 * */
                if (it == visited.end() && pos_next > 0 && pos_next < (target * 2)) {
                    q.push({pos_next, speed_next});
                    visited.insert(state_next);
                }

                speed_next = speed > 0 ? -1 : 1;
                pos_next = pos;
                state_next = to_string(pos_next) + "," + to_string(speed_next);

                it = visited.find(state_next);
                if (it == visited.end() && pos_next > 0 && pos_next < (target * 2)) {
                    q.push({pos_next, speed_next});
                    visited.insert(state_next);
                }

            }
            res++;
        }

        return -1;
    }
};


/*
 * solution 2： dp
 * time: O(nlogn), n为target的值
 * space: O(n)
 * */

class Solution {
    // dp[i]表示在i位置的最小方案长度
    int dp[10001] = {0};
public:
    int racecar(int target) {
        if (dp[target] != 0) {
            return dp[target];
        }

        int n = log2(target + 1); // 从2^n-1=target得来
        if (pow(2, n) - 1 == target) {
            dp[target] = n;
            return n;
        }

        // 超过target
        dp[target] = (n + 1) + 1 + racecar(pow(2, n + 1) - 1 - target);

        // 在target前停止
        for (int k = 0; k < n; k++) {
            int temp = n + 1 + k + 1 + racecar(target - (pow(2, n) - 1) + (pow(2, k) - 1));
            dp[target] = min(dp[target], temp);
        }

        return dp[target];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
