//We are given a list of (axis-aligned) rectangles. Each rectangle[i] = [xi1, yi
//1, xi2, yi2] , where (xi1, yi1) are the coordinates of the bottom-left corner, a
//nd (xi2, yi2) are the coordinates of the top-right corner of the ith rectangle. 
//
//
// Find the total area covered by all rectangles in the plane. Since the answer 
//may be too large, return it modulo 109 + 7. 
//
// 
// Example 1: 
//
// 
//Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
//Output: 6
//Explanation: As illustrated in the picture.
// 
//
// Example 2: 
//
// 
//Input: rectangles = [[0,0,1000000000,1000000000]]
//Output: 49
//Explanation: The answer is 1018 modulo (109 + 7), which is (109)2 = (-7)2 = 49
//.
// 
//
// 
// Constraints: 
//
// 
// 1 <= rectangles.length <= 200 
// rectanges[i].length = 4 
// 0 <= rectangles[i][j] <= 109 
// The total area covered by all rectangles will never exceed 263 - 1 and thus w
//ill fit in a 64-bit signed integer. 
// 
// Related Topics Segment Tree Line Sweep 
// 👍 443 👎 32


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution 1: sweep line in x direction
 * time:O(n*nlogn)
 * space:O(n)
 *
 * */
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();

        /* ****************************** step 1 ************************************
         * start和end在这里表示起始状态和结束状态，用于区分矩形左右边。对每个矩阵，会在event存储两个单元：
         * 单元一：{矩形左边x坐标，矩形左边状态，矩形底边y坐标，矩形顶边y坐标}，矩形左边状态都默认为start
         * 单元二：{矩形右边x坐标，矩形右边状态，矩形底边y坐标，矩形顶边y坐标}，矩形右边状态都默认为end
         * 因此，对每个矩形都会在event中存储2*4个元素，所以event的空间复杂度为O(2n*4)=O(n)
         *
         */
        int start = 0, end = 1;
        vector<vector<long>> events;
        for (const auto& rec : rectangles) { //O(n)
            int x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
            events.push_back({x1, start, y1, y2});
            events.push_back({x2, end, y1, y2});
        }

        /* ****************************** step 2 ************************************
         * 对event进行升序排序，这边遍历的时候就可以实现从左到右的扫描这些线段。排序后会优先扫描
         * 一个矩形的左边，但是在这个左边扫描后是否能够扫描它的右边则是不确定的，因为其它矩形的左
         * 边可能比当前矩形的右边小。所以这种方式就可以应对矩形有面积重合的情况。
        */
        sort(events.begin(), events.end()); //O(nlogn)


        /* ****************************** step 3 ************************************
         * 在每一个扫描区间中，我们要算的面积是x方向的跨度乘以y方向的跨度。所以需要有pre_x记录上一次的x边界
         * cur_x记录当前的x边界，它俩之差就是当前x方向的跨度。yRanges就是用来保存y方向的跨度。
         * */
        long res = 0;
        long pre_x = 0, MOD = 1000000007;
        vector<vector<long>> yRanges; // O(n)


        for (const auto& event : events) { // O(n*nlogn)
            /*  在这个循环里面，我们可以保证每次计算的面积都是在一个区间的面积，不管有没有重合区间。
             *  如果在x左边界上有多个重合边界，那么它们的cur_x都是一样的，所以cur_x-pre_x为0，面积为0.
             *  所以在下面的代码中只要遇到左边界时，就把它对应的y方向跨度存入yRanges中，并排序，等待右边界出现。
             *  虽然在相同x的时候可能存在多个右边界，但是因为我们每次只按照排序遍历其中一个，所以可以一个个考虑。
             *  因此，下面循环内的情况就是：存在多个左边界，一个右边界。处理左边界多个重叠问题，然后选出面积。
             */
            long cur_x = event[0], status = event[1], y1 = event[2], y2 = event[3];
            res += getArea(cur_x - pre_x, yRanges); // O(n)

            /*
             * 如果是左边界，我们只需要把它的y方向跨度放入集合中并排序
             * 如果是右边界，包含这个右边界矩形的面积已经在调用getArea时被使用过
             * 所以我们不再需要这个右边界，为了避免重复调用，需要在yRanges中把它删除
             * */
            if (status == start) {
                yRanges.push_back({y1, y2});
                sort(yRanges.begin(), yRanges.end()); //O(nlogn)
            }
            else {
                // remove the considered interval
                for (int i = 0; i < yRanges.size(); ++i) { // O(n)
                    if (yRanges[i][0] == y1 && yRanges[i][1] == y2) {
                        yRanges.erase(yRanges.begin() + i);
                        break;
                    }
                }
            }

            pre_x = cur_x;
        }

        return (int) (res % MOD);
    }

