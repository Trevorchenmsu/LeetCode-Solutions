//Given an encoded string, return its decoded string. 
//
// The encoding rule is: k[encoded_string], where the encoded_string inside the 
//square brackets is being repeated exactly k times. Note that k is guaranteed to 
//be a positive integer. 
//
// You may assume that the input string is always valid; No extra white spaces, 
//square brackets are well-formed, etc. 
//
// Furthermore, you may assume that the original data does not contain any digit
//s and that digits are only for those repeat numbers, k. For example, there won't
// be input like 3a or 2[4]. 
//
// 
// Example 1: 
// Input: s = "3[a]2[bc]"
//Output: "aaabcbc"
// Example 2: 
// Input: s = "3[a2[c]]"
//Output: "accaccacc"
// Example 3: 
// Input: s = "2[abc]3[cd]ef"
//Output: "abcabccdcdcdef"
// Example 4: 
// Input: s = "abc3[cd]xyz"
//Output: "abccdcdcdxyz"
// 
// 
// Constraints: 
//
// 
// 1 <= s.length <= 30 
// s consists of lowercase English letters, digits, and square brackets '[]'. 
// s is guaranteed to be a valid input. 
// All the integers in s are in the range [1, 300]. 
// 
// Related Topics String Stack Recursion 
// 👍 6165 👎 271


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: stack, iteration
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    string decodeString(string s) {
        if (s.empty() || s.size() == 0) return "";
        stack<char> st;
        string res = "";

        for (auto i = 0; i < s.size(); ++i)
        {
            if (s[i] != ']') st.push(s[i]);
            else {
                string temp = "";
                while (!st.empty() && st.top() != '[')
                {
                    temp.push_back(st.top());
                    st.pop();
                }
                st.pop();

                int count = 0, num = 0;
                while (!st.empty() && isdigit(st.top()))
                {
                    num = num + (st.top() - '0') * pow(10, count);
                    st.pop();
                    ++count;
                }

                for (int j = 0; j < num; ++j)
                {
                    for (int k = temp.size() - 1; k >= 0; --k)
                    {
                        st.push(temp[k]);
                    }
                }
            }
        }

        while (!st.empty()) {
            res.push_back(st.top()); st.pop();
        }

        reverse(res.begin(), res.end());

        return res;
    }
};


class Solution:
    def decodeString(self, s: str) -> str:
        stack = []

        for ch in s:
            if ch == ']':
                temp = ''
                while len(stack) > 0 and stack[-1] != '[':
                    temp = stack[-1] + temp
                    stack.pop()
                stack.pop()

                cnt, num = 0, 0
                while len(stack) > 0 and stack[-1].isdigit():
                    num += int(stack[-1]) * 10 ** cnt
                    stack.pop()
                    cnt += 1

                stack.append(temp * num)
            else: stack.append(ch)

        return ''.join(stack)


/*
 * solution 2: stack, recursion
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    string decodeString(string s) {
        int idx = 0;
        return decodeRecursive(s, idx);
    }

    string decodeRecursive(string &s, int &idx) {
        string res = "";

        while (idx < s.size() && s[idx] != ']')
        {
            if (isalpha(s[idx])) res += s[idx++];
            else
            {
                int k = 0;
                while (idx < s.size() && isdigit(s[idx]))
                {
                    k = k * 10 + s[idx++] - '0';
                }

                ++idx; // skip '['

                string temp_str = decodeRecursive(s, idx);

                ++idx; // skip ']'

                for (int i = 0; i < k; ++i) res += temp_str;
            }
        }

        return res;
    }
};


class Solution:
    def decodeString(self, s: str) -> str:
        def decodeRecursive(s, idx):
            res = ''
            while idx < len(s) and s[idx] != ']':
                if s[idx].isalpha():
                    res += s[idx]
                    idx += 1
            else:
                k = 0
                while idx < len(s) and s[idx].isdigit():
                    k = k * 10 + int(s[idx])
                    idx += 1

                idx += 1
                temp_str, idx = decodeRecursive(s, idx)
                idx += 1
                res += temp_str * k

            return res, idx

    return decodeRecursive(s, 0)[0]
//leetcode submit region end(Prohibit modification and deletion)
