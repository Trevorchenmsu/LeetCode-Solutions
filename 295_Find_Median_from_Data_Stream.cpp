/*
solution 1: two heaps
time: O(logn) + O(1), O(logn) is used to add a number because in heap, its operation is proportional 
	 to the height of the tree. O(1) is used to find the median.
space: O(n), we need space to store n numbers.
*/
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        large.push(num); // 因为不知道新加入的值是不是左边最大的，所以得加入large中进行保证
        small.push(large.top());
        large.pop();
        if (large.size() < small.size()) { //表示左边的少了，得移到右边
            large.push(small.top());
            small.pop();
        }
    }
    
    double findMedian() {
        return large.size() > small.size() ? (double) large.top() : (large.top() + small.top()) / 2.0;
    }
    
private:
    priority_queue<int, vector<int>, greater<int>> small;
    priority_queue<int> large;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */