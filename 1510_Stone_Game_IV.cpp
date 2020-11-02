class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<int> ans(n + 1);
        ans[0] = 0;
        for(int i = 1; i <= n; i++){
            ans[i] = 0;
            for(int j = 1; j * j <= i; j++)
                if(!ans[i - j * j]){
                    ans[i] = 1;
                    break;
                }
        }
        return ans[n];
    }
};

