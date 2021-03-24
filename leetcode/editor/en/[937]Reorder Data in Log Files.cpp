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
class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> res;
        if (logs.empty()) return res;

        vector<string> digits;
        vector<pair<string, string>> letters;

        // separate the logs to digits and letters
        for (const auto& log : logs) {
            int i = log.find_first_of(' ');
            if (isalpha(log[i + 1]))
                letters.push_back(make_pair(log.substr(0, i), log.substr(i + 1)));
            else digits.push_back(log);
        }

        sort(letters.begin(), letters.end(), [](const auto& p1, const auto& p2){
            return p1.second == p2.second ? p1.first < p2.first : p1.second < p2.second;
        });

        for (auto &s : letters)
            res.push_back(s.first + " " + s.second);

        for (auto &s : digits)
            res.push_back(s);

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
