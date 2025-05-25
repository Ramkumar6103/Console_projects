#include<bits/stdc++.h>
using namespace std;
class Passenger{
    private:
    static int idProvider = 0;
    int id;
    string name;
    int age;
    char preference;
    string ticketType;    
    int seatNumber;

    public:
        Passengers(string name,int age, char preference){
            this->id = ++idProvider;
            this->name = name;
            this->age = age;
            this->preference = preference;
        }
        int getId() const {
            return id;
        }
        void setId(const int& value) {
            Passenger.idProvider = value;
        }
        string getName() const {
            return name;
        }
        void set(const string& value) {
            this->name = value;
        }
        int getAge() const {
            return age;
        }
        void setAge(const int& value) {
            this->age = value;
        }
        char getPreference() const {
            return preference;
        }
        void set(const char& value) {
            this->preference = value;
        }
        string getTicketType() const {
            return ticketType;
        }
        void set(const string& value) {
            this->ticketType = value;
        }
        int getSeatNumber() const {
            return seatNumber;
        }
        void setSeatNumber(const int& value) {
            this->seatNumber = value;
        }


};