//Design a max stack data structure that supports the stack operations and suppo
//rts finding the stack's maximum element. 
//
// Implement the MaxStack class: 
//
// 
// MaxStack() Initializes the stack object. 
// void push(int x) Pushes element x onto the stack. 
// int pop() Removes the element on top of the stack and returns it. 
// int top() Gets the element on the top of the stack without removing it. 
// int peekMax() Retrieves the maximum element in the stack without removing it.
// 
// int popMax() Retrieves the maximum element in the stack and removes it. If th
//ere is more than one maximum element, only remove the top-most one. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["MaxStack", "push", "push", "push", "top", "popMax", "top", "peekMax", "pop",
// "top"]
//[[], [5], [1], [5], [], [], [], [], [], []]
//Output
//[null, null, null, null, 5, 5, 1, 5, 1, 5]
//
//Explanation
//MaxStack stk = new MaxStack();
//stk.push(5);   // [5] the top of the stack and the maximum number is 5.
//stk.push(1);   // [5, 1] the top of the stack is 1, but the maximum is 5.
//stk.push(5);   // [5, 1, 5] the top of the stack is 5, which is also the maxim
//um, because it is the top most one.
//stk.top();     // return 5, [5, 1, 5] the stack did not change.
//stk.popMax();  // return 5, [5, 1] the stack is changed now, and the top is di
//fferent from the max.
//stk.top();     // return 1, [5, 1] the stack did not change.
//stk.peekMax(); // return 5, [5, 1] the stack did not change.
//stk.pop();     // return 1, [5] the top of the stack and the max element is no
//w 5.
//stk.top();     // return 5, [5] the stack did not change.
// 
//
// 
// Constraints: 
//
// 
// -107 <= x <= 107 
// At most 104 calls will be made to push, pop, top, peekMax, and popMax. 
// There will be at least one element in the stack when pop, top, peekMax, or po
//pMax is called. 
// 
//
// 
//Follow up: Could you come up with a solution that supports O(1) for each top c
//all and O(logn) for each other call? Related Topics Design 
// 👍 927 👎 225


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution: two stacks
 * time: O(n)
 * space: O(n)
 * */

class MaxStack {
public:
    /** initialize your data structure here. */
    MaxStack() {
        
    }
    
    void push(int x) {
        if (maxStack.empty() || maxStack.top() <= x)
            maxStack.push(x);
        dataStack.push(x);
    }
    
    int pop() {
        if (!maxStack.empty() && maxStack.top() == dataStack.top())
            maxStack.pop();
        int res = dataStack.top();
        dataStack.pop();
        return res;
    }
    
    int top() {
        return dataStack.top();
    }
    
    int peekMax() {
        return maxStack.top();
    }
    
    int popMax() {
        int res = maxStack.top();

        stack<int> temp;
        while (dataStack.top() != maxStack.top()) {
            temp.push(dataStack.top());
            dataStack.pop();
        }

        dataStack.pop();
        maxStack.pop();

        while (!temp.empty()) {
            push(temp.top());
            temp.pop();
        }

        return res;
    }

private:
    stack<int> maxStack, dataStack;
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
//leetcode submit region end(Prohibit modification and deletion)
