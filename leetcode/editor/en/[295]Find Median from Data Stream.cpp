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
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) { // O(logn)
        PQ_right.push(num);
        if (PQ_right.size() > PQ_left.size()) {
            int val = PQ_right.top(); PQ_right.pop();
            PQ_left.push(val);
        }

        if (PQ_left.top() > PQ_right.top()) {
            int left_big = PQ_left.top(); PQ_left.pop();
            int right_small = PQ_right.top(); PQ_right.pop();
            PQ_left.push(right_small);
            PQ_right.push(left_big);
        }
    }
    
    double findMedian() { // O(logn)
        int left = PQ_left.size(), right = PQ_right.size();
        if ((left + right) % 2 == 0){
            return (PQ_left.top() + PQ_right.top()) / 2.0;
        }
        else {
            return (double) PQ_left.top();
        }
    }

private:
    priority_queue<int> PQ_left; // O(n)
    priority_queue<int, vector<int>, greater<int>> PQ_right;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
//leetcode submit region end(Prohibit modification and deletion)
