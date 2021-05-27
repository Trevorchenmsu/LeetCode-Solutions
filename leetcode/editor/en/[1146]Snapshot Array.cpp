//Implement a SnapshotArray that supports the following interface: 
//
// 
// SnapshotArray(int length) initializes an array-like data structure with the g
//iven length. Initially, each element equals 0. 
// void set(index, val) sets the element at the given index to be equal to val. 
//
// int snap() takes a snapshot of the array and returns the snap_id: the total n
//umber of times we called snap() minus 1. 
// int get(index, snap_id) returns the value at the given index, at the time we 
//took the snapshot with the given snap_id 
// 
//
// 
// Example 1: 
//
// 
//Input: ["SnapshotArray","set","snap","set","get"]
//[[3],[0,5],[],[0,6],[0,0]]
//Output: [null,null,0,null,5]
//Explanation: 
//SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
//snapshotArr.set(0,5);  // Set array[0] = 5
//snapshotArr.snap();  // Take a snapshot, return snap_id = 0
//snapshotArr.set(0,6);
//snapshotArr.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5
// 
//
// 
// Constraints: 
//
// 
// 1 <= length <= 50000 
// At most 50000 calls will be made to set, snap, and get. 
// 0 <= index < length 
// 0 <= snap_id < (the total number of times we call snap()) 
// 0 <= val <= 10^9 
// 
// Related Topics Array 
// 👍 847 👎 160


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: hash set + vector + binary search
 * time: O(n)
 * space: O(n)
 * */
class SnapshotArray {
public:
    SnapshotArray(int length) {
        snapId = 0;
        snaps.resize(length);
        for (int i = 0; i < length; i++)
            snaps[i].push_back({-1, 0}); // 对每个index，初始它的第一个snapId为-1，改变的val为0
    }
    
    void set(int index, int val) {
        vals[index] = val; // 更新当前index对应的val
        changed.insert(index); // 加入发生改变的index
        /*
         * 这里的changed就是特地存入index的，假如没有发生快照，不管这个index下的val被set过多少次
         * 我们都只care它目前最新的状态，所以说只能有一个index，不能重复，因此用哈希集。
         * */
    }
    
    int snap() {
        // 执行快照，记录发生改变的元素
        for (int index : changed) {
            // 在当前快照ID下，插入index更新的value
            snaps[index].push_back({snapId, vals[index]});
        }
        changed.clear(); //清除上次这次快照前的所有变化，为下一次快照记录变化做准备；
        snapId++;
        return snapId - 1;
    }
    
    int get(int index, int snap_id) {
        /* 对当前index下，取在snap_id时的快照下index对应的val。因为在这个snap_id下，index不一定有变化，
        因此我们只能取第一个小于等于snap_id的id值，小于表示没有snap_id的快照，等于表示有，因此这里才可以采用
        二分法的思路，查找upper_bound。因为upper_bound返回的是第一个大于snap_id的迭代器位置，所以要向后退一位
        就是第一个小于等于snap_id的迭代器位置。
        */
        auto iter = upper_bound(snaps[index].begin(), snaps[index].end(), make_pair(snap_id, INT_MAX));
        iter = prev(iter, 1);
        return iter->second;
    }

private:
    int vals[50000]; // 用于存储index对应的值，主要可以用来在set方法中更新val
    /*
    snaps存的是某个index在多个快照中元素的变化情况，例如snaps[1]存的是在1位置时，经历了不同快照，有的快照中这个1位置对应的val
    没有发生变化，所有没有被加入，而在有的快照中1位置对应值发生了变化，因此快照的具体id和变化的val都被记录起来。
    每一次变化就是一个pair = (snapId, val)，因此可能在多次快照中发生变化，所以需要用数组把pair存起来。而不同的位置有不同的变化
    情况，所以需要另一个数组继续存上述的数组。
    */
    vector<vector<pair<int, int>>> snaps;
    /*
     * 存储发生改变的index，但是在快照发生前，无论这个index改变了多少，我们都不知道，因为没有进行快照，所以结果只会是返回更新index
     * 对应的值，但最终快照care的只是最后一个，所以这里采用哈希集就可以忽略我们总共加入改变的index有多少次。
     * */
    unordered_set<int> changed;
    int snapId;
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
//leetcode submit region end(Prohibit modification and deletion)
