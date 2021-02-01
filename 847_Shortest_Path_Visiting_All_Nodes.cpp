/*
solution: bfs + bit state
time: O(n*2^n)
space: O(n*2^n)
*/

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        
        int finalState = 0;
        for (int i = 0; i < n; i++) {
            finalState |= (1 << i);
        }

        queue<pair<int, int>> q;
        vector<vector<bool>> visited (n, vector<bool> (finalState));        
        for (int i = 0; i < n; i++) {
            q.push({i, (1 << i)});
            visited[i][(1 << i)] = true;
        }
        
        int step = 0;        
        while (!q.empty()) {
            int len = q.size();       
            while (len--) {
                int node = q.front().first;
                int state = q.front().second;
                q.pop();
                           
                for (int next : graph[node]) {
                    int nextState = (state | 1 << next);
                    
                    if (nextState == finalState) 
                        return step + 1;
                    
                    if (visited[next][nextState])
                        continue;
                    
                    q.push({next, nextState});
                    visited[next][nextState] = true;
                }
            }
            step++;
        }
        return 0;
    }
};
