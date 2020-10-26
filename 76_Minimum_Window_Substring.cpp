/*
solution 1: sliding window
time: O(n), n is the length of string s
space: O(n)
*/
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> counter_s, counter_t;
        // initialize the counter in string t
        for (char ch : t) {
            ++counter_t[ch];
        }
        
        int left = 0, valid = 0, start = -1, min_len = INT_MAX;
        
        for (int right = 0; right < s.size(); ++right) {
            char ch = s[right];
            if (counter_t.count(ch)) {
                ++counter_s[ch];
                if (counter_s[ch] == counter_t[ch]) {
                    ++valid;
                }
            }
                
            while (valid == counter_t.size()) {
                // update the minimum length
                if (right - left < min_len) {
                    start = left;
                    min_len = right - left;
                }
                char left_ch = s[left];
                ++left;
                if (counter_t.count(left_ch)) {
                    if (counter_s[left_ch] == counter_t[left_ch]) {
                        --valid;
                    }
                    --counter_s[left_ch];
                }
            }
        }
        return start == -1 ? "" : s.substr(start, min_len + 1);        
    }
};

/*
solution 2: optimized sliding window
time: O(n)
space: O(1)
*/
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> count(128);
        for (char ch : t) {
            ++count[ch];
        }
        int start = 0, len = t.size(), min_len = INT_MAX;
        for (int left = 0, right = 0; right < s.size(); ++right) {
            char ch = s[right];
            if (count[ch]-- > 0) {
                --len;
            }            
            while (len == 0) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    start = left;
                }
                if (++count[s[left++]] > 0) {
                    ++len;
                }
            }
        }        
        return min_len == INT_MAX ? "" : s.substr(start, min_len);
    }
};