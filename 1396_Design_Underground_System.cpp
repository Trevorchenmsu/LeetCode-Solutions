/*
solution 1: design
time: O(1)
space: O(P+S^2), P is the number of passengaers. it is counted in checkIn function. 
S^2. where S is the number of stations.for start station A, it may check out at any station B,
so the possibility is S^2
*/


class UndergroundSystem {
public:
    UndergroundSystem() {
        
    }
    
    void checkIn(int id, string stationName, int t) {
        inMap[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t) {
        // get start station and start time
        const auto &[startStation, timeIn] = inMap[id];
        auto &[totalDuration, tripsCnt] = stats[startStation + ">" + stationName];
        totalDuration += t - timeIn;
        ++tripsCnt;
    }
    
    double getAverageTime(string startStation, string endStation) {
        auto [totalDuration, tripsCnt] = stats[startStation + ">" + endStation];
        return (double)totalDuration / tripsCnt;
    }
    
private:
    unordered_map<int, pair<string, int>> inMap;
    // string stores the combination of start and end stations
    unordered_map<string, pair<int, int>> stats;
};


/*
solution 2: design
time: O(1)
space: O(P+S^2), P is the number of passengaers. it is counted in checkIn function. 
S^2 where S is the number of stations.for start station A, it may check out at any station B,
so the possibility is S^2
*/

class UndergroundSystem {
public:
    UndergroundSystem() {
        
    }
    
    void checkIn(int id, string stationName, int t) {
        in_map[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t) {
        pair<string, int> in_info = in_map[id];
        string s = in_info.first + "->" + stationName; // start->end
        int time = t - in_info.second;
        
        if (!startToEnd.count(s))
            startToEnd[s] = {time, 1};
        else {
            startToEnd[s].first += time;
            startToEnd[s].second += 1;
        }
        
    }
    
    double getAverageTime(string startStation, string endStation) {
        string s = startStation + "->" + endStation;
        pair<int, int> total = startToEnd[s];
        return  (double) total.first / total.second;
    }

private:
    unordered_map<int, pair<string, int>> in_map;
    unordered_map<string, pair<int, int>> startToEnd;
};