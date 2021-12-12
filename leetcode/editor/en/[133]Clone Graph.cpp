//Given a reference of a node in a connected undirected graph. 
//
// Return a deep copy (clone) of the graph. 
//
// Each node in the graph contains a value (int) and a list (List[Node]) of its 
//neighbors. 
//
// 
//class Node {
//    public int val;
//    public List<Node> neighbors;
//}
// 
//
// 
//
// Test case format: 
//
// For simplicity, each node's value is the same as the node's index (1-indexed)
//. For example, the first node with val == 1, the second node with val == 2, and 
//so on. The graph is represented in the test case using an adjacency list. 
//
// An adjacency list is a collection of unordered lists used to represent a fini
//te graph. Each list describes the set of neighbors of a node in the graph. 
//
// The given node will always be the first node with val = 1. You must return th
//e copy of the given node as a reference to the cloned graph. 
//
// 
// Example 1: 
//
// 
//Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
//Output: [[2,4],[1,3],[2,4],[1,3]]
//Explanation: There are 4 nodes in the graph.
//1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
//2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
//3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
//4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
// 
//
// Example 2: 
//
// 
//Input: adjList = [[]]
//Output: [[]]
//Explanation: Note that the input contains one empty list. The graph consists o
//f only one node with val = 1 and it does not have any neighbors.
// 
//
// Example 3: 
//
// 
//Input: adjList = []
//Output: []
//Explanation: This an empty graph, it does not have any nodes.
// 
//
// Example 4: 
//
// 
//Input: adjList = [[2],[1]]
//Output: [[2],[1]]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the graph is in the range [0, 100]. 
// 1 <= Node.val <= 100 
// Node.val is unique for each node. 
// There are no repeated edges and no self-loops in the graph. 
// The Graph is connected and all nodes can be visited starting from the given n
//ode. 
// 
// Related Topics Hash Table Depth-First Search Breadth-First Search Graph 
// 👍 3374 👎 1795


//leetcode submit region begin(Prohibit modification and deletion)
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

/*
 * solution 1: BFS + hash table
 * time: O(V+E)
 * space: O(V)
 * */

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (nodoe == NULL) {
            return NULL;
        }

        unordered_map<Node*, Node*> old2new;
        copyNodes(node, old2new);
        copyEdges(old2new);

        return old2new[node];
    }

private:
    void copyNodes(Node* node, unordered_map<Node*, Node*> &old2new) { // O(V+E)
        queue<Node*> q;
        q.push(node);
        unordered_set<Node*> visited;
        visited.insert(node);

        while (!q.empty()) {
            Node* cur = q.front(); q.pop(); // O(V)
            Node* newNode = new Node(cur->val);
            old2new[cur] = newNode;

            for (auto &neighbor : cur->neighbors) { // O(E)
                auto it = visited.find(neighbor);
                if (it != visited.end()) {
                    continue;
                }

                q.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }

    void copyEdges(unordered_map<Node*, Node*> &old2new) { // O(E)
        for (auto &[oldNode, newNode] : old2new) {
            for (auto &oldNeighbor : oldNode->neighbors) {
                Node* newNeighbor = old2new[oldNeighbor];
                newNode->neighbors.push_back(newNeighbor);
            }
        }
    }
};


/*
 * solution 2: BFS + hash table
 * time: O(V+E)
 * space: O(V)
 * */

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == NULL) {
            return node;
        }

        unordered_map<Node*, Node*> old2new;
        copyNodes(node, old2new);
        copyEdges(old2new);

        return old2new[node];
    }

    void copyNodes(Node* node, unordered_map<Node*, Node*> &old2new) {
        if (node == NULL) {
            return;
        }

        Node* node_new = new Node(node->val);
        old2new[node] = node_new;

        for (auto &nb : node->neighbors) {
            auto it = old2new.find(nb);
            if (it == old2new.end()) {
                copyNodes(nb, old2new);
            }
        }
    }

    void copyEdges(unordered_map<Node*, Node*> &old2new) {
        for (auto &[node_old, node_new] : old2new) {
            for (auto &nb : node_old->neighbors) {
                node_new->neighbors.push_back(old2new[nb]);
            }
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
