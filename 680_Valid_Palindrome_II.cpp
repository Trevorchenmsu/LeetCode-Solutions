/*
solution: two pointers (shrinkage type)
time: O(n)
space: O(1)
*/
class Solution {
public:
    bool validPalindrome(string s) {
        if (s.empty())  return true;
        
        pair<int, int> diff = findDifference(s, 0, s.length() - 1);
        if (diff.first >= diff.second) return true;
        
        return isPalindrome(s, diff.first + 1, diff.second) || isPalindrome(s, diff.first, diff.second - 1);
    }
    
    pair<int, int> findDifference(const string &s, int left, int right) {
        while (left < right && s[left] == s[right]) {
            left++;
            right--;
        }
        pair<int, int> res = make_pair(left, right);
        return res;
    }
    
    bool isPalindrome(const string &s, int left, int right) {
        pair<int, int> diff = findDifference(s, left, right);
        return diff.first >= diff.second;
    }
};