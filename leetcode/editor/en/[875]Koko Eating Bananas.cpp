//Koko loves to eat bananas. There are n piles of bananas, the ith pile has pile
//s[i] bananas. The guards have gone and will come back in h hours. 
//
// Koko can decide her bananas-per-hour eating speed of k. Each hour, she choose
//s some pile of bananas and eats k bananas from that pile. If the pile has less t
//han k bananas, she eats all of them instead and will not eat any more bananas du
//ring this hour. 
//
// Koko likes to eat slowly but still wants to finish eating all the bananas bef
//ore the guards return. 
//
// Return the minimum integer k such that she can eat all the bananas within h h
//ours. 
//
// 
// Example 1: 
//
// 
//Input: piles = [3,6,7,11], h = 8
//Output: 4
// 
//
// Example 2: 
//
// 
//Input: piles = [30,11,23,4,20], h = 5
//Output: 30
// 
//
// Example 3: 
//
// 
//Input: piles = [30,11,23,4,20], h = 6
//Output: 23
// 
//
// 
// Constraints: 
//
// 
// 1 <= piles.length <= 104 
// piles.length <= h <= 109 
// 1 <= piles[i] <= 109 
// 
// Related Topics Binary Search 
// 👍 1374 👎 85


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: binary search, TLE
 * time: O(hn*logn)
 * space:
 * */
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        if (piles.empty()) return 0;

        long start = 1e9, end = 0, total = 0;
        for (auto &pile : piles) { // O(n)
            start = min(start, (long) pile);
            end = max(end, (long) pile);
            total += pile;
        }

        while (start + 1 < end) { // O(hn*logn)
            long mid = start + (end - start) / 2;
            if (canEatup(piles, mid, h, total))
                end = mid;
            else
                start = mid;
        }

        if (canEatup(piles, start, h, total)) return (int) start; // O(hn)

        return (int) end;
    }

private:
    bool canEatup(vector<int> piles, long k, int h, long total) { // O(hn)
        long sum = 0, i = 0, j = 0;
        int n = piles.size();

        while (j < h) {
            while (piles[i % n] == 0) {
                i++;
            }

            if (piles[i % n] < k) {
                sum += piles[i % n];
                piles[i % n] = 0;
                i++, j++;
            }
            else {
                sum += k;
                piles[i % n] -= k;
                i++, j++;
            }

        }

        return sum == total;
    }

};



/*
 * solution 2: binary search
 * time: O(n*log(maxPile))
 * space: O(1)
 * */
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        if (piles.empty() || piles.size() == 0) {
            return 0;
        }

        int start = 1, end = *max_element(piles.begin(), piles.end());
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (canComplete(piles, mid, h)) {
                end = mid;
            }
            else {
                start = mid;
            }
        }

        if (canComplete(piles, start, h)) {
            return start;
        }

        return end;
    }

    bool canComplete(vector<int>& piles, int k, int h) {
        int sum = 0;

        for (auto pile : piles) {
            sum += (pile + k - 1) / k;
            if (sum > h) {
                return false;
            }
        }

        return true;
    }
};


//leetcode submit region end(Prohibit modification and deletion)
