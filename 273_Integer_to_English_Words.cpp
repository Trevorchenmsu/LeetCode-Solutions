/*
solution: dfs
time: O(n), Intuitively the output is proportional to the number N of digits in the input.
space: O(1)
*/

class Solution {
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        string res = "";
        int i = 0;
        while (num > 0) {
            if (num % 1000 != 0) {
                res = dfs(num % 1000) + thousands[i] + " " + res;
            }
            num /= 1000;
            ++i;
        }
        res.erase(0, res.find_first_not_of(" "));
        res.erase(res.find_last_not_of(" ") + 1);
        return res;
    }
private:
    string dfs(int num) {
        if (num == 0)
            return "";
        if (num < 20) {
            return less20[num] + " ";
        } else if (num < 100) {       
            return tens[num / 10] + " " + dfs(num % 10);
        } else {
            return less20[num / 100] + " Hundred " + dfs(num % 100);
        }  
    }
    
    vector<string> less20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
                    "Nine", "Ten", "Eleven", "Twelve", "Thirteen","Fourteen","Fifteen",
                   "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> tens = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty","Seventy",
                       "Eighty", "Ninety"};
    vector<string> thousands = {"", "Thousand", "Million", "Billion"};
};

