//Given a string s. An awesome substring is a non-empty substring of s such that
// we can make any number of swaps in order to make it palindrome. 
//
// Return the length of the maximum length awesome substring of s. 
//
// 
// Example 1: 
//
// 
//Input: s = "3242415"
//Output: 5
//Explanation: "24241" is the longest awesome substring, we can form the palindr
//ome "24142" with some swaps.
// 
//
// Example 2: 
//
// 
//Input: s = "12345678"
//Output: 1
// 
//
// Example 3: 
//
// 
//Input: s = "213123"
//Output: 6
//Explanation: "213123" is the longest awesome substring, we can form the palind
//rome "231132" with some swaps.
// 
//
// Example 4: 
//
// 
//Input: s = "00"
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 10^5 
// s consists only of digits. 
// 
// Related Topics String Bit Manipulation 
// 👍 345 👎 8


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int longestAwesome(string s)
    {
        vector<int>count(10,0);
        int n = s.size();
        s="#"+s;

        unordered_map<int,int>Map;
        Map[0] = 0;
        int ret = 0;

        for (int i=1; i<=n; i++)
        {
            count[s[i]-'0']+=1;
            int key = makeKey(count);

            if (Map.find(key)!=Map.end())
                ret = max(ret, i - Map[key]);

            for (int k=0; k<10; k++)
            {
                int newKey = key;

                if (((key>>k)&1)==0)
                    newKey |= (1<<k);
                else
                    newKey -= (1<<k);

                if (Map.find(newKey)!=Map.end())
                    ret = max(ret, i - Map[newKey]);
            }
            if (Map.find(key)==Map.end()) Map[key] = i;
        }

        return ret;
    }

    int makeKey(vector<int>&count)
    {
        int key=0;
        for (int i=0; i<10; i++)
        {
            if (count[i]%2==0)
                key+=(0<<i);
            else
                key+=(1<<i);
        }
        return key;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
