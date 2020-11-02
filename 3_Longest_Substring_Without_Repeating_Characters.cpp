/*
solution: sliding window + two pointers
time: O(n), we traverse the whole string
space: O(n), worst case: all the characters are different.
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        if (s.empty() || s.size() == 0)
            return res;
        
        unordered_set<int> set;
        int left = 0, right = 0;
        while (right < s.size()) {
            if (!set.count(s[right])) {
                set.insert(s[right++]);
                res = max(res, right - left);
            } else {
                auto iter = set.find(s[left++]);
                set.erase(iter);
            }
        }
        
        return res;
    }
};

