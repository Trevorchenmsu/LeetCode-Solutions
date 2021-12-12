//There are a total of numCourses courses you have to take, labeled from 0 to nu
//mCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai,
// bi] indicates that you must take course bi first if you want to take course ai.
// 
//
// 
// For example, the pair [0, 1], indicates that to take course 0 you have to fir
//st take course 1. 
// 
//
// Return true if you can finish all courses. Otherwise, return false. 
//
// 
// Example 1: 
//
// 
//Input: numCourses = 2, prerequisites = [[1,0]]
//Output: true
//Explanation: There are a total of 2 courses to take. 
//To take course 1 you should have finished course 0. So it is possible.
// 
//
// Example 2: 
//
// 
//Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
//Output: false
//Explanation: There are a total of 2 courses to take. 
//To take course 1 you should have finished course 0, and to take course 0 you s
//hould also have finished course 1. So it is impossible.
// 
//
// 
// Constraints: 
//
// 
// 1 <= numCourses <= 105 
// 0 <= prerequisites.length <= 5000 
// prerequisites[i].length == 2 
// 0 <= ai, bi < numCourses 
// All the pairs prerequisites[i] are unique. 
// 
// Related Topics Depth-First Search Breadth-First Search Graph Topological Sort
// 
// 👍 6483 👎 271


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: topological sort
 * time: O(V+E)
 * space: O(V+E)
 *
 * */
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> inDegree (numCourses, 0); //O(n)
        unordered_map<int, vector<int>> node2edges;

        for (auto &pre: prerequisites) {//O(n)
            inDegree[pre[0]]++;
        }

        for (auto &pre: prerequisites) {//O(n)
            node2edges[pre[1]].push_back(pre[0]);
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {//O(n)
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int cnt = 0;
        while (!q.empty()) {
            auto node = q.front(); q.pop();
            cnt++;
            for (auto &neighbor : node2edges[node]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        return cnt == numCourses;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
