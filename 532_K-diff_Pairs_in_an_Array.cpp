/*
solution 1: two pointers
time: O(nlogn)
space: O(1), O(n)? due to sort?
*/
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int left = 0, right = 1, res = 0;
        
        while (left < nums.size() && right < nums.size()) {
            if (left == right || nums[right] - nums[left] < k) right++;
            else if (nums[right] - nums[left] > k) left++;
            else {
                left++;
                res++;
                while (left < nums.size() && nums[left] == nums[left - 1])
                    left++;
            }
        }
        return res;
    }
};
/*
solution 2: hashmap
time: O(n)
space: O(n)
*/

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        int res = 0;
        unordered_map<int, int> map;
        for (const auto& num : nums) 
            map[num]++;
        for (auto& m : map) {
            if ((k == 0 && m.second > 1) || (k > 0 && map.count(m.first + k)))
                res++;
        }
        return res;
    }
};