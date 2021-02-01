/*
solution: sliding window + two pointers
time: O(n), we traverse the whole string
space: O(n), worst case: all the characters are different.
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) return 0;
        int res = INT_MIN;
        unordered_set<char> Set;
        int left = 0, right = 0;
        
        while (right < s.size()) {
            if (Set.find(s[right]) == Set.end()) {
                Set.insert(s[right++]);
                res = max(res, right - left);
            }
            else {
                auto left_boundary = Set.find(s[left++]);
                Set.erase(left_boundary);
            }
        }
        
        return res;
    }
};
