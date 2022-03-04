class Truck{
    public:
    int truckID;
    int currentLocation;
    bool isInTrip;
    int nextFreeLocation;
    int nextFreeTime;
    int initialLocation;
    vector<int> tripIDList;
    Truck(){
        isInTrip = false;
        nextFreeTime = getCurTime();
    }
    Truck(int id, int location){
        truckID = id;
        isInTrip = false;
        nextFreeTime = getCurTime();
        nextFreeLocation = location;
        currentLocation = location;
        initialLocation = location;
    }
    void printRoute(vector<Trip> &tripList){
        cout<<"TruckID: "<<truckID<<endl;
        if(tripIDList.size() == 0) cout<<"No trip assigned to this Truck"<<endl;
        int prevLoc = initialLocation;
        for(int tripID : tripIDList){
            int locA = tripList[tripID].startLocation;
            int locB = tripList[tripID].endLocation;
            printf("Extra Trip to reach start Location: %d to %d, Distance %d\n", prevLoc, locA, getDistance(prevLoc, locA));
            printf("Main Trip: %d to %d, Distance %d\n", locA, locB, getDistance(locA, locB));
            prevLoc = locB;
        }
        cout<<endl;
    }
    int extraDist(Trip *curTrip){
        int extraDist = getDistance(nextFreeLocation, curTrip->startLocation);
        return extraDist;
    }
    int addTrip(Trip *curTrip){
        int extraDist = getDistance(nextFreeLocation, curTrip->startLocation);
        int reqTime = distanceToTime(extraDist) + max(getCurTime(), nextFreeTime);
        int startTime = max(reqTime, curTrip->earliestStartTime);

        tripIDList.push_back(curTrip->tripID);
        curTrip->setPrevData(nextFreeLocation, nextFreeTime);
        curTrip->hasGotTruck = true;
        nextFreeLocation = curTrip->endLocation;
        nextFreeTime = startTime + curTrip->tripDuration();
        return extraDist;
    }
    void popLastTrip(Trip *curTrip){
        nextFreeLocation = curTrip->truckPrevLocation;
        nextFreeTime = curTrip->truckPrevTime;
        curTrip->hasGotTruck = false;
        tripIDList.pop_back();
    }

    bool isfitTrip(Trip curTrip){
        int extraDist = getDistance(nextFreeLocation, curTrip.startLocation);
        int reqTime = distanceToTime(extraDist) + max(getCurTime(), nextFreeTime);
        ///After this time we will reach to startLocation of curTrip
        int startTime = max(reqTime, curTrip.earliestStartTime);
        if(startTime + curTrip.tripDuration() <= curTrip.reachTimeLimit) return true;
        else return false;
    }
};
