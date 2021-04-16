//Winter is coming! During the contest, your first job is to design a standard h
//eater with a fixed warm radius to warm all the houses. 
//
// Every house can be warmed, as long as the house is within the heater's warm r
//adius range. 
//
// Given the positions of houses and heaters on a horizontal line, return the mi
//nimum radius standard of heaters so that those heaters could cover all houses. 
//
// Notice that all the heaters follow your radius standard, and the warm radius 
//will the same. 
//
// 
// Example 1: 
//
// 
//Input: houses = [1,2,3], heaters = [2]
//Output: 1
//Explanation: The only heater was placed in the position 2, and if we use the r
//adius 1 standard, then all the houses can be warmed.
// 
//
// Example 2: 
//
// 
//Input: houses = [1,2,3,4], heaters = [1,4]
//Output: 1
//Explanation: The two heater was placed in the position 1 and 4. We need to use
// radius 1 standard, then all the houses can be warmed.
// 
//
// Example 3: 
//
// 
//Input: houses = [1,5], heaters = [2]
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// 1 <= houses.length, heaters.length <= 3 * 104 
// 1 <= houses[i], heaters[i] <= 109 
// 
// Related Topics Binary Search 
// 👍 891 👎 928


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two pointers
 * time: O(mn)
 * space: O(max(logm, logn), stack space for sorting
 *
 * */
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int n = heaters.size(), j = 0, res = 0;

        sort(houses.begin(), houses.end()); // O(mlogm)
        sort(heaters.begin(), heaters.end()); // O(nlogn)

        for (int i = 0; i < houses.size(); ++i) { // O(mn)
            int cur_house = houses[i];

            while(j < n - 1 && abs(heaters[j + 1] - cur_house) <= abs(heaters[j] - cur_house))
                ++j;

            res = max(res, abs(heaters[j] - cur_house));
        }

        return res;
    }
};

/*
 * solution 2: binary search
 * time: O(max(mlogn, nlogn))
 * space: O(logn), stack space for sorting
 *
 * */
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(heaters.begin(), heaters.end()); // O(nlogn)
        int res = 0;

        for (auto &house : houses) { //O(mlogn)
            int heater_idx = binarySearch(heaters, house);

            int radius1 = (heater_idx == heaters.size()) ? INT_MAX : abs(heaters[heater_idx] - house);
            int radius2 = (heater_idx == 0) ? INT_MAX : abs(house - heaters[heater_idx - 1]);

            res = max(res, min(radius1, radius2));
        }

        return res;
    }

private:
    int binarySearch(vector<int> &heaters, int target) { // O(logn)
        int start = 0, end = heaters.size() - 1;

        // binary search for the first element larger and equal to current house
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;

            if (heaters[mid] >= target)
                end = mid;
            else
                start = mid;
        }

        if (heaters[start] >= target)
            return start;

        return end;
    }
};


/*
 * solution 3: binary search, STL lower_bound function
 * time: O(max(mlogn, nlogn))
 * space: O(logn), stack space for sorting
 *
 * */
class Solution {
public:
    int findRadius(vector<int> &houses, vector<int> &heaters) {
        sort(heaters.begin(), heaters.end()); // O(nlogn)
        int res = 0;

        for (auto &house : houses) { //O(mlogn)
            auto heater_iter = lower_bound(heaters.begin(), heaters.end(), house);

            int radius1 = (heater_iter == heaters.end()) ? INT_MAX : abs(*heater_iter - house);
            int radius2 = (heater_iter == heaters.begin()) ? INT_MAX : abs(house - *(heater_iter - 1));

            res = max(res, min(radius1, radius2));
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
