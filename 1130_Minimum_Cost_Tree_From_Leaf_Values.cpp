class Solution {
public:
int f[50][50],maxVal[50][50];
    int mctFromLeafValues(vector<int>& arr) {
      int n = arr.size();

      for(int i = 0; i < n; i ++){
          for(int j = 0; j < n; j ++){
              f[i][j] = INT_MAX;
              maxVal[i][j] = INT_MIN;
              for(int k = i; k <= j; k ++) maxVal[i][j] = max(maxVal[i][j],arr[k]);
          }
      }
       return dp(0, n - 1,arr);
    }
    int dp(int x, int y, vector<int>&arr){
        if(f[x][y] != INT_MAX) return f[x][y];
        if(x == y){
            return f[x][y] = 0;
        }
        for(int i = x; i <= y - 1; i ++){
            f[x][y] = min(f[x][y], dp(x,i,arr) + dp(i+1,y,arr) + maxVal[x][i] * maxVal[i+1][y]);
        }
        return f[x][y];
    }
};
