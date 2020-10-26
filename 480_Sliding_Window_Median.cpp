/*
Solution 1: Brute force. Time Limit Exception
time: O(n*k*logk), as sort() each time takes O(klogk), traverse the array takes n times, so the final is O(N*N*logN)
space: O(k), extra linear space for the window container.
*/
// brute force
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        // edge case
        if (nums.empty() || nums.size() == 0) {
            return res;
        }
        
        // traverse the array
        for (int i = 0; i + k <= nums.size(); ++i) {
            vector<int> window(nums.begin() + i, nums.begin() + i + k);
            sort(window.begin(), window.end());
            
            if (k % 2 != 0) {
                res.push_back((double)window[k / 2]);
            } else {
                res.push_back(((double)window[k / 2 - 1] + (double)window[k / 2]) / 2.0);
            }
        }
                              
        return res;
        
    }
};

/*
Solution 1: Brute force. Time Limit Exception
time: O(N*N*logN), as sort() each time takes O(KlogK), traverse the array takes N times, so the final is O(N*N*logN)
space: O(N), build the new space to store results. 
*/