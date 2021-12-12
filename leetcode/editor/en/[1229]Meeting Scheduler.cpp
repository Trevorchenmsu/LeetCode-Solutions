//Given the availability time slots arrays slots1 and slots2 of two people and a
// meeting duration duration, return the earliest time slot that works for both of
// them and is of duration duration. 
//
// If there is no common time slot that satisfies the requirements, return an em
//pty array. 
//
// The format of a time slot is an array of two elements [start, end] representi
//ng an inclusive time range from start to end. 
//
// It is guaranteed that no two availability slots of the same person intersect 
//with each other. That is, for any two time slots [start1, end1] and [start2, end
//2] of the same person, either start1 > end2 or start2 > end1. 
//
// 
// Example 1: 
//
// 
//Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], durat
//ion = 8
//Output: [60,68]
// 
//
// Example 2: 
//
// 
//Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], durat
//ion = 12
//Output: []
// 
//
// 
// Constraints: 
//
// 
// 1 <= slots1.length, slots2.length <= 104 
// slots1[i].length, slots2[i].length == 2 
// slots1[i][0] < slots1[i][1] 
// slots2[i][0] < slots2[i][1] 
// 0 <= slots1[i][j], slots2[i][j] <= 109 
// 1 <= duration <= 106 
// 
// Related Topics Array Two Pointers Sorting 
// 👍 481 👎 22


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sort + interval
 * time: O(nlogn + mlogm)
 * space: O(logn + logm) for sorting
 * */
class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        vector<int> res;
        if (slots1.empty() || slots2.empty()) {
            return res;
        }

        sort(slots1.begin(), slots1.end());
        sort(slots2.begin(), slots2.end());

        int i = 0, j = 0, start = 0, end = 0 ;
        while (i < slots1.size() && j < slots2.size()) {
            if (slots1[i][1] > slots2[j][0] || slots1[i][0] < slots2[j][1]) {
                start = max(slots1[i][0], slots2[j][0]);
                end = min(slots1[i][1], slots2[j][1]);
                if (end - start >= duration) {
                    return {start, start + duration};
                }
                else {
                    if (slots1[i][1] == end) {
                        i++;
                    }
                    else {
                        j++;
                    }
                }
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
