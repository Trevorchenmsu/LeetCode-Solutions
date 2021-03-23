/*
 * solution: sweep line
 * time: O(n^2*logn)
 * space:
 *
 * */
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int open = 0, close = 1;
        int n = rectangles.size();
        vector<vector<int>> events (2 * n, vector<int> (4));
        int t = 0;

        for (auto &rec : rectangles) {
            events[t++] = {rec[1], open, rec[0], rec[2]};
            events[t++] = {rec[3], close, rec[0], rec[2]};
        }

        sort(events.begin(), events.end(), [] (const vector<int> &v1, const vector<int> &v2) {
            return v1[0] < v2[0];
        });

        vector<vector<int>> active;
        int cur_y = events[0][0];
        long res = 0;

        for (auto& event : events) {
            int y = event[0], typ = event[1], x1 = event[2], x2 = event[3];

            // calculate query
            long query = 0;
            int cur = -1;

            for (auto xs : active) {
                cur = max(cur, xs[0]);
                query += max(xs[1] - cur, 0);
                cur = max(cur, xs[1]);
            }

            res += query *(y - cur_y);

            if (typ == open) {
                active.push_back({x1, x2});
                sort(active.begin(), active.end(), [] (const vector<int> &v1, const vector<int> &v2) {
                    return v1[0] < v2[0];
                });
            }
            else {
                for (int i = 0; i < active.size(); ++i) {
                    if (active[i][0] == x1 && active[i][1] == x2) {
                        active.erase(active.begin() + i);
                        break;
                    }
                }
            }

            cur_y = y;
        }

        res %= 1000000007;
        return (int) res;

    }
};
