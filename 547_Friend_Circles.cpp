/*
Solution 1: BFS
time: O(n*n), traverse the matrix
space: O(n), the maximum size of the queue.
*/
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int res = 0;
        if (M.empty() || M.size() == 0 || M[0].empty() || M[0].size() == 0) {
            return res;
        }
        
        for (int i = 0; i < M.size(); ++i) {
            if (M[i][i] == 1) {
                ++res;
                BFS(i, M);
            }
        }
        
        return res;
    }
    
    void BFS(int student, vector<vector<int>>& M) {
        queue<int> q;
        q.push(student);
        
        while (!q.empty()) {
            int j = q.front();
            q.pop();
            M[j][j] = 0;
            for (int i = 0; i < M[0].size(); ++i){
                if (M[i][j] == 1 && M[i][i] == 1) {
                    q.push(i);
                }
            }
        }
    }
};

/*
Solution 2: DFS
time: O(n*n), traverse the matrix
space: O(n), the maximum size of the students.
*/
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int res = 0;     
        if (M.empty() || M.size() == 0 || M[0].empty() || M[0].size() == 0) {
            return res;
        }
        
        for (int i = 0; i < M.size(); ++i) {
            if (M[i][i] == 1) {
                ++res;
                dfs(i, M);
            }
        }
        return res;
    }
    
    void dfs(int student, vector<vector<int>>& M) {
        M[student][student] = 0;
        
        for (int j = 0; j < M[0].size(); ++j) {
            if (M[j][j] == 1 && M[student][j] == 1) {
                M[j][j] = 0;
                dfs(j, M);
            }
        }
    }
};

/*
Solution 3: Union Find
time: O(n*n), traverse the matrix
space: O(n), the maximum size of the students.
*/

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int res = unionFind(M);
        return res;
    }

private:
    int unionFind(vector<vector<int>>& M) {
        int n = M.size();
        // each in its circle, so n circle
        int res = n;
        
        vector<int> parent(n);
        // initialization: each is its parent node
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        
        // traverse the matrix
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // find friend
                if (M[i][j] == 1 && i != j) {
                    // check whether the two students are in same set
                    if (find(i, parent) != find(j, parent)) {
                        parent[find(i, parent)] = find(j, parent);
                        --res;
                    }
                }
            }
        }
        
        return res;
    }
    
    int find(int student, vector<int>& parent) {
        if (parent[student] == student) {
            return student;
        } else {
            return parent[student] = find(parent[student], parent);
        }
    }
};