private:
    /* ****************************** step 4 ************************************
     *  当我们具有多个y跨度在x左边界，需要考虑如何处理这几个y跨度。
       1 ——
        |_|____
        |_|   | 2
      3 |_|   |
        | |   |
        |_|___|
    从上面的矩形分布可以看出，最高矩形是矩形1，1*5，第二高为矩形2，4*4，最小矩形为矩形3，1*1，且被矩形2包围
     矩形1加入event的情况为:(0,0,0,5), (1,1,0,5); 矩形2加入event的情况为：(0,0,0,4), (4,1,0,4)
     矩形3加入event的情况为:(0,0,2,3), (1,1,2,3)
     event排序结果为：(0,0,0,4),(0,0,0,5),(0,0,2,3),(1,1,0,5), (1,1,2,3),(4,1,0,4)
     yRanges加入后排序结果为：(0,4),(0,5),(2,3)
     当前的情况是遇到了右边界(1,1,0,5)，开始计算面积，因为这个时候width开始不为0了。

     （1）首先处理(0,4)的y跨度，它属于矩形2，当处理完这个后，左侧1*4的小矩形面积被加入结果中，不管什么矩形，只要包括在
     这个范围内，不管重不重合，反正都以这个已计算的矩形面积为准。同时把prev更新为top，这是因为top以下的面积已经被计算了，
     不需要再考虑，接下来要考虑的只需要是top以上的内容。
     （2）当遍历到(0,5)时，bottom = max(bottom, prev)，这个
     代码就起到选取较高底边的作用，虽然在(0,5)得到的初始bottom是0，但是通过与prev取较大值，bottom被更新为4，所以起到去除
     下部分被处理的面积。所以这一部分的矩形面积为1。
     （3）当遍历到(2,3)时，初始得到的bottom=2,top=3，但是我们在上一轮处理
     得到的prev已经是5了，也就是说被处理的高度已经累积到5，再通过取较大值的话，bottom变为5，此时bottom比top大，所以我们
     不需要处理添加这个矩形，因此我们才加入if (top>bottom)这个判定条件。也就是为了覆盖那些被包括在已处理矩形里面的其他矩形。
     * */
    long getArea(long width, vector<vector<long>> &yRanges) {
        long area = 0;
        long prev = 0;

        for (const auto& y_range : yRanges) {
            long bottom = y_range[0], top = y_range[1];
            bottom = max(bottom, prev);
            if (top > bottom) {
                area += (top - bottom) * width;
                prev = top;
            }
        }

        return area;
    }
};




/*
 * Solution 2: sweep line in y direction
 * time:O(n*nlogn)
 * space:O(n)
 *
 * */
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int start = 0, end = 1;
        int n = rectangles.size();
        vector<vector<long>> events;

        for (const auto& rec : rectangles) {
            int x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
            events.push_back({y1, start, x1, x2}); // left edge of the rectangle
            events.push_back({y2, end, x1, x2}); // right edge of the rectangle
        }
        // consider all the left edges first, then the right edges
        sort(events.begin(), events.end());

        long res = 0;
        long pre_y = 0, MOD = 1000000007;
        vector<vector<long>> intervals;

        for (const auto& event : events) {
            long cur_y = event[0], status = event[1], x1 = event[2], x2 = event[3];
            res += getArea(cur_y - pre_y, intervals);

            if (status == start) {
                intervals.push_back({x1, x2});
                sort(intervals.begin(), intervals.end());
            }
            else {
                for (int i = 0; i < intervals.size(); ++i) {
                    if (intervals[i][0] == x1 && intervals[i][1] == x2) {
                        intervals.erase(intervals.begin() + i);
                        break;
                    }
                }
            }

            pre_y = cur_y;
        }

        return (int) (res % MOD);
    }

private:
    long getArea(long width, vector<vector<long>> &intervals) {
        long area = 0;
        long prev = 0;

        for (const auto& interval : intervals) {
            long left = interval[0], right = interval[1];
            left = max(left, prev);
            if (right > left) {
                area += (right - left) * width;
                prev = right;
            }
        }

        return area;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
