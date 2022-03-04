#include <bits/stdc++.h>
#include "Utility.cpp"
#include "Trip.cpp"
#include "Truck.cpp"
#include "randomInputGen.cpp"
#define P(X) cout<<"db "<<X<<endl;
#define P2(X,Y) cout<<"d2 "<<X<<" "<<Y<<endl;
#define P3(X,Y,Z) cout<<"d3 "<<X<<" "<<Y<<" "<<Z<<endl;
#define SQ(x) ((x) * (x))

#define ll long long
#define pii pair<int,int>

#define bchk(n,i) (bool)(n&(1<<i))
#define bon(n,i) (n|(1<<i))
#define boff(n,i) n=n&(~(1<<i))

#define distance(a,b) (sq(a.x-b.x) + sq(a.y-b.y))
#define MAX3(a,b,c) max(a,max(b,c))
#define MS(XX,YY) memset(XX,YY,sizeof(XX));
#define FastIO ios_base::sync_with_stdio(0);cin.tie(nullptr);
#define eps 10e-9
#define MX 1000005
#define MD 1000000007

using namespace std;
ll m,n;

vector<Trip> tripList;
vector<Truck> truckList;
vector<Truck> optimalTruckList;

int optimalExtraDistNow = INT_MAX;
int maxAssignableTrip = 0, numTripTarget;
void assignTripsToTruck(int assignedTripsCnt, int extraDist){
    if(optimalExtraDistNow <= extraDist){
        return; // already not optimal;
    }
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
                ///We will move this part later.
                /// we will use an priority Queue here.
                int extraDistHere = truckList[j].addTrip(&tripList[i]);
                assignTripsToTruck(assignedTripsCnt + 1, extraDist + extraDistHere);
                truckList[j].popLastTrip(&tripList[i]);
            }
        }
    }
    /// Look after case where we fail to assign trucks for some trip.
}
int main()
{
    ll i,j,test=1,cas=0;
    ll a,b;
    RandomInputGen inputGen(70);
    inputGen.addTrucks(truckList, 4);
    inputGen.addTrips(tripList, 6);

    numTripTarget = tripList.size();
    assignTripsToTruck(0, 0);

    if(maxAssignableTrip < tripList.size()){
        numTripTarget = maxAssignableTrip;
        assignTripsToTruck(0, 0);
    }

    cout<<numTripTarget<<" Trips assigned out of "<<tripList.size()<<" trips"<<endl;
    cout<<"Total distance without load is: "<< optimalExtraDistNow<<endl;

    for(Truck truck: optimalTruckList){
        truck.printRoute(tripList);
    }
	#ifndef ONLINE_JUDGE
    freopen("test.txt","r",stdin);
	#endif

    return 0;
}



