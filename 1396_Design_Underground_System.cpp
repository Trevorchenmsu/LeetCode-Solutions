/*
solution: system design
time: O(1)
space: O(P+S^2), P is the number of passengaers. it is counted in checkIn function. S^2?
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

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */

