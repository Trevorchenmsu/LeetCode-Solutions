//Given two arrays of integers nums1 and nums2, return the number of triplets fo
//rmed (type 1 and type 2) under the following rules: 
//
// 
// Type 1: Triplet (i, j, k) if nums1[i]2 == nums2[j] * nums2[k] where 0 <= i < 
//nums1.length and 0 <= j < k < nums2.length. 
// Type 2: Triplet (i, j, k) if nums2[i]2 == nums1[j] * nums1[k] where 0 <= i < 
//nums2.length and 0 <= j < k < nums1.length. 
// 
//
// 
// Example 1: 
//
// 
//Input: nums1 = [7,4], nums2 = [5,2,8,9]
//Output: 1
//Explanation: Type 1: (1,1,2), nums1[1]^2 = nums2[1] * nums2[2]. (4^2 = 2 * 8).
// 
// 
//
// Example 2: 
//
// 
//Input: nums1 = [1,1], nums2 = [1,1,1]
//Output: 9
//Explanation: All Triplets are valid, because 1^2 = 1 * 1.
//Type 1: (0,0,1), (0,0,2), (0,1,2), (1,0,1), (1,0,2), (1,1,2).  nums1[i]^2 = nu
//ms2[j] * nums2[k].
//Type 2: (0,0,1), (1,0,1), (2,0,1). nums2[i]^2 = nums1[j] * nums1[k].
// 
//
// Example 3: 
//
// 
//Input: nums1 = [7,7,8,3], nums2 = [1,2,9,7]
//Output: 2
//Explanation: There are 2 valid triplets.
//Type 1: (3,0,2).  nums1[3]^2 = nums2[0] * nums2[2].
//Type 2: (3,0,1).  nums2[3]^2 = nums1[0] * nums1[1].
// 
//
// Example 4: 
//
// 
//Input: nums1 = [4,7,9,11,23], nums2 = [3,5,1024,12,18]
//Output: 0
//Explanation: There are no valid triplets.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums1.length, nums2.length <= 1000 
// 1 <= nums1[i], nums2[i] <= 10^5 
// 
// Related Topics Hash Table Math 
// 👍 139 👎 33


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<long long, int> map1, map2;
        int res = 0;
        long long one = 1;

        for (const auto& num : nums1)
            map1[one * num * num]++;

        for (const auto& num : nums2)
            map2[one * num * num]++;

        for (int i = 0; i < nums1.size(); i++) {
            for (int j = i + 1; j < nums1.size(); j++) {
                long long pro = one * nums1[i] * nums1[j];
                if (map2.count(pro))
                    res += map2[pro];
            }
        }

        for (int i = 0; i < nums2.size(); i++) {
            for (int j = i + 1; j < nums2.size(); j++) {
                long long pro = one * nums2[i] * nums2[j];
                if (map1.count(pro))
                    res += map1[pro];
            }
        }


        return res;
    }
};


/*
 * solution 2: hash table
 * time: O(n^2)
 * space: O(n)
 * */
class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        return getCount(nums1, nums2) + getCount(nums2, nums1);
    }

private:
    int getCount(vector<int>& nums1, vector<int>& nums2) {
        int res = 0;
        unordered_map<long long, int> cnt_map;
        long long one = 1;

        for (const auto &num : nums1)
            cnt_map[one * num * num]++;


       for (int i = 0; i < nums2.size(); i++) {
           for (int j = i + 1; j < nums2.size(); j++) {
               res += cnt_map[one * nums2[i] * nums2[j]];
           }
       }

       return res;

    }
};


//leetcode submit region end(Prohibit modification and deletion)
