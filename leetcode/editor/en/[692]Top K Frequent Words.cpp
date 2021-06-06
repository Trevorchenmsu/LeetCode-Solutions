//Given a non-empty list of words, return the k most frequent elements. 
// Your answer should be sorted by frequency from highest to lowest. If two word
//s have the same frequency, then the word with the lower alphabetical order comes
// first. 
//
// Example 1: 
// 
//Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
//Output: ["i", "love"]
//Explanation: "i" and "love" are the two most frequent words.
//    Note that "i" comes before "love" due to a lower alphabetical order.
// 
// 
//
// Example 2: 
// 
//Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"]
//, k = 4
//Output: ["the", "is", "sunny", "day"]
//Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
//    with the number of occurrence being 4, 3, 2 and 1 respectively.
// 
// 
//
// Note: 
// 
// You may assume k is always valid, 1 ≤ k ≤ number of unique elements. 
// Input words contain only lowercase letters. 
// 
// 
//
// Follow up: 
// 
// Try to solve it in O(n log k) time and O(n) extra space. 
// 
// Related Topics Hash Table Heap Trie 
// 👍 3095 👎 202


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: min heap + hash table + comparator
 * time: O(nlogk)
 * space: O(n)
 *
 * */
class Solution {
public:
    struct cmp {
        bool operator() (pair<string, int> &p1, pair<string, int> &p2) {
            return p1.second > p2.second || (p1.second == p2.second && p1.first < p2.first);
        }
    };

    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> cnts; // O(n)
        priority_queue<pair<string, int>, vector<pair<string, int>>, cmp> pq; // O(k)

        for (const auto &word : words) { // O(n)
            cnts[word]++;
        }

        for (const auto cnt : cnts) { // O(nlogk)
            pq.push(cnt);
            if (pq.size() > k) pq.pop();
        }

        vector<string> res(k);
        for (int i = res.size() - 1; i >= 0; i--) { // O(klogk)
            res[i] = pq.top().first; pq.pop();
        }

        return res;
    }
};

/*
 * solution : bucket sort + hash table + tree set
 * time: O(nlogk)
 * space: O(n)
 *
 * */

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> res;
        unordered_map<string, int> cnts;

        // bucket sort
        int n = words.size();
        // 桶的数量由unique单词数量决定，即最大频率也只能是n，考虑0 index-based，需要创建n+1的桶数量
        vector<set<string>> buckets (n + 1);

        for (auto &word : words)
            cnts[word]++;

        // 每个桶的index为频率值，桶内装的是具有相同频率的单词，因为采用set，会自动把单词按字母大小递增排序。
        for (auto &cnt : cnts)
            buckets[cnt.second].insert(cnt.first);

        /*
         * 倒序考虑桶的分布，因为答案需要先添加高频单词。这里需要把同频率的单词集合转为vector，因为set不具有index功能，
         * 所以在下面迭代器中无法使用+k等设定迭代器范围。当k大于等于当前频率单词集合个数时，表示包括整个集合后k仍有剩余，所以把整
         * 个集合都插在res后面。当k小于集合个数时，表示我们不需要整个集合的元素，只需要集合中的前k个元素。
         * */
        for (int i = buckets.size() - 1; i >= 0; i--) {
            if (k <= 0) break;
            vector<string> words_same_cnt(buckets[i].begin(), buckets[i].end());
            if (k >= buckets[i].size())
                res.insert(res.end(), words_same_cnt.begin(), words_same_cnt.end());
            else
                res.insert(res.end(), words_same_cnt.begin(), words_same_cnt.begin() + k);
            k -= Words_same_cnt.size();
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
