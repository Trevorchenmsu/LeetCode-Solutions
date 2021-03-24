//Write a program that outputs the string representation of numbers from 1 to n.
// 
//
// But for multiples of three it should output “Fizz” instead of the number and 
//for the multiples of five output “Buzz”. For numbers which are multiples of both
// three and five output “FizzBuzz”. 
//
// Example:
// 
//n = 15,
//
//Return:
//[
//    "1",
//    "2",
//    "Fizz",
//    "4",
//    "Buzz",
//    "Fizz",
//    "7",
//    "8",
//    "Fizz",
//    "Buzz",
//    "11",
//    "Fizz",
//    "13",
//    "14",
//    "FizzBuzz"
//]
// 
// 👍 1285 👎 1491


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> res;

        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 && i % 5 != 0)
                res.push_back("Fizz");
            if (i % 3 != 0 && i % 5 == 0)
                res.push_back("Buzz");
            if (i % 3 != 0 && i % 5 != 0)
                res.push_back(to_string(i));
            if (i % 3 == 0 && i % 5 == 0)
                res.push_back("FizzBuzz");
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
