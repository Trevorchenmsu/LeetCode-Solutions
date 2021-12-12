//You are given an array colors, in which there are three colors: 1, 2 and 3. 
//
// You are also given some queries. Each query consists of two integers i and c,
// return the shortest distance between the given index i and the target color c. 
//If there is no solution return -1. 
//
// 
// Example 1: 
//
// 
//Input: colors = [1,1,2,1,3,2,2,3,3], queries = [[1,3],[2,2],[6,1]]
//Output: [3,0,3]
//Explanation: 
//The nearest 3 from index 1 is at index 4 (3 steps away).
//The nearest 2 from index 2 is at index 2 itself (0 steps away).
//The nearest 1 from index 6 is at index 3 (3 steps away).
// 
//
// Example 2: 
//
// 
//Input: colors = [1,2], queries = [[0,3]]
//Output: [-1]
//Explanation: There is no 3 in the array.
// 
//
// 
// Constraints: 
//
// 
// 1 <= colors.length <= 5*10^4 
// 1 <= colors[i] <= 3 
// 1 <= queries.length <= 5*10^4 
// queries[i].length == 2 
// 0 <= queries[i][0] < colors.length 
// 1 <= queries[i][1] <= 3 
// 
// Related Topics Array Binary Search Dynamic Programming 
// 👍 290 👎 11


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: binary search + hash table
 * time: O(nlogn)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        unordered_map<int, vector<int>> clr2idx;
        for (int i = 0; i < colors.size(); i++) {
            clr2idx[colors[i]].push_back(i);
        }

        vector<int> res;
        for (auto &query : queries) {
            int idx = query[0], target = query[1];

            auto it = clr2idx.find(target);
            if (it == clr2idx.end()) {
                res.push_back(-1);
                continue;
            }

            if (target == colors[idx]) {
                res.push_back(0);
                continue;
            }

            int left_idx = clr2idx[target][0];
            int right_idx = clr2idx[target][clr2idx[target].size() - 1];

            if (idx <= left_idx) {
                res.push_back(left_idx- idx);
            }
            else if (idx >= right_idx) {
                res.push_back(idx - right_idx);
            }
            else {
                auto iter = upper_bound(clr2idx[target].begin(), clr2idx[target].end(), idx);
                int idx1 = *iter - idx;
                int idx2 = idx - *(--iter);
                res.push_back(min(idx1, idx2));
            }
        }

        return res;
    }
};

/*
 * solution 2: dp
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();
        vector<int> right_most = {0, 0 ,0};
        vector<int> left_most = {n - 1, n - 1, n - 1};

        vector<vector<int>> dist(3, vector<int> (n, -1));

        // looking forward
        for (int i = 0; i < n; i++) {
            int color = colors[i] - 1;
            for (int j = right_most[color]; j < i + 1; j++) {
                dist[color][j] = i - j;
            }
            right_most[color] = i + 1;
        }

        // looking backward
        for (int i = n - 1; i > -1; i--) {
            int color = colors[i] - 1;
            for (int j = left_most[color]; j > i - 1; j--) {
                if (dist[color][j] == -1 || dist[color][j] > j - i) {
                    dist[color][j] = j - i;
                }
            }
            left_most[color] = i - 1;
        }

        vector<int> res;
        for (int i = 0; i < queries.size(); i++) {
            res.push_back(dist[queries[i][1] - 1][queries[i][0]]);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
