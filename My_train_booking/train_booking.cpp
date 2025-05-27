#include<bits/stdc++.h>
using namespace std;

// Passenger class

class Passenger{

public:
    static int idCount;
    int id;
    string name;
    int age;
    char preference;
    string ticketType;
    int seatNumber;
    public:    
    static int getProviders(){
        return idCount;
    }

    Passenger(string name, int age, char pref){
        this->id = ++idCount;
        this->name = name;
        this->age = age;
        this->preference = pref;
        this->ticketType = "None";
        this->seatNumber = -1;
    }

    void display() const {
        cout << "Passenger Ticket ID: " << id << "\n"
             << "Name: " << name << "\nAge: " << age 
             << "\nSeat Number: " << seatNumber 
             << "\nPreference: " << preference << "\n";
    }
};
int Passenger::idCount = 0;

// Booking System class

class BookingSystem{
private:
    vector<Passenger*> confirmed;
    queue<Passenger*> racList;
    queue<Passenger*> waitingList;
    unordered_map<int,char> seatMap;
    short upper = 2, lower = 2, middle = 2;
    short rac = 1, waiting = 1;
    short seatNumberCounter = 1;
public:
    void ticketBooking();
    void ticketCancel(int id);
    void displayConfirmed();
    void displayRac();
    void displayWaiting();
};

// Ticket Booking function

void BookingSystem::ticketBooking(){
    int age;
    string name;
    char pref;
    cout<<"Seat availability :";
    cout<<"\nUpper :"<<upper;
    cout<<"\nMiddle :"<<middle;
    cout<<"\nLower : "<<lower;
    cout<<endl;
    cout<<"Enter your name:";
    cin>>name;
    cout<<"Enter your age:";
    cin>>age;
    cout<<"Enter your seat preference:";
    cin>>pref;

    Passenger* p = new Passenger(name, age, pref);
    if((pref == 'U' || pref == 'u') && upper > 0){
        p->seatNumber = seatNumberCounter++;
        p->ticketType = "Confirmed";
        seatMap[p->seatNumber] = 'U';
        upper--;
    }
    else if((pref == 'M' || pref == 'm') && middle > 0){
        p->seatNumber = seatNumberCounter++;
        p->ticketType = "Confirmed";
        seatMap[p->seatNumber] = 'M';
        middle--;
    }
    else if((pref == 'L' || pref == 'l') && lower > 0){
        p->seatNumber = seatNumberCounter++;
        p->ticketType = "Confirmed";
        seatMap[p->seatNumber] = 'L';
        lower--;
    }
    else if(rac > 0){
        p->ticketType = "RAC";
        racList.push(p);
        rac--;
    }
    else if(waiting > 0){
        p->ticketType = "Waiting";
        waitingList.push(p);
        waiting--;
    }
    else{
        cout<<"Tickets are not available";
        delete(p);
        return;
    }

    if(p->ticketType == "Confirmed"){
        confirmed.push_back(p);
    }

    cout<<"Ticket booking id : "<<p->id<<", Ticket type : "<<p->ticketType;
    if(p->seatNumber != -1){
        cout<<"\nSeat Number : "<<p->seatNumber;
    }
    cout<<endl;
}

// Ticket Cancelling function

