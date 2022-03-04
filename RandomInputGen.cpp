class RandomInputGen{
    int numPlaces;
    public:
    RandomInputGen(int numPlaces){
        this->numPlaces = numPlaces;
    }

    void addTrucks(vector<Truck> &truckList, int count){
        while(count--){
            int truckID = truckList.size();
            int loc = rand() % numPlaces + 1;
            Truck newTruck(truckID, loc);
            truckList.push_back(newTruck);
        }
    }

    Trip makeTrip(int id){///Makes a single Trip with random values.
        int locA = rand() % numPlaces + 1;
        int locB = rand() % numPlaces + 1;
        while(locA == locB){///Potiantial Infinity Loop;
            locB = rand() % numPlaces + 1;
        }

        Trip newTrip(id, locA, locB);
        int timeLen = 20, timeD = 2;
        int startTime = getCurTime() + rand()% timeLen;
        int endTime = startTime + 2 * newTrip.tripDuration() +  rand()% timeLen + timeD;
        newTrip.setTime(startTime, endTime);
        newTrip.printTripData();
        return newTrip;
    }

    void addTrips(vector<Trip> &tripList, int count){
        cout<<"Generated Trips:"<<endl;
        while(count--){
            int tripID = tripList.size();
            tripList.push_back(makeTrip(tripID));
        }
        cout<<endl;
    }

};
