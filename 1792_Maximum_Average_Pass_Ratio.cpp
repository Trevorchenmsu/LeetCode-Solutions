/*
solution: greedy + max heap
time: O(nlogn)
space: O(n)
*/
class Solution {
public:
  
    struct cmp{
        bool operator()(pair<int,int> &p1, pair<int,int> &p2){
            // (n + 1) /(m + 1) - n / m, greedy
            double score1 = (p1.first + 1) / (double) (p1.second + 1) - (p1.first) / (double) p1.second;
            double score2 = (p2.first + 1) / (double) (p2.second + 1) - (p2.first) / (double) p2.second;
            return score1 < score2;
        }
    };
    
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        double res;
        priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> maxHeap;
        
        for(vector<int> c : classes)
            maxHeap.push(make_pair(c[0], c[1]));
        
        while(extraStudents--){
            pair<int,int> cur = maxHeap.top(); 
            maxHeap.pop();
            cur.first++;
            cur.second++;
            maxHeap.push(cur);
        }
        
        while(!maxHeap.empty()){
            pair<int,int> cur = maxHeap.top(); 
            maxHeap.pop();
            res += cur.first / (double) cur.second;
        }
        
        cout << " ";
        return res / (double) classes.size();
    }
};

