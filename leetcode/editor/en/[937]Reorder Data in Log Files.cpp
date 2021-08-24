//You are given an array of logs. Each log is a space-delimited string of words,
// where the first word is the identifier. 
//
// There are two types of logs: 
//
// 
// Letter-logs: All words (except the identifier) consist of lowercase English l
//etters. 
// Digit-logs: All words (except the identifier) consist of digits. 
// 
//
// Reorder these logs so that: 
//
// 
// The letter-logs come before all digit-logs. 
// The letter-logs are sorted lexicographically by their contents. If their cont
//ents are the same, then sort them lexicographically by their identifiers. 
// The digit-logs maintain their relative ordering. 
// 
//
// Return the final order of the logs. 
//
// 
// Example 1: 
//
// 
//Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","le
//t3 art zero"]
//Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig
//2 3 6"]
//Explanation:
//The letter-log contents are all different, so their ordering is "art can", "ar
//t zero", "own kit dig".
//The digit-logs have a relative order of "dig1 8 1 5 1", "dig2 3 6".
// 
//
// Example 2: 
//
// 
//Input: logs = ["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act z
//oo"]
//Output: ["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"]
// 
//
// 
// Constraints: 
//
// 
// 1 <= logs.length <= 100 
// 3 <= logs[i].length <= 100 
// All the tokens of logs[i] are separated by a single space. 
// logs[i] is guaranteed to have an identifier and at least one word after the i
//dentifier. 
// 
// Related Topics String 
// 👍 1038 👎 2830


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sort
 * time: O(nlogn)
 * space: O(n)
 *
 * */
class Solution {
public:
    static bool cmp (const vector<string> &s1, const vector<string> &s2) {
        return s1[1] == s2[1] ? s1[0] < s2[0] : s1[1] < s2[1];
    }

    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> res;
        if (logs.empty() || logs.size() == 0) {
            return res;
        }

        vector<string> digits;
        vector<vector<string>> letters;

        for (const auto &log : logs) {
            int i = log.find_first_of(' ');
            if (isalpha(log[i + 1])) {
                letters.push_back({log.substr(0, i), log.substr(i + 1)});
            }
            else {
                digits.push_back(log);
            }
        }

        sort(letters.begin(), letters.end(), cmp);

        for (const auto &letter : letters) {
            res.push_back(letter[0] + " " + letter[1]);
        }

        for (const auto &digit : digits) {
            res.push_back(digit);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
