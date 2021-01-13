/*
solution: bfs
time: ?
space: O(1)
*/

class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        unordered_set<int> forb(forbidden.begin(), forbidden.end());
        const int maxN = 6001;
        // each node has two state: forward visisted or backward visited
        vector<vector<int>> visited(6001, vector<int> (2));
        visited[0][1] = 1; // no backward in start position
        queue<pair<int, int>> q; // node + visiting state
        q.push({0, 1});
        int res = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto [node, state] = q.front(); q.pop();
                if (node == x) return res;
                // forward check
                if (node + a < maxN && !forb.count(node + a) && !visited[node + a][1]) {
                    visited[node + a][1] = 1;
                    q.push({node + a, 1});
                }
                // backward check
                if (state == 1 && node - b >= 0 && !forb.count(node - b) && !visited[node - b][0])                 {
                    visited[node - b][0] = 1;
                    q.push({node - b, 0});
                }
            }
            ++res;
        }
        
        return -1;
    }
};