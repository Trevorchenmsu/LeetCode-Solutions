/*
solution 1: greedy
time: O(nlogn), sort the array
space: O(1)
*/

class Solution {
  public:
  int twoCitySchedCost(vector<vector<int>>& costs) {
    // Sort by a gain which company has 
    // by sending a person to city A and not to city B
    sort(begin(costs), end(costs),
            [](const vector<int> &cost1, const vector<int> &cost2) {
      return (cost1[0] - cost1[1] < cost2[0] - cost2[1]);
    });

    int total = 0;
    int n = costs.size() / 2;
      
    // To optimize the company expenses,
    // send the first n persons to the city A
    // and the others to the city B
      
    for (int i = 0; i < n; ++i) 
        total += costs[i][0] + costs[i + n][1];
      
    return total;
  }
};

/*
solution 2greedy
time: O(nlogn), sort the array
space: O(1)
*/
class Solution {
public:
    static bool cmp(vector<int>& v1, vector<int>& v2){
        return v1[1] - v1[0] > v2[1] - v2[0];
    }
    
    int twoCitySchedCost(vector<vector<int>>& costs) {
        sort(costs.begin(), costs.end(), cmp);
        int n = costs.size(), total=0;
        
        for(int i = 0; i < n; ++i){
            total += i < n / 2 ? costs[i][0] : costs[i][1];
        }
        
        return total;
    }
};