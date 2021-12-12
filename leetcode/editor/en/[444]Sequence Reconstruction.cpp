//Check whether the original sequence org can be uniquely reconstructed from the
// sequences in seqs. The org sequence is a permutation of the integers from 1 to 
//n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common supersequen
//ce of the sequences in seqs (i.e., a shortest sequence so that all sequences in 
//seqs are subsequences of it). Determine whether there is only one sequence that 
//can be reconstructed from seqs and it is the org sequence. 
//
// 
// Example 1: 
//
// 
//Input: org = [1,2,3], seqs = [[1,2],[1,3]]
//Output: false
//Explanation: [1,2,3] is not the only one sequence that can be reconstructed, b
//ecause [1,3,2] is also a valid sequence that can be reconstructed.
// 
//
// Example 2: 
//
// 
//Input: org = [1,2,3], seqs = [[1,2]]
//Output: false
//Explanation: The reconstructed sequence can only be [1,2].
// 
//
// Example 3: 
//
// 
//Input: org = [1,2,3], seqs = [[1,2],[1,3],[2,3]]
//Output: true
//Explanation: The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct th
//e original sequence [1,2,3].
// 
//
// Example 4: 
//
// 
//Input: org = [4,1,5,2,6,3], seqs = [[5,2,6,3],[4,1,5,2]]
//Output: true
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 10^4 
// org is a permutation of {1,2,...,n}. 
// 1 <= segs[i].length <= 10^5 
// seqs[i][j] fits in a 32-bit signed integer. 
// 
//
// 
//
// UPDATE (2017/1/8): 
//The seqs parameter had been changed to a list of list of strings (instead of a
// 2d array of strings). Please reload the code definition to get the latest chang
//es. 
// Related Topics Array Graph Topological Sort 
// 👍 385 👎 1265


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: topological sort
 * time: O(V + E)
 * space: O(V)
 * */
class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        unordered_map<int, unordered_set<int>> graph = buildGraph(seqs); // O(E)
        unordered_map<int, int> inDegree = getIndegree(graph);
        vector<int> ts = topoSort(graph, inDegree);

        if (ts.empty() || ts.size() != org.size()) {
            return false;
        }

        for (int i = 0; i < ts.size(); i++) { // O(V)
            if (ts[i] != org[i]) {
                return false;
            }
        }

        return true;
    }

private:
    unordered_map<int, unordered_set<int>> buildGraph(vector<vector<int>>& seqs) {
        unordered_map<int, unordered_set<int>> graph;
        // graph initialization
        for (auto& seq : seqs) { //O(E)
            for (auto& node : seq) {
                auto iter = graph.find(node)
                if (iter == graph.end()) {
                    // set<int> edge;
                    graph[node] = {};
                }
            }
        }

        // add edges
        for (auto& seq : seqs) {
            for (int i = 1; i < seq.size(); ++i) {
                graph[seq[i - 1]].insert(seq[i]);
            }
        }
        return graph;
    }

    unordered_map<int, int> getIndegree(unordered_map<int, unordered_set<int>> &graph) {
        unordered_map<int, int> inDegree;

        for (auto &[node, edges] : graph) { //O(VE)
            auto iter = inDegree.find(node)
            if (iter == inDegree.end()) {
                inDegree[node] = 0;
            }

            for (auto &edge : edges) { // O(E)
                ++inDegree[edge];
            }
        }

        return inDegree;
    }

    vector<int> topoSort(unordered_map<int, unordered_set<int>>& graph,
                         unordered_map<int, int>& inDegree) {
        vector<int> res;
        queue<int> q;
        for (auto &[node, indegree] : inDegree) {
            if (indegree == 0) {
                q.push(node);
            }
        }

        while (!q.empty()) { //O(V)
            if (q.size() > 1) {
                return {};
            }

            int node = q.front(); q.pop();
            res.push_back(node);
            for (auto &edge : graph[node]) {
                if (--inDegree[edge] != 0) {
                    continue;
                }
                q.push(edge);
            }
        }

        return graph.size() == res.size() ? res : vector<int> {};
    }
};
//leetcode submit region end(Prohibit modification and deletion)
