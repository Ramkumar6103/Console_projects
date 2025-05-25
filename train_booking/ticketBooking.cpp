#include<bits/stdc++.h>
using namespace std;
class TicketBooking{
    static int berthLiimit = 2;
    static int racLimit = 1;
    static int waitingLimit = 1;

    static int upperSeatNumber = 1;
    static int middleSeatNumber = 2;
    static int lowerSeatNumber = 3;

    vector<Passenger> confirmedList;

    vector<Passenger> upperSeat;
    vector<Passenger> middleSeat;
    vector<Passenger> lowerSeat;

    queue<Passenger> racQueue;
    queue<Passenger> waitingQueue;
};