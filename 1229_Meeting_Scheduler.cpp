/*
solution 1: sort + sweep line + two pointers
time: O(nlogn)
space: O(logn), stack space for sorting
*/

class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        vector<int> res;
        if (slots1.empty() || slots2.empty()) return res;
        
        int start = 0, end = 0;
        int i = 0, j = 0;
        sort(slots1.begin(), slots1.end());
        sort(slots2.begin(), slots2.end());
        
        while (i < slots1.size() && j < slots2.size()) {
            start = max(slots1[i][0], slots2[j][0]);
            end = min(slots1[i][1], slots2[j][1]);
            
            if (end > start) {
                if (end - start >= duration) {
                    res.push_back(start);
                    res.push_back(start + duration);
                    return res;
                }
                else {
                    if (slots2[j][1] < slots1[i][1]) {
                        j++;
                    } 
                    else i++;
                }
            }
            else {
                if (slots2[j][1] < slots1[i][1]) j++;
                else i++;
            }
        }
        
        return res;
    }
};


/*
solution 2: sort + sweep line + two pointers
time: O(nlogn)
space: O(logn), stack space for sorting
*/
class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        vector<int> res;
        if (slots1.empty() || slots2.empty()) return res;
        
        int start = 0, end = 0, i = 0, j = 0;
        sort(slots1.begin(), slots1.end());
        sort(slots2.begin(), slots2.end());
        
        while (i < slots1.size() && j < slots2.size()) {
            start = max(slots1[i][0], slots2[j][0]);
            end = min(slots1[i][1], slots2[j][1]);
            
            if (end - start >= duration) 
                return {start, start + duration};
            
            if (slots2[j][1] < slots1[i][1]) 
                j++;
            else i++;
        }
        
        return res;
    }
};