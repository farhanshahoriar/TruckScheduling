class Trip{
    public:
    int tripID;
    int startLocation;
    int endLocation;
    int earliestStartTime;
    int reachTimeLimit;
    int assignedTruckID;
    bool hasGotTruck;
    int truckPrevLocation;
    int truckPrevTime;
    Trip(int tripID, int startLocation, int endLocation){
        this->tripID = tripID;
        this->startLocation = startLocation;
        this->endLocation = endLocation;
        hasGotTruck = false;
    }
    Trip(){
        hasGotTruck = false;
    }
    void printTripData(){
        printf("TripID: %d, startLocation: %d, endLocation: %d\n", tripID, startLocation, endLocation);
        printf("EarliestStartTime: %d, reachTimeLimit: %d, tripDuration: %d\n", earliestStartTime, reachTimeLimit, tripDuration());
    }
    void setTime(int earliestStartTime, int reachTimeLimit){
        this->earliestStartTime = earliestStartTime;
        this->reachTimeLimit = reachTimeLimit;
    }
    void setPrevData(int truckPrevLocation, int truckPrevTime){
        this->truckPrevLocation = truckPrevLocation;
        this->truckPrevTime = truckPrevTime;
    }

    int tripDuration(){
        int dist = getDistance(startLocation, endLocation);
        return distanceToTime(dist);
    }
};
