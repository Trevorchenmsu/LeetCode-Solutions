/*
solution: treemap
time: O(nlogn)
space: O(n)
*/

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.empty() || nums.size() == 0)
            return false;
        
        map<int, int> freq;
        for (int num : nums) 
            ++freq[num];
        
        auto iter = freq.begin();
        while (iter != freq.end()) {
            int num = iter->first;
            int cnt = iter->second;
            
            if (cnt == 0) {
                ++iter;
                continue;
            }
            
            freq[num]--;
            
            for (int i = 1; i < k ; ++i) {
                if (!freq.count(num + i) || freq[num + i] == 0)
                    return false;
                freq[num + i]--;
            }
            if (cnt == 0)
                iter++; 
        }
        return true;
    }
};