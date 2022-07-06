//The median is the middle value in an ordered integer list. If the size of the 
//list is even, there is no middle value and the median is the mean of the two mid
//dle values. 
//
// 
// For example, for arr = [2,3,4], the median is 3. 
// For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5. 
// 
//
// Implement the MedianFinder class: 
//
// 
// MedianFinder() initializes the MedianFinder object. 
// void addNum(int num) adds the integer num from the data stream to the data st
//ructure. 
// double findMedian() returns the median of all elements so far. Answers within
// 10-5 of the actual answer will be accepted. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
//[[], [1], [2], [], [3], []]
//Output
//[null, null, null, 1.5, null, 2.0]
//
//Explanation
//MedianFinder medianFinder = new MedianFinder();
//medianFinder.addNum(1);    // arr = [1]
//medianFinder.addNum(2);    // arr = [1, 2]
//medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
//medianFinder.addNum(3);    // arr[1, 2, 3]
//medianFinder.findMedian(); // return 2.0
// 
//
// 
// Constraints: 
//
// 
// -105 <= num <= 105 
// There will be at least one element in the data structure before calling findM
//edian. 
// At most 5 * 104 calls will be made to addNum and findMedian. 
// 
//
// 
// Follow up: 
//
// 
// If all integer numbers from the stream are in the range [0, 100], how would y
//ou optimize your solution? 
// If 99% of all integer numbers from the stream are in the range [0, 100], how 
//would you optimize your solution? 
// 
// Related Topics Heap Design 
// 👍 4309 👎 81


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: heap
 * time: O(logn)
 * space: O(n)
 *
 * */
class MedianFinder {
public:
    priority_queue<int> small;
    priority_queue<int, vector<int>, greater<int>> large;
    MedianFinder() {

    }

    void addNum(int num) {
        large.push(num);
        if (large.size() > small.size())
        {
            small.push(large.top());
            large.pop();
        }

        if (small.top() > large.top())
        {
            large.push(small.top());
            small.pop();
            small.push(large.top());
            large.pop();
        }
    }

    double findMedian() {
        double res = small.size() == large.size() ? (small.top() + large.top()) / 2.0 : (double) small.top();
        return res;
    }
};


class MedianFinder:

    def __init__(self):
        self.small = []
        self.large = []

    def addNum(self, num: int) -> None:
        heapq.heappush(self.large, num)
        if len(self.large) > len(self.small):
            heapq.heappush(self.small, -heapq.heappop(self.large))

        if len(self.small) > 0 and len(self.large) > 0 and -self.small[0] > self.large[0]:
            heapq.heappush(self.large, -heapq.heappop(self.small))
            heapq.heappush(self.small, -heapq.heappop(self.large))


    def findMedian(self) -> float:
        res = (-self.small[0] + self.large[0]) / 2.0 if len(self.small) == len(self.large) else -self.small[0]
        return res
/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
//leetcode submit region end(Prohibit modification and deletion)
