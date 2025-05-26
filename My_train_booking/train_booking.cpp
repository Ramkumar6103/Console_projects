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

    Passenger(String name, int age, char pref){
        this->id = ++idCount;
        this->name = name;
        this->age = age;
        this->preference = pref;
        this->ticketType = 'None';
        this->seatNumber = -1;
    }

    // Getters

    int getId() const {
        return id;;
    }
    string getName() const {
        return name;
    }
    int getAge() const {
        return age;
    }
    char getPreference() const {
        return preference;
    }
    string getTicketType() const {
        return ticketType;
    }
    int getSeatNumber() const {
        return seatNumber;
    }

    // Setter 

    void setId(const int& value) {
        Passenger::idProvider = value;
    }
    void setPreference(const char& value) {
        preference = value;
    }
    void setTicketType(const string& value) {
        ticketType = value;
    }
    void setSeatNumber(const & value) {
        seatNumber = value;
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

    vector<Passenger*> confirmed;
    queue<Passenger*> racList;
    queue<Passenger*> waitingList;

    short upper = 2, lower = 2, middle = 2;
    short rac = 1, waiting = 1;

    void ticketBooking();
    void ticketCancel(int id);
    void displayTickets();
    void displayRac();
    void displayWaiting();
};



// Main function

int main(){
    cout<<"SRS TRAIN BOOKING CENTER:\n";
    cout<<Passenger::getProviders()<<endl;
    bool loop = true;
    short choice;
    while(loop){
        cout<<"\nMenu :\n 1) Book Ticket\n 2) Cancel Ticket\n 3) Display Confirmed\n 4) Display RAC\n 5) Display Waiting List\n 6) Exit\n";
        cout<<"Enter your choice:\n";
        cin>>choice;
        switch(choice){
            case 1:{
                cout<<"Booking tickets";
                break;
            }
            case 2:{
                cout<<"Cancel tickets";
                break;
            }
            case 3:{
                cout<<"Display Confirmed";
                break;
            }
            case 4:{ 
                cout<<"Display RAC";
                break;
            }
            case 5:{
                cout<<"Display waiting list";
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