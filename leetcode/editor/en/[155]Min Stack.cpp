//Design a stack that supports push, pop, top, and retrieving the minimum elemen
//t in constant time. 
//
// Implement the MinStack class: 
//
// 
// MinStack() initializes the stack object. 
// void push(int val) pushes the element val onto the stack. 
// void pop() removes the element on the top of the stack. 
// int top() gets the top element of the stack. 
// int getMin() retrieves the minimum element in the stack. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["MinStack","push","push","push","getMin","pop","top","getMin"]
//[[],[-2],[0],[-3],[],[],[],[]]
//
//Output
//[null,null,null,null,-3,null,0,-2]
//
//Explanation
//MinStack minStack = new MinStack();
//minStack.push(-2);
//minStack.push(0);
//minStack.push(-3);
//minStack.getMin(); // return -3
//minStack.pop();
//minStack.top();    // return 0
//minStack.getMin(); // return -2
// 
//
// 
// Constraints: 
//
// 
// -231 <= val <= 231 - 1 
// Methods pop, top and getMin operations will always be called on non-empty sta
//cks. 
// At most 3 * 104 calls will be made to push, pop, top, and getMin. 
// 
// Related Topics Stack Design 
// 👍 8489 👎 643


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two arrays to stack
 * time: O(1)
 * space: O(n)
 * */
class MinStack {
public:
    vector<int> stack_arr, min_arr;
    int MIN;
    MinStack() {
        MIN = INT_MAX;
    }

    void push(int val) {
        stack_arr.push_back(val);
        if (val <= MIN) MIN = val;
        min_arr.push_back(MIN);
    }

    void pop() {
        stack_arr.pop_back();
        min_arr.pop_back();
        if (stack_arr.empty()) MIN = INT_MAX;
        else MIN = min_arr.back();
    }

    int top() {
        return stack_arr.back();
    }

    int getMin() {
        return min_arr.back();
    }
};

class MinStack:

    def __init__(self):
        self.min = float('inf')
        self.stk = []
        self.min_stk = []

    def push(self, val: int) -> None:
        self.stk.append(val)
        if val <= self.min:
            self.min = val
        self.min_stk.append(self.min)

    def pop(self) -> None:
        self.stk.pop()
        self.min_stk.pop()
        if not self.stk: self.min = float('inf')
        else: self.min = self.min_stk[-1]

    def top(self) -> int:
        return self.stk[-1]

    def getMin(self) -> int:
        return self.min_stk[-1]

/*
 * solution 2: two arrays to stack
 * time: O(1)
 * space: O(n)
 * */
class MinStack {
private:
    stack<int> data;
    stack<int> min;

public:
    /** initialize your data structure here. */
    MinStack() {
    }

    void push(int x) {
        data.push(x);
        if(min.empty()){
            min.push(x);
        } else {
            if(x > min.top()){
                x = min.top();
            }
            min.push(x);
        }
    }

    void pop() {
        data.pop();
        min.pop();
    }

    int top() {
        return data.top();
    }

    int getMin() {
        return min.top();
    }
};
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
//leetcode submit region end(Prohibit modification and deletion)
