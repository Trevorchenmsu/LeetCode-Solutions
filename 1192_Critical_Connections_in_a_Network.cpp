/*
solution: DFS
time:
space:
*/

class Solution {
public:
    int time = 0;
    
    void dfs(int node,int parent, vector<vector<int>> &graph, vector<int> &visited, 
    		vector<int> &in, vector<int> &low, vector<vector<int>> &res){
        // mark this node as visited
        visited[node] += 1;

		// low => in time of the earliest ancestors to which it is directly 
		// connected to increase in time and low time
        in[node] = low[node] = time++;
        
        for(auto child: graph[node]){
            // if child is == parent simply continue (thats where we came from)
            if(child == parent) {
            	continue;
            }

            // if the child is alreay visited (must be ancestor so update the low of current node)
            if(visited[child]){
                low[node] = min(low[node], in[child]);
            } 
            else {
                // traverse through this unvisited child
                dfs(child, node, graph, visited, in, low, res);

                // update low of current node (cause child migt be directly connected to some early ancestor 
                // so current node can directly connect to it using this child)
                low[node] = min(low[node], low[child]);
             
                // if the earliest ansector that is connected to child comes after 
                // the current node then this is a bridge
                if(low[child] > in[node]){
                    // add node and child to res
                    res.push_back({ node, child });
                }
            }
        }
    }
    
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    	// build graph
        vector<vector<int>> graph(n + 1);
        for(auto connection: connections){
            graph[connection[0]].push_back(connection[1]);
            graph[connection[1]].push_back(connection[0]);
        }
        
        vector<vector<int>> res;
        vector<int> visited(n + 1, 0), in(n + 1, -1), low(n + 1,-1);
        dfs(0, -1, graph, visited, in, low, res);
        return res;
    }
};