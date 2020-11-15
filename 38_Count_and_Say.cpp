/*
solution: brute force
time: O(2^n)
space: O(2^n)
*/
class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) return "1";
        string s = countAndSay(n-1);
        string res; 
        char cur = s[0];
        int i = 0, cnt = 0;
        while(i < s.size()) {
            if(s[i] == cur) {
                ++cnt;
            } else {
                res.push_back(cnt + '0');
                res.push_back(cur);
                cnt = 1;
                cur = s[i];
            }
            ++i;
        }
        res.push_back(cnt + '0');
        res.push_back(cur);
        return res;
    }
};