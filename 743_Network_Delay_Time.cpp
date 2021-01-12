class Solution {
public:

    int networkDelayTime(vector<vector<int>>& times, int n, int K) {
        const int INF = 0x3f3f3f3f;
        vector<vector<int>> g(n+1, vector<int>(n+1, INF));
        for (auto &v: times){
            g[v[0]][v[1]] = v[2];
        }
        vector<int> dist(n+1, INF); 
        vector<bool> st(n+1, false); 

        dist[K] = 0; 
        for (int i = 0; i< n - 1; i++ ){
            int t = -1;
            for (int j = 1; j <=n; j++){ // 
                if (!st[j] && (t == -1 || dist[t] > dist[j])){ 
                    t = j;
                }
            }

            st[t] = true; 

            for (int j = 1; j<=n; j++){ 
                dist[j] = min(dist[j], dist[t] + g[t][j]); 
            }
        }
        int ans = *max_element(dist.begin()+1, dist.end());
        return ans == INF ? -1: ans;
    }
};

