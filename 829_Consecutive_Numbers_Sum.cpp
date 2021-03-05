/*
solution: math
time: O(n)
space: O(1)
*/
class Solution {
public:
    int consecutiveNumbersSum(int N) {
        int res = 0;
        
        for (int i = 1; N > 0;  i++) {
            res += (N % i == 0);
            N -= i;
        }
        
        return res;
    }
};
