/*
solution: sweep line
time: O(n)
space: O(1)
*/
class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        vector<vector<int>> res;
        if (intervals.empty() || intervals[0].empty())
            return res;
        
        int i = 0, n = intervals.size();
        int B_s = toBeRemoved[0], B_e = toBeRemoved[1];
        
        for (const auto &interval : intervals) {
            int A_s = interval[0], A_e = interval[1];
            
            // no intersection
            if (A_e < B_s || A_s > B_e) 
                res.push_back({A_s, A_e});
            else  
            {
                if (A_s < B_s) 
                    res.push_back({A_s, B_s});
                    
                if (A_e > B_e) 
                    res.push_back({B_e, A_e});
            } 
        }
        
        return res;
    }
};



