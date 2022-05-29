//Write a function to find the longest common prefix string amongst an array of 
//strings. 
//
// If there is no common prefix, return an empty string "". 
//
// 
// Example 1: 
//
// 
//Input: strs = ["flower","flow","flight"]
//Output: "fl"
// 
//
// Example 2: 
//
// 
//Input: strs = ["dog","racecar","car"]
//Output: ""
//Explanation: There is no common prefix among the input strings.
// 
//
// 
// Constraints: 
//
// 
// 1 <= strs.length <= 200 
// 0 <= strs[i].length <= 200 
// strs[i] consists of only lower-case English letters. 
// 
// Related Topics String 
// 👍 5068 👎 2417


//leetcode submit region begin(Prohibit modification and deletion)

/*
 * solution 1: brute force
 * time: O(n*L)
 * space: O(1)
 * */
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty() || strs.size() == 0) {
            return "";
        }

        for (int i = 0; i < strs[0].length(); i++) {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (i == strs[j].size() || strs[j][i] != c) {
                    return strs[0].substr(0, i);
                }
            }
        }

        return strs[0];
    }
};



/*
 * solution 2: brute force
 * time: O(n*L)
 * space: O(1)
 * */
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty() || strs.size() == 0) {
            return "";
        }

        int res = INT_MAX;
        for (int i = 1; i < strs.size(); i++) {
            int end = INT_MIN;
            int len = min(strs[i].size(), strs[i - 1].size());

            for (int j = 0; j < len; j++) {
                if (strs[i][j] == strs[i - 1][j]) {
                    end = j;
                }
                else {
                    break;
                }
            }

            if (end == INT_MIN) {
                res = 0;
            }
            else {
                res = min(res, end + 1);
            }
        }

        return res == 0 ? "" : strs[0].substr(0, res);
    }
};


/*
 * solution 3: brute force
 * time: O(n*L)
 * space: O(1)
 * */
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int len = 300;
        for (auto &str : strs)
        {
            int size = str.size();
            len = min(size, len);
        }

        string res = "";
        for (int i = 0; i < len; ++i)
        {
            bool flag = true;
            char c = strs[0][i];
            for (auto &str : strs)
            {
                if (str[i] == c) continue;
                flag = false;
                break;
            }
            if (flag) res.push_back(c);
            else break;
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
