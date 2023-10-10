//Given a string s, rearrange the characters of s so that any two adjacent chara
//cters are not the same. 
//
// Return any possible rearrangement of s or return "" if not possible. 
//
// 
// Example 1: 
// Input: s = "aab"
//Output: "aba"
// Example 2: 
// Input: s = "aaab"
//Output: ""
// 
// 
// Constraints: 
//
// 
// 1 <= s.length <= 500 
// s consists of lowercase English letters. 
// 
// Related Topics Hash Table String Greedy Sorting Heap (Priority Queue) Countin
//g 
// 👍 4817 👎 180


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: hash table + heap
 * time: O(nlogn)
 * space: O(n)
 * */

class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> cnts;
        priority_queue<pair<int, char>> max_heap;

        for (auto ch : s)
            ++cnts[ch];

        for (auto c : cnts)
        {
            if (c.second > (s.size() + 1) / 2) return "";
            max_heap.push({c.second, c.first});
        }

        string res = "";

        while (max_heap.size() >= 2)
        {
            auto p1 = max_heap.top(); max_heap.pop();
            auto p2 = max_heap.top(); max_heap.pop();
            res.push_back(p1.second);
            res.push_back(p2.second);
            if (--p1.first > 0) max_heap.push(p1);
            if (--p2.first > 0) max_heap.push(p2);
        }

        if (max_heap.size() > 0) res.push_back(max_heap.top().second);

        return res;
    }
};

class Solution:
    def reorganizeString(self, s: str) -> str:
        cnts = defaultdict(int)
        heap = []
        res = ''
        for c in s:
            cnts[c] += 1

        for letter, cnt in cnts.items():
            if cnt > (len(s) + 1) // 2: return ''
            heap.append([-cnt, letter])

        heapify(heap)

        while len(heap) >= 2:
            p1 = heappop(heap)
            p2 = heappop(heap)

            res += p1[1]
            res += p2[1]

            p1[0] += 1
            p2[0] += 1

            if p1[0] < 0: heappush(heap, p1)
            if p2[0] < 0: heappush(heap, p2)

        if len(heap) > 0: res += heappop(heap)[1]

        return res

//leetcode submit region end(Prohibit modification and deletion)
