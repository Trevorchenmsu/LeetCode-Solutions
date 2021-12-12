//You are given an array of transactions transactions where transactions[i] = [f
//romi, toi, amounti] indicates that the person with ID = fromi gave amounti $ to 
//the person with ID = toi. 
//
// Return the minimum number of transactions required to settle the debt. 
//
// 
// Example 1: 
//
// 
//Input: transactions = [[0,1,10],[2,0,5]]
//Output: 2
//Explanation:
//Person #0 gave person #1 $10.
//Person #2 gave person #0 $5.
//Two transactions are needed. One way to settle the debt is person #1 pays pers
//on #0 and #2 $5 each.
// 
//
// Example 2: 
//
// 
//Input: transactions = [[0,1,10],[1,0,1],[1,2,5],[2,0,5]]
//Output: 1
//Explanation:
//Person #0 gave person #1 $10.
//Person #1 gave person #0 $1.
//Person #1 gave person #2 $5.
//Person #2 gave person #0 $5.
//Therefore, person #0 only need to give person #1 $4, and all debt is settled.
// 
//
// 
// Constraints: 
//
// 
// 1 <= transactions.length <= 8 
// transactions[i].length == 3 
// 0 <= fromi, toi <= 20 
// fromi != toi 
// 1 <= amounti <= 100 
// 
// Related Topics Array Backtracking 
// 👍 941 👎 88


//leetcode submit region begin(Prohibit modification and deletion)

/*
 * solution 1: two pointers + hash table, wrong answer
 * */
class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> id_balance;

        for (auto &t : transactions) {
            int from = t[0], to = t[1], cash = t[2];
            id_balance[from] -= cash;
            id_balance[to] += cash;
        }

        vector<int> balance;
        for (auto &ib : id_balance) {
            balance.push_back(ib.second);
        }

        sort(balance.begin(), balance.end());

        int left = 0, right = balance.size() - 1;
        int cnt = 0;
        while (left < right) {
            while (left < right && balance[left] < 0 && abs(balance[left]) > abs(balance[right])) {
                balance[left] += balance[right];
                right--, cnt++;
            }

            while (left < right && balance[right] != 0 && balance[left] + balance[right] == 0) {
                left++, right--;
                cnt++;
            }

            while (left < right && balance[left] < 0 && abs(balance[left]) < abs(balance[right])) {
                balance[right] += balance[left];
                left++, cnt++;
            }

            if (balance[left] == 0) {
                left++;
            }

            if (balance[right] == 0) {
                right--;
            }
        }

        return cnt;
    }
};

/*
 * solution 2: hash table + backtrack
 * time: O(n!)，n是债务中的非零个数
 * space: O(m+n)，m为人数
 * */

class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> id_balance;
        int res = INT_MAX;

        for (auto &t : transactions) {
            int from = t[0], to = t[1], cash = t[2];
            id_balance[from] -= cash;
            id_balance[to] += cash;
        }

        vector<int> balance;
        for (auto &ib : id_balance) {
            if (ib.second != 0) {
                balance.push_back(ib.second);
            }
        }

        backtrack(res, balance, 0, 0);

        return res;
    }

    /*
    为什么可以用回溯？在balance中有正/负，目的是任意组合这些正负值凑出和为0的情况，回溯可以暴力的考虑到所有的情况，所以在整个回溯过程中我们采用了res来记录最终最小的分配数。
    */
    void backtrack(int& res, vector<int> &balance, int idx, int cnt) {
        // cnt用来跟进每条路径的计数器，方便用于res的比较。在路径过程中，某些idx下的值可以累加后为0
        while (idx < balance.size() && balance[idx] == 0) {
            idx++;
        }

        // 当idx走到底，表明路径已经走完，此时更新结果。根据题意，路径是一定存在的
        if (idx == balance.size()) {
            res = min(res, cnt);
            return;
        }

        // 因为递归是从idx进来的，要考虑下面的元素，所以从idx+1开始。只考虑符号不同的情况
        for (int i = idx + 1; i < balance.size(); ++i) {
            if (balance[i] * balance[idx] < 0) {
                balance[i] += balance[idx];
                backtrack(res, balance, idx + 1, cnt + 1);
                balance[i] -= balance[idx];
            }
        }
    }

};
//leetcode submit region end(Prohibit modification and deletion)
