/*
solution 1: dfs
time: O(n)
space: O(n)
*/
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        if (arr.empty() || arr.size() == 0)
            return false;
        vector<bool> visited(arr.size(), false);
        return dfs(arr, start, visited);
    }
    
    bool dfs(vector<int>& arr, int idx, vector<bool>& visited) {
        if (idx < 0 || idx >= arr.size() || visited[idx])
            return false;
        if (arr[idx] == 0)
            return true;
        
        visited[idx] = true;

        return dfs(arr, idx + arr[idx], visited) || 
        	   dfs(arr, idx - arr[idx], visited);
    }
};

/*
solution 2: dfs
time: O(n)
space: O(n)
*/

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        if (arr.size() == 0) return false;
        
        unordered_set<int> visited;
        queue<int> q{{start}};
        
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            if (cur < 0 || cur >= arr.size() || visited.count(cur)) continue;
            if (arr[cur] == 0) return true;
            visited.insert(cur);
            q.push(cur + arr[cur]);
            q.push(cur - arr[cur]);
        }
        
        return false;
    }
};