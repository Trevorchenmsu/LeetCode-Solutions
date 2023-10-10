//A frog is crossing a river. The river is divided into some number of units, an
//d at each unit, there may or may not exist a stone. The frog can jump on a stone
//, but it must not jump into the water. 
//
// Given a list of stones' positions (in units) in sorted ascending order, deter
//mine if the frog can cross the river by landing on the last stone. Initially, th
//e frog is on the first stone and assumes the first jump must be 1 unit. 
//
// If the frog's last jump was k units, its next jump must be either k - 1, k, o
//r k + 1 units. The frog can only jump in the forward direction. 
//
// 
// Example 1: 
//
// 
//Input: stones = [0,1,3,5,6,8,12,17]
//Output: true
//Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd 
//stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 unit
//s to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.
// 
//
// Example 2: 
//
// 
//Input: stones = [0,1,2,3,4,8,9,11]
//Output: false
//Explanation: There is no way to jump to the last stone as the gap between the 
//5th and 6th stone is too large.
// 
//
// 
// Constraints: 
//
// 
// 2 <= stones.length <= 2000 
// 0 <= stones[i] <= 231 - 1 
// stones[0] == 0 
// stones is sorted in a strictly increasing order. 
// 
// Related Topics Array Dynamic Programming 
// 👍 2090 👎 151


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: brute force, TLE
 * time: O(3^n)
 * space: O(1)
 * */
class Solution {
public:
    bool canCross(vector<int>& stones) {
        return canCrossHelper(stones, 0, 0);
    }

    bool canCrossHelper(vector<int> &stones, int idx, int preJump) {
        if (idx == stones.size() - 1) return true;

        for (int i = idx + 1; i < stones.size(); i++) {
            int gap = stones[i] - stones[idx];
            if (gap >= preJump - 1 && gap <= preJump + 1) {
                if (canCrossHelper(stones, i, gap)) return true;
            }
        }

        return false;
    }
};

/*
 * solution 2: dfs + memo
 * time: O(n^3), 因为有k-1，k，k+1三种跳跃方式，相当于对这三种情况对遍历所有可能性，所以是n^3，重复的被memo过滤了
 * space: O(n^2)
 * */

class Solution {
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        vector<vector<int>> memo(n, vector<int> (n, -1));
        return canCrossHelper(stones, 0, 0, memo);
    }

    int canCrossHelper(vector<int> &stones, int idx, int preJump, vector<vector<int>> &memo) {
        if (memo[idx][preJump] != -1) return memo[idx][preJump];

        for (int i = idx + 1; i < stones.size(); i++) {
            int gap = stones[i] - stones[idx];
            if (gap >= preJump - 1 && gap <= preJump + 1) {
                if (canCrossHelper(stones, i, gap, memo) == 1) {
                    memo[idx][gap] = 1; // 注意这里使用的是idx而不是i，表示的是从idx位置跳gap步可行
                    return memo[idx][gap];
                }
            }
        }

        memo[idx][preJump] = (idx == stones.size() - 1) ? 1 : 0;

        return memo[idx][preJump];
    }
};


/*
 * solution 3: hashtable， optimal
 * time: O(n^2)
 * space: O(n^2)
 * */

class Solution {
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        // 哈希表映射关系：石头位置->在该石头上能跳多少步（哈希集存储）
        unordered_map<int, unordered_set<int>> stone2step;
        for (int i = 0; i < n; i++) {
            unordered_set<int> temp;
            stone2step[stones[i]] = temp;
        }

        //第一个石头只能跳一步
        stone2step[stones[0]].insert(1);
        int target = stones[n - 1];

        // 对每个石头位置进行查找，如果在当前位置加上可以跳到的步数能够抵达最后一个位置，就返回true
        for (int i = 0; i < n; i++) {
            for (auto &step : stone2step[stones[i]]) {
                int jump = step + stones[i];
                if (jump == target) return true;
                // 查找跳跃的石头，如果不存在哈希表中，表示石头数组中没有那个位置
                auto it = stone2step.find(jump);
                if (it != stone2step.end()) {
                    // 此时表示石头数组中有这个新跳跃位置，那么在jump下能够跳跃的选择有step-1，step，step+1
                    // 当step-1大于0的时候才有用处，小于等于0就不需要
                    stone2step[jump].insert(step);
                    stone2step[jump].insert(step + 1);
                    if (step - 1 > 0) stone2step[jump].insert(step - 1);
                }
            }
        }

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
