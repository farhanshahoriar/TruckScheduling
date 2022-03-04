#include <bits/stdc++.h>
using namespace std;

int getCurTime(){
    return 0;
}
int distanceToTime(int distance){
    int speed = 1;
    return distance * speed;
}
unordered_map<int, int> distMap;
int getDistance(int locA, int locB){
    // We have make this function consistant
    int hs = locA * 1000 + locB;
    if(distMap.count(hs)) return distMap[hs];
    int dis = rand() % 40 + 1;
    return distMap[hs] = dis;
}
