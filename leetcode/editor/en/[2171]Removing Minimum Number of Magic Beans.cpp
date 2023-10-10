//You are given an array of positive integers beans, where each integer represen
//ts the number of magic beans found in a particular magic bag. 
//
// Remove any number of beans (possibly none) from each bag such that the number
// of beans in each remaining non-empty bag (still containing at least one bean) i
//s equal. Once a bean has been removed from a bag, you are not allowed to return 
//it to any of the bags. 
//
// Return the minimum number of magic beans that you have to remove. 
//
// 
// Example 1: 
//
// 
//Input: beans = [4,1,6,5]
//Output: 4
//Explanation: 
//- We remove 1 bean from the bag with only 1 bean.
//  This results in the remaining bags: [4,0,6,5]
//- Then we remove 2 beans from the bag with 6 beans.
//  This results in the remaining bags: [4,0,4,5]
//- Then we remove 1 bean from the bag with 5 beans.
//  This results in the remaining bags: [4,0,4,4]
//We removed a total of 1 + 2 + 1 = 4 beans to make the remaining non-empty bags
// have an equal number of beans.
//There are no other solutions that remove 4 beans or fewer.
// 
//
// Example 2: 
//
// 
//Input: beans = [2,10,3,2]
//Output: 7
//Explanation:
//- We remove 2 beans from one of the bags with 2 beans.
//  This results in the remaining bags: [0,10,3,2]
//- Then we remove 2 beans from the other bag with 2 beans.
//  This results in the remaining bags: [0,10,3,0]
//- Then we remove 3 beans from the bag with 3 beans. 
//  This results in the remaining bags: [0,10,0,0]
//We removed a total of 2 + 2 + 3 = 7 beans to make the remaining non-empty bags
// have an equal number of beans.
//There are no other solutions that removes 7 beans or fewer.
// 
//
// 
// Constraints: 
//
// 
// 1 <= beans.length <= 105 
// 1 <= beans[i] <= 105 
// 
// 👍 179 👎 19


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sort, prefix sum
 * time: O(nlogn)
 * space: O(1)
 * */
class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        long n = beans.size(), res = LLONG_MAX;
        long sum = accumulate(beans.begin(), beans.end(), 0L);
        sort(beans.begin(), beans.end());

        /*
        sum-(n-i)*beans[i]公式解释：
        以[2,10,3,2]为例，排序后为[2,2,3,10]。主要思想是从小到大，每次删除一个值后，就需要把后面的值切平，例如
        （1）删除第一个2以后得到2，[0,2,3,10]，要计算还要切多少才能保证剩下的数相等，就是(3-2)+(10-2)=1+8，总共要删除
        2+9=11个豆子。（2）删除第二个2以后，变成[0,0,3,10]，剩下的就变成10-3=7，总共要删除2+2+7=11；（3）删除3以后，
        变成[0,0,0,10]，由于只有一个元素，所以不用再删除，总共删除2+2+3=7，也就是说在这个过程中每次求较小值。
        可以将这个过程拆分为两部分：
        (1)在某个位置i，i前面的都是被删除的豆子，那么自然是求和,N[0]+N[1]+...N[i-1]
        (2)在>=i的位置，就得求每个元素与起点i的插值，然后求和，即(N[i]-N[i])+(N[i+1]-N[i])+...+(N[n-1]-N[i])
        这两部分的和就是我们每次要求的删除豆子个数，把它们合并起来，等于：
        N[0]+N[1]+...N[i-1] + (N[i]-N[i])+(N[i+1]-N[i])+...+(N[n-1]-N[i])=
        N[0] + N[1] + ... + N[n - 1] - (n - i) * N[i] = sum - (n - i) * N[i]
        */
        for (int i = 0; i < n; ++i) {
            res = min(res, sum - (n - i) * beans[i]);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
