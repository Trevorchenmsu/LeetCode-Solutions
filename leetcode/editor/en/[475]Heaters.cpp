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
            /*
             * idx查找的是在heater中第一个大于等于house的heater，当找到这个idx后，需要查看这个idx
             * 左右两边的heater哪个离house更近。但实际上我们不需要考虑右边，因为这个idx是第一个大于
             * 等于house的heater，所以它肯定是右边界heater。而左边界heater就只能是idx-1。通过这
             * 两个heater与house的差值，可以得到两个heater的半径。为什么要取这两个heater的较小值
             * 半径？因为对于这两个heater来说，它们都可以覆盖house，而根据题意，肯定是优先选半径短的.
             * 但是查找这个idx的时候就会产生两个边界条件：（1）idx在最左边；（2）idx在最右边。因为在
             * 二分法中要么返回start要么返回end，idx不会超出[0,n]这个区间。我们需要两个半径，对于情
             * 况一如何处理？左边界不存在了，我们又不想取它，由于比较时用较小值，所以这里赋值INT_MAX，
             * 这样就不会取到这个最大值作为左边界。如果idx不是最左边的时候，我们就以普通的idx-1表示左
             * 边界。同理，对于idx在最右边时，就用INT_MAX代替。如果小于最右边，就用正常的idx表示右
             * 边界。
             * */
            int heater_idx = binarySearch(heaters, house);
            int radius_left = (heater_idx == 0) ? INT_MAX : abs(house - heaters[heater_idx - 1]);
            int radius_right = (heater_idx == heaters.size()) ? INT_MAX : abs(heaters[heater_idx] - house);

            res = max(res, min(radius_right, radius_left));
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
