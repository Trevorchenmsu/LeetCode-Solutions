/*
solution: frequency 
time: O(n)
space: O(n)
*/
class Solution {
public:
    int countBinarySubstrings(string s) {
        vector<int> cnts;
        int cnt = 0;
        char pre = s[0];
        for (int i = 0; i < s.size(); i++) {
            cnt++;
            if (s[i] != pre) {
                cnt--;
                pre = s[i];
                cnts.push_back(cnt);
                cnt = 1;
            }
        }
        cnts.push_back(cnt);
        int res = 0;
        for (int i = 1; i < cnts.size(); i++) {
            res += min(cnts[i], cnts[i - 1]);
        }
        
        return res;
    }
};