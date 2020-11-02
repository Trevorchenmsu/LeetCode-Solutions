/*
solution: sliding window + two pointers
time: O(n), we traverse the array for one time
space: O(1), no extra space
*/
class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        int res = 0;
        if (A.empty() || A.size() == 0)
            return res;
        
        int left = 0, right; 
        for (right = 0; right < A.size(); ++right) {
            if (A[right] == 0) --K;
            
            if (K < 0) {
                if (A[left] == 0) ++K;
                ++left;
            }
        }
        return right - left;
        
    }
};


