/*
solution: hashmap + set
time: O(1) for addScore and reset, O(k) for top
space: O(n), n is the number of players
*/
class Leaderboard {
public:
    Leaderboard() {
        
    }
    
    void addScore(int playerId, int score) {
        players.erase({score_map[playerId], playerId});
        score_map[playerId] += score;
        players.insert({score_map[playerId], playerId});
    }
    
    int top(int K) {
        int res = 0;
        for (auto it = players.rbegin(); it != players.rend() && K > 0; ++it, --K)
            res += it->first;
        return res;
    }
    
    void reset(int playerId) {
        players.erase({score_map[playerId], playerId});
        score_map.erase(playerId);
    }
private:
    set<pair<int, int>> players;
    unordered_map<int, int> score_map;
};

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */