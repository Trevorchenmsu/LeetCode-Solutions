//You have one chocolate bar that consists of some chunks. Each chunk has its ow
//n sweetness given by the array sweetness. 
//
// You want to share the chocolate with your K friends so you start cutting the 
//chocolate bar into K+1 pieces using K cuts, each piece consists of some consecut
//ive chunks. 
//
// Being generous, you will eat the piece with the minimum total sweetness and g
//ive the other pieces to your friends. 
//
// Find the maximum total sweetness of the piece you can get by cutting the choc
//olate bar optimally. 
//
// 
// Example 1: 
//
// 
//Input: sweetness = [1,2,3,4,5,6,7,8,9], K = 5
//Output: 6
//Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9
//]
// 
//
// Example 2: 
//
// 
//Input: sweetness = [5,6,7,8,9,1,2,3,4], K = 8
//Output: 1
//Explanation: There is only one way to cut the bar into 9 pieces.
// 
//
// Example 3: 
//
// 
//Input: sweetness = [1,2,2,1,2,2,1,2,2], K = 2
//Output: 5
//Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]
// 
//
// 
// Constraints: 
//
// 
// 0 <= K < sweetness.length <= 10^4 
// 1 <= sweetness[i] <= 10^5 
// 
// Related Topics Binary Search Greedy 
// 👍 453 👎 32


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int K)
    {
        int sum = 0;
        for (auto x: sweetness)
            sum+=x;

        int left = 0;
        int right = sum;

        while (left<right)
        {
            int mid = left+(right-left+1)/2;
            if (ok(sweetness, mid, K))
                left = mid;
            else
                right = mid-1;
        }

        return left;
    }

    bool ok(vector<int>& sweetness, int S, int K)
    {
        int sum = 0;
        int count = 0;
        for (int i=0; i<sweetness.size(); i++)
        {
            sum+=sweetness[i];
            if (sum>=S)
            {
                sum = 0;
                count++;
            }
        }
        return count>=K+1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
