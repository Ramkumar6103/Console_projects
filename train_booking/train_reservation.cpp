// #include <iostream>
// #include <vector>
// #include <queue>
// #include <unordered_map>
// #include <string>

#include<bits/stdc++.h>
using namespace std;

class Passenger {
    static int idProvider;
    int id;
    string name;
    int age;
    char preference;
    string ticketType;
    int seatNumber;

public:
    Passenger(string name, int age, char preference)
        : name(name), age(age), preference(preference) {
        id = ++idProvider;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    char getPreference() const { return preference; }
    string getTicketType() const { return ticketType; }
    int getSeatNumber() const { return seatNumber; }

    void setTicketType(string type) { ticketType = type; }
    void setSeatNumber(int number) { seatNumber = number; }
    void setPreference(char p) { preference = p; }

    void display() const {
        cout << "Passenger Ticket ID: " << id << "\n"
             << "Name: " << name << "\nAge: " << age 
             << "\nSeat Number: " << seatNumber 
             << "\nPreference: " << preference << "\n";
    }

    friend class TicketBooking;
    friend class TicketCanceling;
};

int Passenger::idProvider = 0;

class TicketCanceling;

class TicketBooking {
    static const int berthLimit = 2;
    static const int racLimit = 1;
    static const int waitingLimit = 1;

    static int upperSeatNumber;
    static int middleSeatNumber;
    static int lowerSeatNumber;

    static vector<Passenger*> confirmedList;
    static vector<Passenger*> upperList;
    static vector<Passenger*> middleList;
    static vector<Passenger*> lowerList;

    static queue<Passenger*> racQueue;
    static queue<Passenger*> waitingQueue;

    static unordered_map<int, char> seatNumberWithBerth;

    static void availableList() {
        cout << "Available Seats:\n";
        cout << "Upper: " << berthLimit - upperList.size() << "\n";
        cout << "Middle: " << berthLimit - middleList.size() << "\n";
        cout << "Lower: " << berthLimit - lowerList.size() << "\n";
    }

    static void getSeatDetails(Passenger* p) {
        for (auto& entry : seatNumberWithBerth) {
            if (entry.second == p->getPreference()) {
                p->seatNumber = entry.first;
                seatNumberWithBerth.erase(entry.first);
                return;
            }
        }
    }

    static bool checkAvailability(Passenger* p) {
        if (p->getPreference() == 'U' && upperList.size() < berthLimit) {
            if (!seatNumberWithBerth.empty()) getSeatDetails(p);
            else p->seatNumber = upperSeatNumber, upperSeatNumber += 3;
            upperList.push_back(p);
            return true;
        } else if (p->getPreference() == 'M' && middleList.size() < berthLimit) {
            if (!seatNumberWithBerth.empty()) getSeatDetails(p);
            else p->seatNumber = middleSeatNumber, middleSeatNumber += 3;
            middleList.push_back(p);
            return true;
        } else if (p->getPreference() == 'L' && lowerList.size() < berthLimit) {
            if (!seatNumberWithBerth.empty()) getSeatDetails(p);
            else p->seatNumber = lowerSeatNumber, lowerSeatNumber += 3;
            lowerList.push_back(p);
            return true;
        }
        return false;
    }

    static bool updateRAC(Passenger* p) {
        if (racQueue.size() < racLimit) {
            p->setTicketType("rac");
            racQueue.push(p);
            return true;
        }
        return false;
    }

    static bool updateWaiting(Passenger* p) {
        if (waitingQueue.size() < waitingLimit) {
            p->setTicketType("waiting");
            waitingQueue.push(p);
            return true;
        }
        return false;
    }

public:
    static void bookTicket(Passenger* p) {
        if (upperList.size() == berthLimit &&
            middleList.size() == berthLimit &&
            lowerList.size() == berthLimit) {

            if (updateRAC(p)) {
                cout << "Added to RAC. Ticket ID: " << p->getId() << "\n";
            } else if (updateWaiting(p)) {
                cout << "Added to Waiting List. Ticket ID: " << p->getId() << "\n";
            } else {
                cout << "No Tickets Available.\n";
                delete p;
            }
        } else if (checkAvailability(p)) {
            p->setTicketType("berth");
            confirmedList.push_back(p);
            cout << "Booking Confirmed. Ticket ID: " << p->getId() << "\n";
        } else {
            cout << "Preferred berth not available.\n";
            availableList();
            delete p;
        }
    }

    static void displayConfirmed() {
        cout << "--- Confirmed Tickets ---\n";
        for (auto p : confirmedList) p->display();
    }

    static void displayRAC() {
        cout << "--- RAC List ---\n";
        for (queue<Passenger*> q = racQueue; !q.empty(); q.pop()) q.front()->display();
    }

