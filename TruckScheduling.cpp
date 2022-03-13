#include <bits/stdc++.h>
#include "Utility.cpp"
#include "Trip.cpp"
#include "Truck.cpp"
#include "randomInputGen.cpp"

#define P(X) cout<<"db "<<X<<endl;
#define P2(X,Y) cout<<"d2 "<<X<<" "<<Y<<endl;
#define P3(X,Y,Z) cout<<"d3 "<<X<<" "<<Y<<" "<<Z<<endl;

using namespace std;

vector<Trip> tripList;
vector<Truck> truckList;
vector<Truck> optimalTruckList;

int optimalExtraDistNow = INT_MAX;
int maxAssignableTrip = 0, numTripTarget;
int steps = 0;
void assignTripsToTruckBacktrack(int assignedTripsCnt, int extraDist){
    if(optimalExtraDistNow <= extraDist){
        return; // already not optimal;
    }
    steps++;
    maxAssignableTrip = max(maxAssignableTrip, assignedTripsCnt);
    if(numTripTarget == assignedTripsCnt){
        optimalExtraDistNow = extraDist;
        ///Analize Assigmnent
        optimalTruckList = truckList;
        return;
    }
    for(int i = 0; i < tripList.size(); i++){
        if(tripList[i].hasGotTruck) continue;
        for(int j = 0; j < truckList.size(); j++){
                //truckList[j].addTrip(NULL);
            if(truckList[j].isfitTrip(tripList[i])){
                int extraDistHere = truckList[j].addTrip(&tripList[i]);
                assignTripsToTruckBacktrack(assignedTripsCnt + 1, extraDist + extraDistHere);
                truckList[j].popLastTrip(&tripList[i]);
            }
        }
    }
}
class TruckTripPair{
    public:
    int truckID, tripID;
    int huristicVal;
    TruckTripPair(int truckID,int tripID, int huristicVal){
        this->tripID = tripID;
        this->truckID = truckID;
        this->huristicVal = huristicVal;
    }
    bool operator < (const TruckTripPair & pair2)const{
        return huristicVal < pair2.huristicVal;
    }
};

void assignTripsToTruckHuristic(int assignedTripsCnt, int extraDist){
    if(optimalExtraDistNow <= extraDist){
        return; // already not optimal;
    }
    steps++;
    maxAssignableTrip = max(maxAssignableTrip, assignedTripsCnt);
    if(numTripTarget == assignedTripsCnt){
        optimalExtraDistNow = extraDist;
        ///Analize Assigmnent
        optimalTruckList = truckList;
        return;
    }
    vector<TruckTripPair> truckTripPairList;
    for(int i = 0; i < tripList.size(); i++){
        if(tripList[i].hasGotTruck) continue;
        for(int j = 0; j < truckList.size(); j++){
            if(truckList[j].isfitTrip(tripList[i])){

                int extraDistHere = truckList[j].extraDist(&tripList[i]);
                truckTripPairList.push_back(TruckTripPair(j, i, extraDist));
            }
        }
    }
    sort(truckTripPairList.begin(), truckTripPairList.end());
    int size = min((int)truckTripPairList.size(), 3);/// Not more than 3 pair
    for(int i = 0; i < size; i++){
        int truckID = truckTripPairList[i].truckID;
        int tripID = truckTripPairList[i].tripID;
        int extraDistHere = truckList[truckID].addTrip(&tripList[tripID]);
        assignTripsToTruckHuristic(assignedTripsCnt + 1, extraDist + extraDistHere);
        truckList[truckID].popLastTrip(&tripList[tripID]);
    }
}

void assignTripsToTruckGreedy(int assignedTripsCnt, int extraDist){
    if(optimalExtraDistNow <= extraDist){
        return; // already not optimal;
    }
    steps++;
    maxAssignableTrip = max(maxAssignableTrip, assignedTripsCnt);
    if(numTripTarget == assignedTripsCnt){
        optimalExtraDistNow = extraDist;
        ///Analize Assigmnent
        optimalTruckList = truckList;
        return;
    }
    TruckTripPair currentOptimalPair(0,0, -1);
    vector<TruckTripPair> truckTripPairList;
    for(int i = 0; i < tripList.size(); i++){
        if(tripList[i].hasGotTruck) continue;
        for(int j = 0; j < truckList.size(); j++){
            if(truckList[j].isfitTrip(tripList[i])){

                int extraDistHere = truckList[j].extraDist(&tripList[i]);
                if(currentOptimalPair.huristicVal == -1){
                    currentOptimalPair = TruckTripPair(j, i, extraDist);
                }
                else if(extraDist < currentOptimalPair.huristicVal){
                    currentOptimalPair = TruckTripPair(j, i, extraDist);
                }
            }
        }
    }
    int truckID = currentOptimalPair.truckID;
    int tripID = currentOptimalPair.tripID;
    int extraDistHere = truckList[truckID].addTrip(&tripList[tripID]);
    assignTripsToTruckGreedy(assignedTripsCnt + 1, extraDist + extraDistHere);
    truckList[truckID].popLastTrip(&tripList[tripID]);

}


int main()
{
    //freopen("outb.txt","w", stdout);
    RandomInputGen inputGen(50);
    inputGen.addTrucks(truckList, 4);
    inputGen.addTrips(tripList, 7);

    numTripTarget = tripList.size();
    assignTripsToTruckHuristic(0, 0);

    if(maxAssignableTrip < tripList.size()){
        numTripTarget = maxAssignableTrip;
        assignTripsToTruckHuristic(0, 0);
    }

    cout<<numTripTarget<<" Trips assigned out of "<<tripList.size()<<" trips with "<<steps<<" steps"<<endl;
    cout<<"Total distance without load is: "<< optimalExtraDistNow<<endl;

    for(Truck truck: optimalTruckList){
        truck.printRoute(tripList);
    }
	#ifndef ONLINE_JUDGE
    freopen("test.txt","r",stdin);
	#endif

    return 0;
}



