/*
solution: strint/num manuplation
time: O(n)
space: O(1)
*/

class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        int i = num1.length() - 1, j = num2.length() - 1;
        int sum = 0;
        while (i >= 0 && j >= 0) {
            sum += (num1[i--] - '0') + (num2[j--] - '0');
            res += (sum % 10 + '0');
            sum /= 10;
        }
        
        while (i >= 0) {
            sum += num1[i--] - '0';
            res += (sum % 10 + '0');
            sum /= 10;
        }
        
        while (j >= 0) {
            sum += num2[j--] - '0';
            res += (sum % 10 + '0');
            sum /= 10;
        }
        
        if (sum > 0)
            res += sum + '0';
        
        reverse(res.begin(), res.end());
        
        return res;
    }
};