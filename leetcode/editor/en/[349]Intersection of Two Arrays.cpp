//Given two integer arrays nums1 and nums2, return an array of their intersectio
//n. Each element in the result must be unique and you may return the result in an
//y order. 
//
// 
// Example 1: 
//
// 
//Input: nums1 = [1,2,2,1], nums2 = [2,2]
//Output: [2]
// 
//
// Example 2: 
//
// 
//Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
//Output: [9,4]
//Explanation: [4,9] is also accepted.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums1.length, nums2.length <= 1000 
// 0 <= nums1[i], nums2[i] <= 1000 
// 
// Related Topics Hash Table Two Pointers Binary Search Sort 
// 👍 1342 👎 1513


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 0: hash set
 * time: O(min(m, n))
 * space: O(max(m, n))
 * */

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return intersection(nums2, nums1);
        }

        unordered_set<int> res;
        unordered_set<int> numSet(nums2.begin(), nums2.end());

        for (auto &num : nums1) {
            auto it = numSet.find(num);
            if (it != numSet.end()) {
                res.insert(num);
            }
        }

        return vector<int> (res.begin(), res.end());
    }
};


/*
 * solution 1: two pointers + hash set + sort
 * time: O(max(mlogm, nlogn)
 * space: O(max(logm, logn), for stack space when sorting
 * */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> res;
        if (nums1.empty() || nums2.empty())
            return {};

        sort(nums1.begin(), nums1.end()); // O(mlogm)
        sort(nums2.begin(), nums2.end()); // o(nlogn)
        int i = 0, j = 0, m = nums1.size(), n = nums2.size();

        while (i < m && j < n) { // O(min(m, n))
            if (nums1[i] == nums2[j]) {
                res.insert(nums1[i]);
                i++, j++;
            }
            else if (nums1[i] < nums2[j]) i++;
            else j++;
        }

        vector<int> res(res.begin(), res.end()); //  O(min(m, n))

        return res;
    }
};



/*
 * solution 2: binary search + sort
 * time: O(nlogn), m is the size of nums1, n is the size of nums2
 * space: O(logn), for stack space when sorting
 * */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        if (nums1.empty() || nums2.empty())
            return res;

        if (nums1.size() > nums2.size())
            return intersection(nums2, nums1);

        sort(nums1.begin(), nums1.end());  // O(mlogm)
        sort(nums2.begin(), nums2.end()); // O(nlogn)

        for (int i = 0; i < nums1.size() - 1; i++) { // O(mlogn)
            if (nums1[i + 1] == nums1[i]) continue;
            if (binarySearch(nums2, nums1[i]))
                res.push_back(nums1[i]);
        }

        if (binarySearch(nums2, nums1[nums1.size() - 1])) // O(logn)
            res.push_back(nums1[nums1.size() - 1]);

        return res;
    }

private:
    bool binarySearch(vector<int> &nums, int target) { //  O(logn)
        int start = 0, end = nums.size() - 1;

        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target)
                return true;
            else if (nums[mid] > target)
                end = mid;
            else
                start = mid;
        }

        if (nums[start] == target || nums[end] == target)
            return true;

        return false;
    }
};


/*
 * solution 3: STL intersection of set
 * time: O(nlogn), m is the size of nums1, n is the size of nums2
 * space: O(logn), for stack space when sorting
 * */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> st1(nums1.begin(), nums1.end());
        set<int> st2(nums2.begin(), nums2.end());
        vector<int> vec;
        set_intersection(st1.begin(),st1.end(),st2.begin(),st2.end(),inserter(vec, vec.begin() ));
        return vec;
    }
};


/*
 * solution 4: two pointers + hash set + sort, optimized
 * time: O(max(mlogm, nlogn)
 * space: O(max(logm, logn), for stack space when sorting
 * */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> res;
        if (nums1.empty() || nums2.empty())
            return {};

        sort(nums1.begin(), nums1.end()); // O(mlogm)
        sort(nums2.begin(), nums2.end()); // o(nlogn)
        int i = 0, j = 0, m = nums1.size(), n = nums2.size();

        while (i < m && j < n) { // O(min(m, n))
            if (nums1[i] == nums2[j]) {
                res.insert(nums1[i]);
                i++, j++;
                while(i < nums1.size() && nums1[i] == nums1[i - 1]) ++i;
                while(j < nums2.size() && nums2[j] == nums2[j - 1]) ++j;
            }
            else if (nums1[i] < nums2[j]) {
                i++;
                while(i < nums1.size() && nums1[i] == nums1[i-1]) ++i;
            }
            else {
                j++;
                while(j < nums2.size() && nums2[j] == nums2[j-1]) ++j;
            }
        }

        vector<int> ans(res.begin(), res.end()); //  O(min(m, n))

        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
