//You are given a list of songs where the ith song has a duration of time[i] sec
//onds. 
//
// Return the number of pairs of songs for which their total duration in seconds
// is divisible by 60. Formally, we want the number of indices i, j such that i < 
//j with (time[i] + time[j]) % 60 == 0. 
//
// 
// Example 1: 
//
// 
//Input: time = [30,20,150,100,40]
//Output: 3
//Explanation: Three pairs have a total duration divisible by 60:
//(time[0] = 30, time[2] = 150): total duration 180
//(time[1] = 20, time[3] = 100): total duration 120
//(time[1] = 20, time[4] = 40): total duration 60
// 
//
// Example 2: 
//
// 
//Input: time = [60,60,60]
//Output: 3
//Explanation: All three pairs have a total duration of 120, which is divisible 
//by 60.
// 
//
// 
// Constraints: 
//
// 
// 1 <= time.length <= 6 * 104 
// 1 <= time[i] <= 500 
// 
// Related Topics Array Hash Table Counting 
// 👍 2945 👎 114


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        long long res = 0;
        unordered_set<int> visited;
        unordered_map<int, int> time_cnt;
        for (auto &t : time) {
            /*
            取模后可以把所有的数限制在[0, 59]，不用去考虑t有多大。即便是模后结果相同，但是t不同也没事，
            如10和130，因为130的120成分在与另一个数求和再求模会被消除掉。那么，模后的数的计数器内容该
            怎么使用是本题的关键。
            */
            ++time_cnt[t % 60];
        }

        for (auto & tc : time_cnt) {
            int t = tc.first, cnt = tc.second;
            auto it = visited.find(t);
            if (it != visited.end()) continue;
            // 当t是60的倍数或30时，两个元素就能凑够模60，因此转化为组合思想，从n任意取2个数。
            if (t % 60 == 0 || t == 30) {
                res += (long long) cnt * (long long) (cnt - 1) / 2;
            }
            else {
                int target = 60 - t;
                auto it = time_cnt.find(target);
                if (it == time_cnt.end()) continue;
                res += cnt * time_cnt[target];
                visited.insert(target);
            }
            visited.insert(t);
        }

        return (int) res;
    }
};

/*
 * solution 2: hash table
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int res = 0;
        vector<int> cnt(60);

        for (auto &t : time) {
            res += cnt[(600 - t) % 60];
            ++cnt[t % 60];
        }

        return res;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