    static void displayWaiting() {
        cout << "--- Waiting List ---\n";
        for (queue<Passenger*> q = waitingQueue; !q.empty(); q.pop()) q.front()->display();
    }

    friend class TicketCanceling;
};

int TicketBooking::upperSeatNumber = 1;
int TicketBooking::middleSeatNumber = 2;
int TicketBooking::lowerSeatNumber = 3;
vector<Passenger*> TicketBooking::confirmedList;
vector<Passenger*> TicketBooking::upperList;
vector<Passenger*> TicketBooking::middleList;
vector<Passenger*> TicketBooking::lowerList;
queue<Passenger*> TicketBooking::racQueue;
queue<Passenger*> TicketBooking::waitingQueue;
unordered_map<int, char> TicketBooking::seatNumberWithBerth;

class TicketCanceling : public TicketBooking {
    static char canceledPreference;
    static int canceledSeatNumber;

    static void deletePassenger(Passenger* p) {
        auto& list = (p->getPreference() == 'U') ? upperList : (p->getPreference() == 'M') ? middleList : lowerList;
        confirmedList.erase(remove(confirmedList.begin(), confirmedList.end(), p), confirmedList.end());
        list.erase(remove(list.begin(), list.end(), p), list.end());
        delete p;
    }

    static void promoteRAC() {
        if (!racQueue.empty()) {
            Passenger* p = racQueue.front();
            racQueue.pop();
            p->setSeatNumber(canceledSeatNumber);
            p->setPreference(canceledPreference);
            p->setTicketType("berth");
            confirmedList.push_back(p);
            if (canceledPreference == 'U') upperList.push_back(p);
            else if (canceledPreference == 'M') middleList.push_back(p);
            else lowerList.push_back(p);
            seatNumberWithBerth.erase(canceledSeatNumber);
        }
        canceledSeatNumber = 0;
        canceledPreference = '\0';
    }

    static void promoteWaiting() {
        if (!waitingQueue.empty()) {
            Passenger* p = waitingQueue.front();
            waitingQueue.pop();
            p->setTicketType("rac");
            racQueue.push(p);
        }
    }

public:
    static string cancel(int id) {
        for (auto it = confirmedList.begin(); it != confirmedList.end(); ++it) {
            if ((*it)->getId() == id) {
                canceledPreference = (*it)->getPreference();
                canceledSeatNumber = (*it)->getSeatNumber();
                seatNumberWithBerth[canceledSeatNumber] = canceledPreference;
                deletePassenger(*it);
                promoteRAC();
                promoteWaiting();
                return "Ticket Cancelled Successfully.";
            }
        }

        queue<Passenger*> tempRAC;
        bool found = false;
        while (!racQueue.empty()) {
            Passenger* p = racQueue.front(); racQueue.pop();
            if (!found && p->getId() == id) {
                delete p;
                found = true;
                continue;
            }
            tempRAC.push(p);
        }
        racQueue = tempRAC;
        if (found) {
            promoteWaiting();
            return "RAC Ticket Cancelled Successfully.";
        }

        queue<Passenger*> tempWait;
        while (!waitingQueue.empty()) {
            Passenger* p = waitingQueue.front(); waitingQueue.pop();
            if (p->getId() == id) {
                delete p;
                return "Waiting Ticket Cancelled Successfully.";
            }
            tempWait.push(p);
        }
        waitingQueue = tempWait;

        return "Invalid Ticket ID.";
    }
};

char TicketCanceling::canceledPreference = '\0';
int TicketCanceling::canceledSeatNumber = 0;

// ========== MAIN FUNCTION ==========
int main() {
    bool loop = true;
    while (loop) {
        cout << "\nChoose an option:\n1. Book Ticket\n2. Cancel Ticket\n3. Display Confirmed\n4. Display RAC\n5. Display Waiting\n6. Exit\n";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                string name;
                int age;
                char pref;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter age: ";
                cin >> age;
                cout << "Enter berth preference (U/M/L): ";
                cin >> pref;
                if (pref == 'U' || pref == 'M' || pref == 'L') {
                    Passenger* p = new Passenger(name, age, pref);
                    TicketBooking::bookTicket(p);
                } else {
                    cout << "Invalid berth preference.\n";
                }
                break;
            }
            case 2: {
                int id;
                cout << "Enter ticket ID to cancel: ";
                cin >> id;
                cout << TicketCanceling::cancel(id) << "\n";
                break;
            }
            case 3:
                TicketBooking::displayConfirmed();
                break;
            case 4:
                TicketBooking::displayRAC();
                break;
            case 5:
                TicketBooking::displayWaiting();
                break;
            case 6:
                loop = false;
                cout << "Thank you for using the system!\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    }
    return 0;
}
