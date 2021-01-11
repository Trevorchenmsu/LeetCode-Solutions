class Solution {
private:
    // index by group id
    vector<vector<int>> Groups;
    vector<unordered_set<int>> GroupsBefore;

    // index by item id
    vector<int> *ItemGroup;
    vector<vector<int>> *ItemBefore; 
    
    unordered_set<int> handledGroup;
    unordered_set<int> handledItem;
    vector<int> res;

    int _handleOneItem(const int &item, unordered_set<int> &st) {
        int rc = 0;
        if (st.count(item))
            return -1;

        if (handledItem.count(item))
            return 0;
        
        st.insert(item);
        for (auto &i:(*ItemBefore)[item]) {
            if ((*ItemGroup)[i] == (*ItemGroup)[item]) {
                rc = _handleOneItem(i, st);
                if (rc < 0) return rc;
            }
        }
        st.erase(item);
        
        res.emplace_back(item);
        handledItem.insert(item);
        return rc;
    }

    int _arrangeOneGroup(const int &gid) {
        unordered_set<int> st;
        int rc = 0;
        
        for (auto &iid:Groups[gid]) {
            rc = _handleOneItem(iid, st);
            if (rc < 0) return rc;
        }   
        
        return rc;
    }

    int _handleOneGroup(const int &gid, unordered_set<int> &st) {
        int rc = 0;
        if (st.count(gid)) {
            return -1;
        }

        if (handledGroup.count(gid))
            return 0;

        st.insert(gid);
        for (auto &j : GroupsBefore[gid]) {
            rc = _handleOneGroup(j, st);
            if (rc < 0) return rc;
        }
        st.erase(gid);

        handledGroup.insert(gid);
        return _arrangeOneGroup(gid);
    }
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {       
        int rc;

        ItemGroup = &group;
        ItemBefore = &beforeItems;
        
        Groups.resize(m);
        int start = m;
        for (int i = 0; i < n; ++i) {
            if ((*ItemGroup)[i] == -1) {
                vector<int> t = {i};
                Groups.emplace_back(t);
                (*ItemGroup)[i] = start++;
            } else {
                Groups[(*ItemGroup)[i]].emplace_back(i);
            }
        }
        GroupsBefore.resize(Groups.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < (*ItemBefore)[i].size(); ++j) {
                int groupID = (*ItemGroup)[(*ItemBefore)[i][j]];
                if (groupID != (*ItemGroup)[i])
                    GroupsBefore[(*ItemGroup)[i]].insert(groupID);
            }
        }
        unordered_set<int> tmp;
        for (int i = 0; i < Groups.size(); ++i) {
            rc = _handleOneGroup(i, tmp);
            if (rc < 0) {
                res.clear();
                return res;
            }
        }
        return res;
    }
};

