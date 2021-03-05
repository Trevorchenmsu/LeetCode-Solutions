/*
solution 1: dp
time: O(n)
space: O(n)
*/
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        
        int n = s.length();
        vector<int> dp(n + 1);
        dp[0] = 1;
        
        for (int i = 1; i < dp.size(); i++) {
            dp[i] = s[i - 1] == '0' ? 0 : dp[i - 1];
            if (i > 1 && (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6')))
                dp[i] += dp[i-2];
        }
        
        return dp[n];
    }
};



/*
solution 2: dp
time: O(n)
space: O(n)
*/
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty()) return 0;
        
        int len = s.length();
        vector<int> dp(len);
        dp[0] = s[0] == '0' ? 0 : 1; 
        
        for (int i = 1; i < len; i++) {
            int first = stoi(s.substr(i, 1));
            int second = stoi(s.substr(i - 1, 2));
            if (first >= 1 && first <= 9)
                dp[i] += dp[i - 1];
            if (second >= 10 && second <= 26)
                dp[i] += i >= 2 ? dp[i - 2] : 1;
        }
        
        return dp[len - 1];
    }
};


/*
solution 3: dp
time: O(n)
space: O(1)
*/

class Solution {
public:
    int numDecodings(string s) {
        if(s.empty()) return 0;
        int prev = 0;
        int cur = 1;
        
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '0'){
                cur = 0;
            }
            if(i == 0 || !(s[i-1] == '1' || (s[i-1] == '2' && s[i] <= '6'))){
                prev = 0;
            }
            
            int tmp = cur;
            cur += prev;
            prev = tmp;
        }
        
        return cur;
    }
};