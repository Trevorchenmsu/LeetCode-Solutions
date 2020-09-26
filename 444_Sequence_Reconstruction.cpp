class Solution {
private:
    vector<int> getTopoOrder(unordered_map<int, set<int>> graph) {
        vector<int> topoOrder;
        queue<int> q;
        
        // get indegrees
       unordered_map<int, int> indegrees = getIndegrees(graph);

        // get the node with indegree=0
        for (auto &node : indegrees) {
            if (node.second == 0) {
                q.push(node.first);
                topoOrder.push_back(node.first);
            }
        }
        
        // BFS
        while (!q.empty()) {
            if (q.size() > 1) {
                return vector<int> {};
            }
            
            int node = q.front(); q.pop();
            for (auto &neighbor : graph[node]) {
                if(--indegrees[neighbor] == 0) {
                    q.push(neighbor);
                    topoOrder.push_back(neighbor);
                }
            }
        }
        
        if (graph.size() == topoOrder.size()) {
            return topoOrder;
        }
        
        return vector<int> {};
    }
    
    unordered_map<int, set<int>> buildGraph(vector<vector<int>>& seqs){
        unordered_map<int, set<int>> graph;
        for (auto &seq : seqs) {
            for (int i = 0; i < seq.size(); ++i) {
                if(!graph.count(seq[i])) {
                    set<int> edge;
                    graph[seq[i]] = edge;
                }
            }
        }
        
        for (auto &seq : seqs) {
            for (int i = 1; i < seq.size(); ++i) {
               graph[seq[i - 1]].insert(seq[i]);
            }
        }
        
        return graph;
    }
    
    unordered_map<int, int> getIndegrees(unordered_map<int, set<int>> &graph) {
        unordered_map<int, int> indegrees;  
        for (auto &node : graph) {
            indegrees[node.first] = 0;
        }
        
        for (auto &node : graph) {
            for (auto &neighbor : node.second) {
                indegrees[neighbor]++;
            }
        }
        
        return indegrees;
    }
    
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        unordered_map<int, set<int>> graph = buildGraph(seqs);
        vector<int> topoOrder = getTopoOrder(graph);
        vector<int> empty_res{};
        
        if (topoOrder == empty_res || topoOrder.size() != org.size()) {
            return false;
        }
        
        for (int i = 0; i < org.size(); ++i) {
            if (org[i] != topoOrder[i]) {
                return false;
            }
        }
        
        return true;
    }
};