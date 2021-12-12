//You are given a 0-indexed string s that you must perform k replacement operati
//ons on. The replacement operations are given as three 0-indexed parallel arrays,
// indices, sources, and targets, all of length k. 
//
// To complete the ith replacement operation: 
//
// 
// Check if the substring sources[i] occurs at index indices[i] in the original 
//string s. 
// If it does not occur, do nothing. 
// Otherwise if it does occur, replace that substring with targets[i]. 
// 
//
// For example, if s = "abcd", indices[i] = 0, sources[i] = "ab", and targets[i]
// = "eee", then the result of this replacement will be "eeecd". 
//
// All replacement operations must occur simultaneously, meaning the replacement
// operations should not affect the indexing of each other. The testcases will be 
//generated such that the replacements will not overlap. 
//
// 
// For example, a testcase with s = "abc", indices = [0, 1], and sources = ["ab"
//,"bc"] will not be generated because the "ab" and "bc" replacements overlap. 
// 
//
// Return the resulting string after performing all replacement operations on s.
// 
//
// A substring is a contiguous sequence of characters in a string. 
//
// 
// Example 1: 
//
// 
//Input: s = "abcd", indices = [0, 2], sources = ["a", "cd"], targets = ["eee", 
//"ffff"]
//Output: "eeebffff"
//Explanation:
//"a" occurs at index 0 in s, so we replace it with "eee".
//"cd" occurs at index 2 in s, so we replace it with "ffff".
// 
//
// Example 2: 
//
// 
//Input: s = "abcd", indices = [0, 2], sources = ["ab","ec"], targets = ["eee","
//ffff"]
//Output: "eeecd"
//Explanation:
//"ab" occurs at index 0 in s, so we replace it with "eee".
//"ec" does not occur at index 2 in s, so we do nothing.
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 1000 
// k == indices.length == sources.length == targets.length 
// 1 <= k <= 100 
// 0 <= indexes[i] < s.length 
// 1 <= sources[i].length, targets[i].length <= 50 
// s consists of only lowercase English letters. 
// sources[i] and targets[i] consist of only lowercase English letters. 
// 
// Related Topics Array String Sorting 
// 👍 592 👎 639


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: sorting
 * time: O(nlogn)
 * space: O(n)
 * */
class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        vector<pair<int, vector<string>>> idx_src_dst;
        int n = indices.size();

        for (int i = 0; i < n; i++) {
            idx_src_dst.push_back({indices[i], {sources[i], targets[i]}});
        }

        sort(idx_src_dst.rbegin(), idx_src_dst.rend());

        string res = "";
        for (int i = 0; i < n; i++) {
            int idx = idx_src_dst[i].first;
            string src = idx_src_dst[i].second[0];
            string dst = idx_src_dst[i].second[1];
            if (s.substr(idx, src.size()) == src) {
                s = s.substr(0, idx) + dst + s.substr(idx + src.size());
            }
        }

        return s;
    }
};

/*
 * solution 2: treemap
 * time: O(nlogn)
 * space: O(n)
 * */
class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        map<int, int, greater<int>> m; // treemap降序排序，{target index, iteration index}
        for (int i = 0; i < indices.size(); i++) {
            m[indices[i]] = i;
        }

        for (const auto& a : m) {
            int i = a.first;
            string src = sources[a.second], dst = targets[a.second];
            if (s.substr(i, src.size()) == src) {
                s = s.substr(0, i) + dst + s.substr(i + src.size());
            }
        }

        return s;
    }
};


/*
 * solution 3: hash table, optimal
 * time: O(n)
 * space: O(n)，虽然这里也是O(n)，但是因为排除了不满足条件的cases，实际上更省空间
 * */
class Solution {
public:
    string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        string res = "";
        unordered_map<int, int> m;

        // 只有满足替换条件的idx才会被加入哈希表中
        for (int i = 0; i < indexes.size(); ++i) {
            if (S.substr(indexes[i], sources[i].size()) == sources[i]) {
                m[indexes[i]] = i;
            }
        }

        /* 如果哈希表中有这个i，表示满足替换条件，所以要想着怎么替换
            m[i]可以得到原始数组中的下标，即可得到替换代词targets[m[i]]，以及原子串长度sorces[m[i]]
            把替换目标加到结果res中，同时指针以原子串长度递增。
            如果没有这个i，则把原始字符加入res中即可。
        */
        for (int i = 0; i < S.size();) {
            if (m.count(i)) {
                res += targets[m[i]];
                i += sources[m[i]].size();
            } else {
                res.push_back(S[i]);
                ++i;
            }
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
