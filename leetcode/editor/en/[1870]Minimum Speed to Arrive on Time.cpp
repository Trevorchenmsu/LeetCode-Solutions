//You are given a floating-point number hour, representing the amount of time yo
//u have to reach the office. To commute to the office, you must take n trains in 
//sequential order. You are also given an integer array dist of length n, where di
//st[i] describes the distance (in kilometers) of the ith train ride. 
//
// Each train can only depart at an integer hour, so you may need to wait in bet
//ween each train ride. 
//
// 
// For example, if the 1st train ride takes 1.5 hours, you must wait for an addi
//tional 0.5 hours before you can depart on the 2nd train ride at the 2 hour mark.
// 
// 
//
// Return the minimum positive integer speed (in kilometers per hour) that all t
//he trains must travel at for you to reach the office on time, or -1 if it is imp
//ossible to be on time. 
//
// Tests are generated such that the answer will not exceed 107 and hour will ha
//ve at most two digits after the decimal point. 
//
// 
// Example 1: 
//
// 
//Input: dist = [1,3,2], hour = 6
//Output: 1
//Explanation: At speed 1:
//- The first train ride takes 1/1 = 1 hour.
//- Since we are already at an integer hour, we depart immediately at the 1 hour
// mark. The second train takes 3/1 = 3 hours.
//- Since we are already at an integer hour, we depart immediately at the 4 hour
// mark. The third train takes 2/1 = 2 hours.
//- You will arrive at exactly the 6 hour mark.
// 
//
// Example 2: 
//
// 
//Input: dist = [1,3,2], hour = 2.7
//Output: 3
//Explanation: At speed 3:
//- The first train ride takes 1/3 = 0.33333 hours.
//- Since we are not at an integer hour, we wait until the 1 hour mark to depart
//. The second train ride takes 3/3 = 1 hour.
//- Since we are already at an integer hour, we depart immediately at the 2 hour
// mark. The third train takes 2/3 = 0.66667 hours.
//- You will arrive at the 2.66667 hour mark.
// 
//
// Example 3: 
//
// 
//Input: dist = [1,3,2], hour = 1.9
//Output: -1
//Explanation: It is impossible because the earliest the third train can depart 
//is at the 2 hour mark.
// 
//
// 
// Constraints: 
//
// 
// n == dist.length 
// 1 <= n <= 105 
// 1 <= dist[i] <= 105 
// 1 <= hour <= 109 
// There will be at most two digits after the decimal point in hour. 
// 
// Related Topics Math Binary Search 
// 👍 199 👎 58


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int n = dist.size();
        if (hour <= n-1 ) return -1;

        int low = 1, high = 1e7;

        while (low < high)
        {
            int mid = low+(high-low)/2;
            double time = helper(dist, mid);
            if (time > hour)
                low = mid+1;
            else
                high = mid;
        }

        return low;
    }

    double helper(vector<int>&dist, int speed)
    {
        double time = 0;
        for (int i=0; i<dist.size()-1; i++)
        {
            time += (dist[i]-1)/speed+1;
        }
        time += dist.back()*1.0/speed;
        return time;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
