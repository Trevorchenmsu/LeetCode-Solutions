/*
solution: topolocigal sort
time: O(mn), m is the number of the sequences, n is the length of each sequence
space: O(mn)
*/

class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        unordered_map<int, set<int>> graph = buildGraph(seqs);
        unordered_map<int, int> inDegree = getIndegree(graph);
        vector<int> ts = topoSort(graph, inDegree);
        
        if (ts.empty() || ts.size() != org.size()) return false;
        for (int i = 0; i < ts.size(); ++i) {
            if (org[i] != ts[i]) return false;                
        }   
        return true;
    }
    
    unordered_map<int, set<int>> buildGraph(const vector<vector<int>>& seqs) {
        unordered_map<int, set<int>> graph;
        // graph initialization
        for (auto& seq : seqs) {
            for (auto& node : seq) {
                if (!graph.count(node))  graph[node] = set<int> {};                  
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
    
    unordered_map<int, int> getIndegree(const unordered_map<int, set<int>>& graph) {
        unordered_map<int, int> inDegree;
        // in-degree initialization
        for (auto& g : graph) {
           inDegree[g.first] = 0;
        }
        
        for (auto& g : graph) {
            for (auto& e : g.second) {
                ++inDegree[e];
            }
        }
        return inDegree;
    }
    
    vector<int> topoSort( unordered_map<int, set<int>>& graph, 
                          unordered_map<int, int>& inDegree) {
        vector<int> res;
        queue<int> q;
        for (auto& in : inDegree) {
            if (in.second == 0) {
                q.push(in.first);
                res.push_back(in.first);
            }
        }
        
        while (!q.empty()) {
            if (q.size() > 1)  return vector<int> {};
            int node = q.front(); q.pop();
            for (auto& e : graph[node]) {
                if (--inDegree[e] != 0) continue;
                q.push(e);
                res.push_back(e);
            }
        }    
        return graph.size() == res.size() ? res : vector<int> {};
    }
};