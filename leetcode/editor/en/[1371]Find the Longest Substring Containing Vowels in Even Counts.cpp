//Given the string s, return the size of the longest substring containing each v
//owel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear a
//n even number of times. 
//
// 
// Example 1: 
//
// 
//Input: s = "eleetminicoworoep"
//Output: 13
//Explanation: The longest substring is "leetminicowor" which contains two each 
//of the vowels: e, i and o and zero of the vowels: a and u.
// 
//
// Example 2: 
//
// 
//Input: s = "leetcodeisgreat"
//Output: 5
//Explanation: The longest substring is "leetc" which contains two e's.
// 
//
// Example 3: 
//
// 
//Input: s = "bcbcbc"
//Output: 6
//Explanation: In this case, the given string "bcbcbc" is the longest because al
//l vowels: a, e, i, o and u appear zero times.
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 5 x 10^5 
// s contains only lowercase English letters. 
// 
// Related Topics String 
// 👍 655 👎 28


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int findTheLongestSubstring(string s) {
        vector<int>count(5,0);
        unordered_map<int,int>Map;
        Map[0] = -1;

        int ret = 0;

        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='a')
                count[0] = (count[0]+1)%2;
            if (s[i]=='e')
                count[1] = (count[1]+1)%2;
            if (s[i]=='i')
                count[2] = (count[2]+1)%2;
            if (s[i]=='o')
                count[3] = (count[3]+1)%2;
            if (s[i]=='u')
                count[4] = (count[4]+1)%2;

            int code = 0;
            for (int i=0; i<5; i++)
                code = code*2 + count[i];

            if (Map.find(code)!=Map.end())
                ret = max(ret, i-Map[code]);
            else
                Map[code] = i;
        }

        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
