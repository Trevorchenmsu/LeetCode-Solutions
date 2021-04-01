//You are assigned to put some amount of boxes onto one truck. You are given a 2
//D array boxTypes, where boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]: 
//
// 
// numberOfBoxesi is the number of boxes of type i. 
// numberOfUnitsPerBoxi is the number of units in each box of the type i. 
// 
//
// You are also given an integer truckSize, which is the maximum number of boxes
// that can be put on the truck. You can choose any boxes to put on the truck as l
//ong as the number of boxes does not exceed truckSize. 
//
// Return the maximum total number of units that can be put on the truck. 
//
// 
// Example 1: 
//
// 
//Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
//Output: 8
//Explanation: There are:
//- 1 box of the first type that contains 3 units.
//- 2 boxes of the second type that contain 2 units each.
//- 3 boxes of the third type that contain 1 unit each.
//You can take all the boxes of the first and second types, and one box of the t
//hird type.
//The total number of units will be = (1 * 3) + (2 * 2) + (1 * 1) = 8.
// 
//
// Example 2: 
//
// 
//Input: boxTypes = [[5,10],[2,5],[4,7],[3,9]], truckSize = 10
//Output: 91
// 
//
// 
// Constraints: 
//
// 
// 1 <= boxTypes.length <= 1000 
// 1 <= numberOfBoxesi, numberOfUnitsPerBoxi <= 1000 
// 1 <= truckSize <= 106 
// 
// Related Topics Greedy Sort 
// 👍 263 👎 20


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: greedy + sort
 * time: O(nlogn)
 * space: O(1)
 *
 * */
class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        int res = 0;
        if (boxTypes.empty()) return res;

        sort(boxTypes.begin(), boxTypes.end(), [](const vector<int> &v1, const vector<int> &v2){
            return v1[1] > v2[1];
        });

        for (const auto &boxType: boxTypes) {
            if (truckSize == 0) break;
            if (truckSize > boxType[0]) {
                truckSize -= boxType[0];
                res += boxType[0] * boxType[1];
            }
            else{
                res += truckSize * boxType[1];
                truckSize = 0;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