void BookingSystem::ticketCancel(int id){
    bool found = false;
    for(int i=0;i<confirmed.size();i++){
        if(confirmed[i]->id == id){
            Passenger* p = confirmed[i];
            char seatType = seatMap[p->seatNumber];

            // Free up seat
            if(seatType == 'U') upper++;
            else if(seatType == 'M') middle++;
            else if(seatType == 'L') lower++;

            seatMap.erase(p->seatNumber);
            delete(confirmed[i]);
            confirmed.erase(confirmed.begin() + i);
            found = true;

            // Rac to confirmed list
            if(!racList.empty()){
                Passenger* p = racList.front();
                racList.pop();
                rac++;
                p->seatNumber = seatNumberCounter++;
                p->ticketType = "Confirmed";
                confirmed.push_back(p);
                seatMap[p->seatNumber] = seatType;

                if(!waitingList.empty()){
                    Passenger* p = waitingList.front();
                    waitingList.pop();
                    waiting++;
                    p->ticketType = "RAC";
                    racList.push(p);
                    rac--;
                    waiting--;
                }
            }
            cout<<"Ticket cancelled successfully";
            return;
        }
    }
        queue<Passenger* >racQue;
        while(!racList.empty()){
            Passenger* p = racList.front();
            racList.pop();
            if(p->id == id){
                rac++;
                delete(p);
                cout<<"RAC ticket deleted";
                found = true;
                if(!waitingList.empty()){
                    Passenger* p1 = waitingList.front();
                    waitingList.pop();
                    waiting++;
                    p1->ticketType = "RAC";
                    racList.push(p1);
                    rac--;
                    waiting--;
                }
                return;
            }
            else{
                racQue.push(p);
            }
        }
        racList = racQue;

        queue<Passenger* >waitingQue;
        while(!waitingList.empty()){
            Passenger *p = waitingList.front();
            waitingList.pop();
            if(p->id == id){
                delete(p);
                waiting++;
                cout<<"RAC ticket deleted";
                found = true;
                return;
            }
            else{
                waitingQue.push(p);
            }
        }
        waitingList = waitingQue;

        if(!found){
            cout << "Ticket ID not found.\n";
        }
}

void BookingSystem::displayConfirmed(){
    if(confirmed.empty()){
        cout<<"No tickets have been booked yet...!";
    }
    else{
        cout<<"Confirmed Tickets : \n";
        for(auto it : confirmed){
        cout<<"Id : "<<it->id<<" Name : "<<it->name<<" Seat Number : "<<it->seatNumber<<" Ticket type : "<<it->ticketType<<endl;
    }
    }
}

void BookingSystem::displayRac(){
    if(racList.empty()){
        cout<<"No passengers in RAC queue.";
    }
    else{
        cout<<"Rac Tickets : \n";
        queue<Passenger*> p = racList;
        while(!p.empty()){
        Passenger* it = p.front();
        p.pop();
        cout<<"Id : "<<it->id<<" Name : "<<it->name<<" Ticket type : "<<it->ticketType<<endl;
        }
    }
}

void BookingSystem::displayWaiting(){
    if(waitingList.empty()){
        cout<<"No tickets are on the waiting list";
    }
    else{
        cout<<"Waiting Tickets : \n";
        queue<Passenger*> p = waitingList;
        while(!p.empty()){
        Passenger* it = p.front();
        p.pop();
        cout<<"Id : "<<it->id<<" Name : "<<it->name<<" Ticket type : "<<it->ticketType<<endl;
        }
    }
}

// Main function

int main(){
    cout<<"\n--------------------RAM TRAIN BOOKING CENTER------------------------\n";
    //cout<<Passenger::getProviders()<<endl;

    BookingSystem bs;
    bool loop = true;
    short choice;
    while(loop){
        cout<<"\nMenu :\n 1) Book Ticket\n 2) Cancel Ticket\n 3) Display Confirmed\n 4) Display RAC\n 5) Display Waiting List\n 6) Exit\n";
        cout<<"Enter your choice:\n";
        cin>>choice;
        switch(choice){
            case 1:{
                bs.ticketBooking();
                break;
            }
            case 2:{
                int id;
                cout<<"Enter your id : ";
                cin>>id;
                bs.ticketCancel(id);
                break;
            }
            case 3:{
                bs.displayConfirmed();
                break;
            }
            case 4:{ 
                bs.displayRac();
                break;
            }
            case 5:{
                bs.displayWaiting();
                break;
            }
            case 6:{
                loop = false;
                break;
            }
            default:{
                cout<<"Invalid input";
            }
        }
    }
    return 0;
}