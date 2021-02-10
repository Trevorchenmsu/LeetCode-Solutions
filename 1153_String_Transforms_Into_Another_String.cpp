/*
solution: brute force
time: O(n)
space: O(26)
*/
class Solution {
public:
    bool canConvert(string str1, string str2) {
        if (str1 == str2) return true;
        unordered_map<int, int> Map;
        
        for (int i = 0; i < str1.size(); i++) {
            if (Map[str1[i]] != NULL && Map[str1[i]] != str2[i])
                return false;
            Map[str1[i]] = str2[i];
        }
        
        return set(str2.begin(), str2.end()).size() < 26;
    }
};