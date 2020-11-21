/*
solution 1: brute force
time: O(n*n/k), traverse the string once is O(n), we will only repeat n/k times.
space: O(1)
*/

class Solution {
public:
    string removeDuplicates(string s, int k) {
        int len = -1;
        while (len != s.size()) {
            len = s.size();
            int cnt = 1;
            for (int i = 0; i < s.size(); ++i) {
                if (i == 0 || s[i] != s[i - 1]) 
                    cnt = 1;
                else if (++cnt == k) {
                    s.erase(i - k + 1, k);
                    break;
                }
            }
        }
        return s;
    }
};

/*
solution 2: memo count
time: O(n), traverse the string once is O(n)
space: O(n), store the count
*/
class Solution {
public:
    string removeDuplicates(string s, int k) {
        vector<int> cnt(s.size());
        
        for (int i = 0; i < s.size(); ++i) {
            if (i == 0 || s[i] != s[i - 1])
                cnt[i] = 1;
            else {
                cnt[i] = cnt[i - 1] + 1;
                if (cnt[i] == k) {
                    s.erase(i - k + 1, k);
                    i -= k;
                }
            }
        }
        return s;
    }
};


/*
solution 3: memo count + stack
time: O(n), traverse the string once is O(n)
space: O(n), store the count
*/
class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<int> cnt;
        for (int i = 0; i < s.size(); ++i) {
            if (i == 0 || s[i] != s[i - 1])
                cnt.push(1);
            else if (++cnt.top() == k) {
                cnt.pop();
                s.erase(i - k + 1, k); 
                i -= k;
            }
        }
        
        return s;
    }
};