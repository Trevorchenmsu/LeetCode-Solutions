/*
solution 1: backtrack
time: O(n*2^n), the number of valid permutation
space: O(n), the deepest recursion tree is n. visited array is also O(n)
*/
class Solution {
public:
    int countArrangement(int n) {
        int res = 0;
        vector<int> visited (n + 1, 0);
        backtrack(res, n, 1, visited);
        return res;
    }
    
    void backtrack(int &res, int n, int pos, vector<int> &visited) {
        if (pos > n) 
            res++;
        
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && (pos % i == 0 || i % pos == 0)) {
                visited[i] = 1;
                backtrack(res, n, pos + 1, visited);
                visited[i] = 0;
            }
        }
    }
};
/*
solution 2: dp + bit manipulation, better
time: O(n*2^n), the number of valid permutation
space: O(n), the deepest recursion tree is n. visited array is also O(n)
*/
class Solution {
public:
    int countArrangement(int N) {
        vector<int> dp(1 << N,0);
        
        // each number can be placed in the first position
        for(int i = 0;i < N;++i)
            dp[1 << i] = 1;
        
        for(int i = 0;i < (1 << N);++i) {
            int index = 1;
            int temp = i;
            
            //count the number of 1
            while(temp) {
                temp &= temp-1;
                ++index;
            }
            
            for(int j = 0;j < N;++j) {
                // binary number is 0 (unselected), can only be placed in index_th position
                if(!(i & (1 << j)) && ((j+1) % index == 0 || index % (j+1) == 0))
                    dp[1 << j | i] += dp[i];
            }
        }
        
        return dp[(1 << N) -1];
    }
};
