/*
solution: sliding window
time: O(l1 + 26 * (l2 -l1)), l1 is the length of s1, l2 is the length of l2.
space: O(1), we use two arrays to store the state, but its length is 26, so it can be considered constant.

*/
class Solution {
public:
    bool checkInclusion(string &s1, string &s2) {
        if (s1.size() > s2.size())
            return false;
        
        int s1_map[26] = {0};
        int s2_map[26] = {0};
        
        for (int i = 0; i < s1.size(); ++i) {
            ++s1_map[s1[i] - 'a'];
            ++s2_map[s2[i] - 'a'];
        }
        
        for (int i = 0; i < s2.size() - s1.size(); ++i) {
            if (match(s1_map, s2_map)) {
                return true;
            }
            ++s2_map[s2[i + s1.size()] - 'a'];
            --s2_map[s2[i] - 'a'];
        }
        return match(s1_map, s2_map);
    }
private:
    bool match(int* s1_map, int* s2_map) {
        for (int i = 0; i < 26; ++i) {
            if (s1_map[i] != s2_map[i])
                return false;
        }
        return true;
    }
};
