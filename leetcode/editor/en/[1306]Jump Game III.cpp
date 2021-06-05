//Given an array of non-negative integers arr, you are initially positioned at s
//tart index of the array. When you are at index i, you can jump to i + arr[i] or 
//i - arr[i], check if you can reach to any index with value 0. 
//
// Notice that you can not jump outside of the array at any time. 
//
// 
// Example 1: 
//
// 
//Input: arr = [4,2,3,0,3,1,2], start = 5
//Output: true
//Explanation: 
//All possible ways to reach at index 3 with value 0 are: 
//index 5 -> index 4 -> index 1 -> index 3 
//index 5 -> index 6 -> index 4 -> index 1 -> index 3 
// 
//
// Example 2: 
//
// 
//Input: arr = [4,2,3,0,3,1,2], start = 0
//Output: true 
//Explanation: 
//One possible way to reach at index 3 with value 0 is: 
//index 0 -> index 4 -> index 1 -> index 3
// 
//
// Example 3: 
//
// 
//Input: arr = [3,0,2,1,2], start = 2
//Output: false
//Explanation: There is no way to reach at index 1 with value 0.
// 
//
// 
// Constraints: 
//
// 
// 1 <= arr.length <= 5 * 104 
// 0 <= arr[i] < arr.length 
// 0 <= start < arr.length 
// 
// Related Topics Depth-first Search Breadth-first Search Recursion 
// 👍 1223 👎 38


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: bfs
 * time: O(n)
 * space: O(n)
 * since it needs q to store next index. In fact, q would keep at most two levels of nodes.
 * Since we got two children for each node, the traversal of this solution is a binary tree.
 * The maximum number of nodes within a single level for a binary tree would be N/2
 * so the maximum length of q is o(N/2+N/2)=o(N)
 * */
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();

        queue<int> q;
        q.push(start);
        unordered_set<int> visited;
        visited.insert(start);

        while (!q.empty()) {
            int cur = q.front(); q.pop();

            if (arr[cur] == 0) return true;
            int dir1 = cur + arr[cur], dir2 = cur - arr[cur];

            if (isValid(arr, visited, dir1)) {
                q.push(dir1);
                visited.insert(dir1);
            }


            if (isValid(arr, visited, dir2)) {
                q.push(dir2);
                visited.insert(dir2);
            }
        }

        return false;
    }

    bool isValid(vector<int> &arr, unordered_set<int> &visited, int idx) {
        if (idx < 0 || idx >= arr.size())
            return false;

        if (visited.count(idx))
            return false;

        return true;
    }
};

/*
 * solution 2: dfs
 * time: O(n)
 * space: O(n)
 *
 * */
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
       int n = arr.size();
       vector<int> visited(n);
       return dfs(arr, start, visited);
    }

    bool dfs(vector<int> &arr, int idx, vector<int> &visited) {
        if (idx < 0 || idx >= arr.size() || visited[idx])
            return false;

        if (arr[idx] == 0)
            return true;

        visited[idx] = 1;

        return dfs(arr, idx + arr[idx], visited) ||
                dfs(arr, idx - arr[idx], visited);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
