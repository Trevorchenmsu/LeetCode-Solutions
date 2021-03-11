/*
solution: segment tree
time: O(n)
space: O(n)
*/
class MyCalendarThree {
public:
    MyCalendarThree() {}
    
    int book(int start, int end) {
        ++freq[start];
        --freq[end];
        
        int cnt = 0, res = 0;
        for (auto& f : freq) {
            cnt += f.second;
            res = max(res, cnt);
        }
        
        return res;
    }
    
private:
    map<int, int> freq;
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */