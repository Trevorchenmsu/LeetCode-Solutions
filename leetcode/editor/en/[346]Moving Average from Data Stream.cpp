//Given a stream of integers and a window size, calculate the moving average of 
//all integers in the sliding window. 
//
// Implement the MovingAverage class: 
//
// 
// MovingAverage(int size) Initializes the object with the size of the window si
//ze. 
// double next(int val) Returns the moving average of the last size values of th
//e stream. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["MovingAverage", "next", "next", "next", "next"]
//[[3], [1], [10], [3], [5]]
//Output
//[null, 1.0, 5.5, 4.66667, 6.0]
//
//Explanation
//MovingAverage movingAverage = new MovingAverage(3);
//movingAverage.next(1); // return 1.0 = 1 / 1
//movingAverage.next(10); // return 5.5 = (1 + 10) / 2
//movingAverage.next(3); // return 4.66667 = (1 + 10 + 3) / 3
//movingAverage.next(5); // return 6.0 = (10 + 3 + 5) / 3
// 
//
// 
// Constraints: 
//
// 
// 1 <= size <= 1000 
// -105 <= val <= 105 
// At most 104 calls will be made to next. 
// 
// Related Topics Design Queue 
// 👍 837 👎 84


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: queue
 * time: O(1)
 * space: O(n), n is the size of the window
 * */
class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        win_size = size;
        sum = 0;
    }
    
    double next(int val) {
        if (q.size() < win_size) {
            sum += val;
            q.push(val);
        }
        else {
            int pre = q.front(); q.pop();
            sum += val - pre;
            q.push(val);
        }

        return q.size() == win_size ?  ((double) sum / win_size) :  ((double) sum / q.size());
    }

private:
    int win_size;
    queue<int> q;
    int sum;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
//leetcode submit region end(Prohibit modification and deletion)
