/*
solution: bfs
time: O(V+E)
space: O(V+E)
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        
        vector<Node*> nodes = findNodes(node); // find all the nodes
        unordered_map<Node*, Node*> mapping = copyNodes(nodes); // mapping: old node -> new node
        copyEdges(mapping, nodes); // copy all the edges
        
        return mapping[node];
    }
    
private:
    vector<Node*> findNodes(Node* node) {
        vector<Node*> res;
        // bfs to find nodes
        queue<Node*> q;
        q.push(node);
        unordered_set<Node*> visited;
        visited.insert(node);
        
        while (!q.empty()) {
            Node* cur = q.front();
            res.push_back(cur);
            q.pop();
            for (auto& next : cur->neighbors) {
                if (visited.find(next) != visited.end())
                    continue;
                q.push(next);
                visited.insert(next);
            }
        }
        return res;
    }
    
    unordered_map<Node*, Node*> copyNodes(vector<Node*> nodes) {
        unordered_map<Node*, Node*> mapping;
        for (const auto& node : nodes) {
            mapping[node] = new Node(node->val);
        }
        return mapping;
    }
    
    void copyEdges(unordered_map<Node*, Node*>& mapping, vector<Node*> nodes) {
        for (const auto& node : nodes) {
            for (const auto& neighbor : node->neighbors) {
                mapping[node]->neighbors.push_back(mapping[neighbor]);
            }
        }
    }
};