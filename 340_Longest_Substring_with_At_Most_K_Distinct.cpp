/*
solution: two pointers + sliding window
time: O(n), because we traverse the string
space: O(1), the visited array is constant space
*/

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int res = 0;
        if (s.empty() || s.size() == 0)
            return res;
        
        int left = 0, right = 0, n = s.size(), count = 0;
        int visited[256] = {0};
        
        // sliding window + two pointers
        while (right < n) {
            if (visited[s[right]] == 0)
                ++count;
            ++visited[s[right]];
            
            // move the window
            while (count > k) {
                --visited[s[left]];
                if (visited[s[left++]] == 0) 
                    --count;
            }
            res = max(res, right - left + 1);
            ++right;
        }
        return res;
    }
};