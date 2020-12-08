/*
solution: binary
time: O(log(dividend/divisor))
space: O(1)
*/


class Solution {
public:
    int divide(int dividend, int divisor) {
        int sign = 1;
        if ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0))
            sign = -1;
        long ldividend = abs((long) dividend);
        long ldivisor = abs((long) divisor);
        if (ldividend == 0 || ldividend < ldivisor)
            return 0;
        long lres = divide(ldividend, ldivisor);
        
        int res = 0;
        if (lres > INT_MAX) {
            res = (sign == 1) ? INT_MAX : INT_MIN;
        } else res = (int) (lres * sign);
        return res;
    }
    
    long divide(long dividend, long divisor) {
       if(dividend < divisor) return 0;
        long sum = divisor;
        long multiple = 1;
        while((sum + sum) < dividend){
            sum += sum;
            multiple += multiple;
        }
        return multiple + divide(dividend - sum, divisor);
    }
};

    
