/*
time: O(n)
space: O(1)
*/

class Solution {
public:
    int totalMoney(int n) {       
        int cur = 6;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (i % 7 == 0) cur -= 5;
            else cur++;
            ans += cur;
        }
        return ans;
    }  
};