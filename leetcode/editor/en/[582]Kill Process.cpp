//You have n processes forming a rooted tree structure. You are given two intege
//r arrays pid and ppid, where pid[i] is the ID of the ith process and ppid[i] is 
//the ID of the ith process's parent process. 
//
// Each process has only one parent process but may have multiple children proce
//sses. Only one process has ppid[i] = 0, which means this process has no parent p
//rocess (the root of the tree). 
//
// When a process is killed, all of its children processes will also be killed. 
//
//
// Given an integer kill representing the ID of a process you want to kill, retu
//rn a list of the IDs of the processes that will be killed. You may return the an
//swer in any order. 
//
// 
// Example 1: 
//
// 
//Input: pid = [1,3,10,5], ppid = [3,0,5,3], kill = 5
//Output: [5,10]
//Explanation: The processes colored in red are the processes that should be kil
//led.
// 
//
// Example 2: 
//
// 
//Input: pid = [1], ppid = [0], kill = 1
//Output: [1]
// 
//
// 
// Constraints: 
//
// 
// n == pid.length 
// n == ppid.length 
// 1 <= n <= 5 * 104 
// 1 <= pid[i] <= 5 * 104 
// 0 <= ppid[i] <= 5 * 104 
// Only one process has no parent. 
// All the values of pid are unique. 
// kill is guaranteed to be in pid. 
// 
// Related Topics Tree Queue 
// 👍 687 👎 14


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table + BFS
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        vector<int> res;
        queue<int> q;
        q.push(kill);

        unordered_map<int, vector<int>> parent2child;

        for (int i = 0; i < ppid.size(); i++) {
            parent2child[ppid[i]].push_back(pid[i]);
        }

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            res.push_back(cur);

            for (auto &child : parent2child[cur]) {
                q.push(child);
            }
        }

        return res;
    }
};


/*
 * solution 2: hash table + DFS
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        vector<int> res;
        unordered_map<int, vector<int>> m;
        for (int i = 0; i < pid.size(); ++i) {
            m[ppid[i]].push_back(pid[i]);
        }
        helper(kill, m, res);
        return res;
    }
    void helper(int kill, unordered_map<int, vector<int>>& m, vector<int>& res) {
        res.push_back(kill);
        for (int p : m[kill]) {
            helper(p, m, res);
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
