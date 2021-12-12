//There are n cities. Some of them are connected, while some are not. If city a 
//is connected directly with city b, and city b is connected directly with city c,
// then city a is connected indirectly with city c. 
//
// A province is a group of directly or indirectly connected cities and no other
// cities outside of the group. 
//
// You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the 
//ith city and the jth city are directly connected, and isConnected[i][j] = 0 othe
//rwise. 
//
// Return the total number of provinces. 
//
// 
// Example 1: 
//
// 
//Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
//Output: 2
// 
//
// Example 2: 
//
// 
//Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 200 
// n == isConnected.length 
// n == isConnected[i].length 
// isConnected[i][j] is 1 or 0. 
// isConnected[i][i] == 1 
// isConnected[i][j] == isConnected[j][i] 
// Related Topics Depth-First Search Breadth-First Search Union Find Graph 
// 👍 3379 👎 194


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution 1: bfs
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        unordered_map<int, vector<int>> city2neighbor;
        getNeighbors(isConnected, city2neighbor);
        vector<int> visited (n, 0);

        int res = 0;
        for (int i = 0; i < n; i++) { // O(n)
            if (visited[i] == 1) {
                continue;
            }

            bfs(i, city2neighbor, visited); //O(n)
            res++;
        }

        return res;
    }

private:
    void bfs(int city, unordered_map<int, vector<int>> &city2neighbor, vector<int> &visited) {
        queue<int> q;
        q.push(city);

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            visited[cur] = 1;
            for (auto &neighbor : city2neighbor[cur]) {
                if (visited[neighbor] == 1) {
                    continue;
                }

                q.push(neighbor);
            }
        }
    }

    void getNeighbors(vector<vector<int>>& isConnected, unordered_map<int, vector<int>> &city2neighbor) {
        for (int i = 0; i < isConnected.size(); i++) {
            for (int j = 0; j < isConnected.size(); j++) {
                if (i == j) {
                    continue;
                }
                if (isConnected[i][j] == 1) {
                    city2neighbor[i].push_back(j);
                }
            }
        }
    }
};

/*
 * Solution 2: dfs
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        unordered_map<int, vector<int>> city2neighbor;
        getNeighbors(isConnected, city2neighbor);
        vector<int> visited (n, 0);

        int res = 0;
        for (int i = 0; i < n; i++) {
            if (visited[i] == 1) {
                continue;
            }

            dfs(i, city2neighbor, visited);
            res++;
        }

        return res;
    }

private:
    void dfs(int city, unordered_map<int, vector<int>> &city2neighbor, vector<int> &visited) {
        visited[city] = 1;
        for (auto &neighbor : city2neighbor[city]) {
            if (visited[neighbor] == 1) {
                continue;
            }
            dfs(neighbor, city2neighbor, visited);
        }
    }

    void getNeighbors(vector<vector<int>>& isConnected, unordered_map<int, vector<int>> &city2neighbor) {
        for (int i = 0; i < isConnected.size(); i++) {
            for (int j = 0; j < isConnected.size(); j++) {
                if (i == j) {
                    continue;
                }
                if (isConnected[i][j] == 1) {
                    city2neighbor[i].push_back(j);
                }
            }
        }
    }
};


/*
 * Solution 3: union find
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        if (isConnected.empty() || isConnected.size() == 0) {
            return 0;
        }

        // 极限情况：每个省只有一个市，所以总共有n个省
        int n = isConnected.size();
        int res = n;

        // 初始化上级：每个节点的上级都是本身
        vector<int> parents(n);
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }

        // union find中的union功能，将非连通块连接成连通块
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }

                /* grid值为1且i，j不等，表示i城市和j城市是相连接的，但是此时我们只是从矩阵值这里知道它们是连通的，
                  * 但是我们并不知道它们是否已经被操作过连成一个连通块，所以需要进行判定：如果i和j城市通过find函数找到
                  * 根节点不同，那说明它们俩还未被连成连通块，所以任选其中一个作为另一个的父级节点即可形成一个连通块，
                  * 而此时因为两个城市合并成一个省，因此省的个数减1.
                */

                if (isConnected[i][j] == 1) {
                    int i_root = find(i, parents);
                    int j_root = find(j, parents);
                    if (i_root!= j_root) {
                        parents[i_root] = j_root;
                        res--;
                    }
                }
            }
        }


        return res;
    }

private:
    // find函数查找根节点，如果节点的上级就是本身，就表示它是根节点，直接返回
    // 如果不是，就层层递归往上找。用迭代也可以。此解法中我们没有进行路径压缩
    int find(int root, vector<int> &parents) {
//         while (parents[root] != root) {
//             root = parents[root];
//         }

//         return root;
        if (root == parents[root]) {
            return root;
        }

        return find(parents[root], parents);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
