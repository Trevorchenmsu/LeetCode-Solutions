class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char, int> map;
        int i = 0, j = 0, res = 0;
        while(i < s.length()){
            map[s[i]]++;
            while(map.size() > 2){
                map[s[j]]--;
                if(map[s[j]] == 0) map.erase(s[j]);
                j++;
            }
            res = max(res, i - j + 1);
            i++;
        }
        return res;
    }
};