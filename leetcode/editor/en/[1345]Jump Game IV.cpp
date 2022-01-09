//Given an array of integers arr, you are initially positioned at the first inde
//x of the array. 
//
// In one step you can jump from index i to index: 
//
// 
// i + 1 where: i + 1 < arr.length. 
// i - 1 where: i - 1 >= 0. 
// j where: arr[i] == arr[j] and i != j. 
// 
//
// Return the minimum number of steps to reach the last index of the array. 
//
// Notice that you can not jump outside of the array at any time. 
//
// 
// Example 1: 
//
// 
//Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
//Output: 3
//Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that in
//dex 9 is the last index of the array.
// 
//
// Example 2: 
//
// 
//Input: arr = [7]
//Output: 0
//Explanation: Start index is the last index. You don't need to jump.
// 
//
// Example 3: 
//
// 
//Input: arr = [7,6,9,6,9,6,9,7]
//Output: 1
//Explanation: You can jump directly from index 0 to index 7 which is last index
// of the array.
// 
//
// Example 4: 
//
// 
//Input: arr = [6,1,9]
//Output: 2
// 
//
// Example 5: 
//
// 
//Input: arr = [11,22,7,7,7,7,7,7,7,22,13]
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// 1 <= arr.length <= 5 * 104 
// -108 <= arr[i] <= 108 
// 
// Related Topics Breadth-first Search 
// 👍 630 👎 44


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: bfs
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 0;

        unordered_map<int, vector<int>> children;
        for (int i = 0; i < n; i++)
            children[arr[i]].push_back(i);

        vector<int> visited(n, 0);
        visited[0] = 1;
        queue<int> q;
        q.push(0);

        int step = 0;
        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                int cur = q.front(); q.pop();
                if (cur == n - 1) return step;

                if (cur + 1 < n && visited[cur + 1] == 0) {
                    q.push(cur + 1);
                    visited[cur + 1] = 1;
                }

                if (cur - 1 >= 0 && visited[cur - 1] == 0) {
                    q.push(cur - 1);
                    visited[cur - 1] = 1;
                }

                for (auto &next : children[arr[cur]]) {
                    if (visited[next] == 0) {
                        q.push(next);
                        visited[next] = 1;
                    }
                }

                children.erase(arr[cur]);
            }
            step++;
        }

        return 0;
    }
};

/*
 * solution 2: bfs + dp
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 0;

        // build the graph
        unordered_map<int, vector<int>> edges;
        int pre_idx = 0, pre_val = arr[0];
        edges[pre_val].push_back(pre_idx);
        for (int i = 1; i < n; i++) {
            int val = arr[i];
            if (val == pre_val && i != n - 1) { // skip duplicates
                pre_idx = i;
                continue;
            }
            edges[pre_val].push_back(pre_idx);
            pre_idx = i;
            pre_val = val;
            edges[pre_val].push_back(pre_idx);
        }

        // bfs
        vector<int> dp_visited(n, 0);
        dp_visited[0] = 1;
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            if (cur == n - 1) break;

            if (cur + 1 < n && dp_visited[cur + 1] == 0) {
                q.push(cur + 1);
                dp_visited[cur + 1] = dp_visited[cur] + 1;
            }

            if (cur - 1 >= 0 && dp_visited[cur - 1] == 0) {
                q.push(cur - 1);
                dp_visited[cur - 1] = dp_visited[cur] + 1;
            }

            auto s = edges[arr[cur]];
            for (size_t i = s.size() - 1; i > 0; i--) {
                if (dp_visited[s[i]] != 0)
                    continue;
                q.push(s[i]);
                dp_visited[s[i]] = dp_visited[cur] + 1;
            }

        }

        return dp_visited[n - 1] - 1;
    }
};

/*
 * solution 3: 双向BFS，TLE
 * time: O(n)？
 * space: O(n)
 * */
class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;

        unordered_map<int, vector<int>> val2idx;
        for (int i = 0; i < n; i++) val2idx[arr[i]].push_back(i);

        vector<int> visited(n);
        visited[0] = visited[n - 1] = 1;

        unordered_set<int> head, tail;
        head.insert(0);
        tail.insert(n - 1);

        int step = 0;
        while (!head.empty()) {
            if (head.size() > tail.size()) {
                unordered_set<int> temp = head;
                head = tail;
                tail = temp;
            }

            unordered_set<int> next;
            for (auto &cur : head) {
                // 考虑等值任意跳的情况是否与tail相交
                for (auto &idx : val2idx[arr[cur]]) {
                    if (tail.count(idx)) return step + 1;
                    if (visited[idx] == 0) next.insert(idx);
                }
                val2idx.erase(arr[cur]);

                // 考虑左右跳的情况是否与tail相交
                if (tail.count(cur + 1) || tail.count(cur - 1))
                    return step + 1;
                // 左右跳没有与tail相交，所以加入next
                int x = cur + 1, y = cur - 1;
                if (x < n && visited[x] == 0) next.insert(x);
                if (y >= 0 && visited[y] == 0) next.insert(y);
            }
            step++;
            head = next;
        }
        return -1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
