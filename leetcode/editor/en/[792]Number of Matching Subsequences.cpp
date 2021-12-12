//Given a string s and an array of strings words, return the number of words[i] 
//that is a subsequence of s. 
//
// A subsequence of a string is a new string generated from the original string 
//with some characters (can be none) deleted without changing the relative order o
//f the remaining characters. 
//
// 
// For example, "ace" is a subsequence of "abcde". 
// 
//
// 
// Example 1: 
//
// 
//Input: s = "abcde", words = ["a","bb","acd","ace"]
//Output: 3
//Explanation: There are three strings in words that are a subsequence of s: "a"
//, "acd", "ace".
// 
//
// Example 2: 
//
// 
//Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
//Output: 2
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 5 * 104 
// 1 <= words.length <= 5000 
// 1 <= words[i].length <= 50 
// s and words[i] consist of only lowercase English letters. 
// 
// Related Topics Hash Table String Trie Sorting 
// 👍 2255 👎 126


//leetcode submit region begin(Prohibit modification and deletion)

/*
 * 暴力法：遍历单词数组的每个单词的每个字符，需要O(n*L),用角标记录，再每次从角标遍历s，判定字符是否存在
 * 总体时间复杂度为(n*L*m)，而题目中m高达10^5，所以优化方向就是是遍历s这一部分进行考虑
 * */

/*
 * solution 1: binary search
 * time: O(n*L*logm)，n为单词个数，L为最大单词长度，m为原始字符串长度
 * space: O(1)
 * */
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        //处理字符串，类似哈希表存储，key为字符串中的字符，value存改字符在字符串中的下标。
        auto char_index = vector<vector<int>> (26);
        for (int i = 0; i < s.size(); ++i)
        {
            char_index[s[i] - 'a'].push_back(i);
        }

        int count = 0;
        //谷歌面经中要求获得所有满足的单词，所以这里可以建立vector存结果
        // vector<string> res;
        for (auto word : words)
        {
            // 如果单词长度比原始字符串还长，肯定不是子序列
            if (word.size() > s.size())  continue;
            if (check(word, char_index)) count++;
            // res.push_back(word);
        }

        return count;
        // return res;
    }

    /*
     * 对单词数组中的每个单词每个字符在s中进行查找。经过上述处理，在s中查找变成二分查找。
     * 我们采用了ch-’a'，这样就可以在s中具体查找ch的位置。因为所有index都有序的存在vector中
     * 所以可以直接用二分法查找。为了使在上一个查找的位置继续寻找子序列，用i进行指针跟踪。
     * */
    bool check(string word, vector<vector<int>>& table) {
        int i = 0;
        for (auto ch : word)
        {
//            auto indices = table[ch - 'a']; 不能采用这一步，因为赋值操作也算了时间，
//            如果每个字符都这样赋值，时间就很高了，从而导致TLE
            auto iter = lower_bound(table[ch - 'a'].begin(), table[ch - 'a'].end(), i);
            if (iter == table[ch - 'a'].end()) return false;
            i = *iter + 1;
        }

        return true;
    }
};


/*
 * solution 2: state machine
 * time: O(m+nL)，n为单词个数，L为最大单词长度，m为字符串长度
 * space: O(m)
 * */
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int m = s.size();
        /*
         next[i][ch]表示在s中位置i时，从i的右边看过去，第一个ch在s中的位置
         next[9][a]
         next[9][b]
         next[9][c]
         next[9][d]
         ...
         next[9][z]
        */
        vector<vector<int>> next(m + 1, vector<int> (26, -1));
        s = '#' + s;// 方便后面s取index操作

        for (int i = m; i >= 1; i--) // O(26m)
        {
            for (int j = 0; j < 26; j++)
            {
                //从末端开始考虑，先把后面的状态赋给前面的。根据具体情况再更新前面的
                next[i - 1][j] = next[i][j];
            }
            //这里表示从i-1位置往右看，当前的s[i]字符处于字符串s中的位置i
            next[i - 1][s[i] - 'a'] = i;
        }

        int res = 0;
        for (auto word : words) // O(nL)
        {
            // 这里另i=0表示从s的第一个位置开始往右边看过去，
            // 如果word的第一个字符在s中的话，下面的i肯定不是-1
            int i = 0, flag = 1;
            for (auto ch : word)
            {
                i = next[i][ch - 'a']; // 因为要查后序的位置，所以要更新i作为跟踪指针
                if (i == -1)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag) res++;
        }

        return res;
    }
};




//leetcode submit region end(Prohibit modification and deletion)
