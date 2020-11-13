/*
solution: prefix sum + binary search
time: O(logn) for pickIndex(), n is the length of the array. O(n) for constrcutor
space: O(n), a prefix sum array
*/

class Solution {
public:
    Solution(vector<int>& w) {
        sum = w;
        for (int i = 1; i < w.size(); ++i) {
            sum[i] = sum[i - 1] + w[i];
        }
    }
    
    int pickIndex() {
        int x = rand() % sum.back();
        int start = 0;
        int end = sum.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (sum[mid] > x) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        if (sum[start] > x) {
            return start;
        } else {
            return end;
        }
    }
private:
    vector<int> sum;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */