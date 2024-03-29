//You are given a string s and an integer k. You can choose any character of the
// string and change it to any other uppercase English character. You can perform 
//this operation at most k times. 
//
// Return the length of the longest substring containing the same letter you can
// get after performing the above operations. 
//
// 
// Example 1: 
//
// 
//Input: s = "ABAB", k = 2
//Output: 4
//Explanation: Replace the two 'A's with two 'B's or vice versa.
// 
//
// Example 2: 
//
// 
//Input: s = "AABABBA", k = 1
//Output: 4
//Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
//The substring "BBBB" has the longest repeating letters, which is 4.
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 105 
// s consists of only uppercase English letters. 
// 0 <= k <= s.length 
// 
// Related Topics Two Pointers Sliding Window 
// 👍 2406 👎 120


//Input: s = "AABABBA", k = 1
//Output: 4

//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two pointers / sliding window
 * time: O(n)
 * space:O(1)
 * */
class Solution {
public:
    int characterReplacement(string s, int k) {
        int left = 0, res = 0;
        vector<int> count(26, 0);

        for (int right = 0; right < s.size(); right++) {
            count[s[right] - 'A']++;

            while (right - left + 1 - *max_element(count.begin(), count.end()) > k) {
                count[s[left] - 'A']--;
                left++;
            }

            res = max(res, right - left + 1);
        }

        return res;
    }
};

/*
 * solution 2: two pointers / sliding window
 * time: O(n)
 * space:O(1)
 * */
class Solution {
public:
    int characterReplacement(string s, int k) {
        int left = 0, res = 0;
        vector<int> count(26, 0);

        for (int right = 0; right < s.size(); right++) {
            count[s[right] - 'A']++;
            int maxFreq = *max_element(count.begin(), count.end());

            if (right - left + 1 - maxFreq <= k) {
                res = max(res, right - left + 1);
            }
            else {
                count[s[left] - 'A']--;
                left++;
            }
        }

        return res;
    }
};

/*
 * solution 3: hash table + sliding window
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    int characterReplacement(string s, int k) {
        int res = 0, left = 0, maxFreq = INT_MIN;
        unordered_map<char, int> cnts;


        for (int right = 0; right < s.size(); right++) {
            cnts[s[right]]++;
            for (auto & cnt : cnts) {
                if (cnt.second > maxFreq) {
                    maxFreq = cnt.second;
                }
            }

            while (right - left + 1 - maxFreq > k) {
                cnts[s[left++]]--;
                for (auto & cnt : cnts) {
                    if (cnt.second > maxFreq) {
                        maxFreq = cnt.second;
                    }
                }
            }

            res = max(res, right - left + 1);
        }

        return res;
    }
};


/*
 * solution 4: sliding window, fastest
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> freqs(26, 0);
        int left = 0, res = 0, max_freq = 0;

        for(int right = 0; right < s.size(); right++) {

            int window_size = right - left + 1;

            freqs[s[right] - 'A']++;

            max_freq = max(max_freq, freqs[s[right] - 'A']);

            if(window_size - max_freq > k) {
                freqs[s[left] - 'A']--;
                left++;
            }
            else {
                res = max(res, window_size);
            }
        }

        return res;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
