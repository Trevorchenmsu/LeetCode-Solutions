/*
solution 1: divide and conquer
time: O(M×N)
The time complexity for a recursive solution is defined by two things: 
the number of recursive calls that we make and the time it takes to process a single call.
all we are doing in the function is to check the dictionary for a key, 
and then we make a couple of function calls. So the time it takes to process a single call is actually O(1).
The number of unique recursive calls is defined by the two state variables that we have. 
Potentially, we can make O(M×N) calls where M and N represent the lengths of the two strings. 
Thus, the time complexity for this solution would be O(M×N).
space: O(M×N) for total, O(M) for stack space
The maximum space is utilized by the dictionary that we are using and the size of that dictionary 
would also be controlled by the total possible combinations of i and j which turns out to be O(M×N) as well. 
We also have the space utilized by the recursion stack which is O(M) where MM is the length of string S. 
This is because in one of our recursion calls, we don't progress at all in the string T. 
Hence, we would have a branch in the tree where only the index i progresses one step until it 
reaches the end of string S. The number of nodes in this branch would be equal to the length of string S.
*/
class Solution {
public:
    int numDistinct(string s, string t) {
        // divide conquer
        unordered_map<string, int> countMap;
        return divideConquer(s, 0, t, 0, countMap);
    }
    
    int divideConquer(string& s, int s_start, string& t, int t_start, unordered_map<string, int>& countMap) {
        if (t_start == t.size()) // t is empty string
            return 1;
        
        if (s_start == s.size()) // s is empty string
            return 0;
        
        int count = 0;
        string state = to_string(s_start) + "@" + to_string(t_start);
        
        if (countMap.find(state) != countMap.end())
            return countMap[state];
        
        if (s[s_start] == t[t_start]) {
            count = divideConquer(s, s_start + 1, t, t_start + 1, countMap) + 
                    divideConquer(s, s_start + 1, t, t_start, countMap);
        }
        else count = divideConquer(s, s_start + 1, t, t_start, countMap);
        
        countMap[state] = count;
        return count;
    }
};

/*
solution 2: backtrack
time: O(M*N)
space: O(M*N)
*/
class Solution {
public:
    int numDistinct(string s, string t) {
        // backtrack
        unordered_map<string, int> countMap;
        backtrack(s, 0, t, 0, countMap);
        return count;
    }
    
private:
    int count = 0;
    void backtrack(string &s, int s_start, string &t, int t_start, unordered_map<string, int>& countMap) {
        if (t_start == t.size()) {
            count++;
            return;
        }
        
        if (s_start == s.size())
            return;
        
        string state = to_string(s_start) + "->" + to_string(t_start);
        if (countMap.find(state) != countMap.end()) {
            count += countMap[state];
            return;
        }
        
        int count_pre = count;
        if (s[s_start] == t[t_start])
            backtrack(s, s_start + 1, t, t_start + 1, countMap);
        backtrack(s, s_start + 1, t, t_start, countMap);
        
        int count_increment = count - count_pre;
        countMap[state] = count_increment;
    }
};

/*
solution 3: dp, bottom up
time: O(mn)
space: O(mn)
*/
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<long>> dp(m + 1, vector<long> (n + 1));
        
        for (int i = 0; i <= m; i++) {
            dp[i][n] = 1;
        }
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (s[i] == t[j]) {
                    dp[i][j] = dp[i + 1][j + 1] + dp[i + 1][j];
                } 
                else dp[i][j] = dp[i + 1][j];
            }
        }
        
        return (int) dp[0][0];
    }
};


/*
solution 4: dp, top down
time: O(mn)
space: O(mn)
*/
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<long>> dp(m + 1, vector<long> (n + 1));
        
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                }
                else dp[i][j] = dp[i - 1][j];
            }
        }
        
        return (int) dp[m][n];
    }
};

/*
solution 5: dp, top down + compression
time: O(mn)
space: O(n)
*/y
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<long>> dp(2, vector<long> (n + 1));
        
        for (int i = 0; i < m; i++) {
            dp[i % 2][0] = 1;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + dp[(i - 1) % 2][j];
                }
                else dp[i % 2][j] = dp[(i - 1) % 2][j];
            }
        }
        
        return (int) dp[m % 2][n];
    }
};