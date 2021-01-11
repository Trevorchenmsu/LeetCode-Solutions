/*
time: O(n)
space: O(1)
*/
class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        vector<int> res(1, first);
        
        for (int e : encoded) { 
             res.push_back(first ^= e); 
        }

        return res;
    }
};

