//Design a stack which supports the following operations. 
//
// Implement the CustomStack class: 
//
// 
// CustomStack(int maxSize) Initializes the object with maxSize which is the max
//imum number of elements in the stack or do nothing if the stack reached the maxS
//ize. 
// void push(int x) Adds x to the top of the stack if the stack hasn't reached t
//he maxSize. 
// int pop() Pops and returns the top of stack or -1 if the stack is empty. 
// void inc(int k, int val) Increments the bottom k elements of the stack by val
//. If there are less than k elements in the stack, just increment all the element
//s in the stack. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["CustomStack","push","push","pop","push","push","push","increment","increment
//","pop","pop","pop","pop"]
//[[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
//Output
//[null,null,null,2,null,null,null,null,null,103,202,201,-1]
//Explanation
//CustomStack customStack = new CustomStack(3); // Stack is Empty []
//customStack.push(1);                          // stack becomes [1]
//customStack.push(2);                          // stack becomes [1, 2]
//customStack.pop();                            // return 2 --> Return top of th
//e stack 2, stack becomes [1]
//customStack.push(2);                          // stack becomes [1, 2]
//customStack.push(3);                          // stack becomes [1, 2, 3]
//customStack.push(4);                          // stack still [1, 2, 3], Don't 
//add another elements as size is 4
//customStack.increment(5, 100);                // stack becomes [101, 102, 103]
//
//customStack.increment(2, 100);                // stack becomes [201, 202, 103]
//
//customStack.pop();                            // return 103 --> Return top of 
//the stack 103, stack becomes [201, 202]
//customStack.pop();                            // return 202 --> Return top of 
//the stack 102, stack becomes [201]
//customStack.pop();                            // return 201 --> Return top of 
//the stack 101, stack becomes []
//customStack.pop();                            // return -1 --> Stack is empty 
//return -1.
// 
//
// 
// Constraints: 
//
// 
// 1 <= maxSize <= 1000 
// 1 <= x <= 1000 
// 1 <= k <= 1000 
// 0 <= val <= 100 
// At most 1000 calls will be made to each method of increment, push and pop eac
//h separately. 
// Related Topics Stack Design 
// 👍 574 👎 48


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two stacks
 * time: O(n)
 * space: O(n)
 * */
class CustomStack {
public:
    CustomStack(int maxSize) {
        maxLen = maxSize;
    }

    void push(int x) { // O(1)
        if (workStack.size() == maxLen)
            return;
        workStack.push(x);
    }

    int pop() {// O(1)
        if (workStack.empty())
            return -1;
        int res = workStack.top();
        workStack.pop();
        return res;
    }

    void increment(int k, int val) { // O(n)
        if (k >= workStack.size()) {
           helper(val);
        }
        else {
            int cnt = workStack.size() - k;

            while (cnt > 0) {
                helperStack.push(workStack.top());
                workStack.pop();
                cnt--;
            }

            helper(val);
        }
    }

private:
    int maxLen;
    stack<int> workStack;
    stack<int> helperStack;
    void helper(int val) {
        while (!workStack.empty()) { // O(n)
            helperStack.push(workStack.top() + val);
            workStack.pop();
        }

        while (!helperStack.empty()) { // O(n)
            workStack.push(helperStack.top());
            helperStack.pop();
        }
    }
};


/*
 * solution 2: vector
 * time: O(n)
 * space: O(n)
 * */
class CustomStack {
public:
    CustomStack(int maxSize) {
        maxLen = maxSize;
        cnt = 0;
        nums = vector<int> (1001, 0);
    }

    void push(int x) { // O(1)
        if (cnt == maxLen)
            return;
        cnt++;
        nums[cnt] = x;
    }

    int pop() {// O(1)
        if (cnt == 0)
            return -1;

        int res = nums[cnt];
        nums[cnt--] = 0;
        return res;
    }

    void increment(int k, int val) { // O(k)
       while (k > 0) {
           nums[k] += val;
           k--;
       }
    }

private:
    int maxLen;
    int cnt;
    vector<int> nums;
};

/*
 * solution 3: vector
 * time: O(n)
 * space: O(n)
 * */

class CustomStack {
public:
    CustomStack(int maxSize) {
        _maxSize = maxSize;
    }

    void push(int x) {
        if (nums.size() == _maxSize)
            return;
        nums.push_back(x);
    }

    int pop() {
        if (nums.empty())
            return -1;
        int res = nums.back();
        nums.pop_back();
        return res;
    }

    void increment(int k, int val) {
        if (nums.size() >= k) {
            for (int i = 0; i < k; i++)
                nums[i] += val;
        }
        else {
            for (int i = 0; i < nums.size(); i++)
                nums[i] += val;
        }
    }


private:
    int _maxSize;
    vector<int> nums;
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
//leetcode submit region end(Prohibit modification and deletion)
