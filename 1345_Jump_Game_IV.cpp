/*
solution: BFS + DP
time: O(n)
space: O(n)
*/

class Solution {
public:
    int minJumps(vector<int>& arr) 
    {
        // build the edges in the graph
        unordered_map<int, vector<int>> edges;
        int pre_i = 0;
        int pre_val = arr[0];
        edges[pre_val].push_back(pre_i);
        for (size_t i = 1; i < arr.size(); i++) {
            int val = arr[i];
            if (val == pre_val && i != arr.size() - 1) {
                pre_i = i;
                continue;
            }
            edges[pre_val].push_back(pre_i);
            pre_i = i;
            pre_val = val;
            edges[pre_val].push_back(pre_i);
        }
        
        // BFS
        vector<int> dp_visited(arr.size(), 0);
        queue<int> q;
        q.push(0);
        dp_visited[0] = 1;

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            if (cur == arr.size() - 1) break;

            if (cur != 0 && dp_visited[cur - 1] == 0) {
                q.push(cur - 1);
                dp_visited[cur - 1] = dp_visited[cur] + 1;
            }
            if (cur != arr.size() - 1 && dp_visited[cur + 1] == 0) {
                q.push(cur + 1);
                dp_visited[cur + 1] = dp_visited[cur] + 1;
            }
            auto s = edges[arr[cur]];
            for (size_t i = s.size() - 1; i < s.size(); i--) {
                if (dp_visited[s[i]] != 0) continue;
                q.push(s[i]);
                dp_visited[s[i]] = dp_visited[cur] + 1;
            }
        }

        return dp_visited[arr.size() - 1] - 1;
    }
};