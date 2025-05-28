#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

//
// ─── CLASS: Taxi ────────────────────────────────────────────────────────────────
//
class Taxi {
private:
    char currentLocation = 'A';
    int customerId;
    int taxiId;
    char pickupLocation;
    char dropLocation;
    int pickupTime;
    int dropTime;
    int earnings;

public:
    // Setters
    void setCurrentLocation(char loc) { currentLocation = loc; }
    void setCustomerId(int id) { customerId = id; }
    void setTaxiId(int id) { taxiId = id; }
    void setPickupLocation(char loc) { pickupLocation = loc; }
    void setDropLocation(char loc) { dropLocation = loc; }
    void setPickupTime(int time) { pickupTime = time; }
    void setDropTime(int time) { dropTime = time; }
    void setEarnings(int amount) { earnings = amount; }

    // Getters
    char getCurrentLocation() const { return currentLocation; }
    int getCustomerId() const { return customerId; }
    int getTaxiId() const { return taxiId; }
    char getPickupLocation() const { return pickupLocation; }
    char getDropLocation() const { return dropLocation; }
    int getPickupTime() const { return pickupTime; }
    int getDropTime() const { return dropTime; }
    int getEarnings() const { return earnings; }

    // Clone function (deep copy)
    Taxi clone() const {
        return *this;
    }

    // Display taxi information
    void display() const {
        cout << "Taxi " << taxiId << "\ncurrentLocation = " << currentLocation
             << ", \ncustomerId = " << customerId
             << ", \npickupLocation = " << pickupLocation
             << ", \ndropLocation = " << dropLocation
             << ", \npickupTime = " << pickupTime
             << ", \ndropTime = " << dropTime
             << ", \nearnings = " << earnings << "\n";
    }
};

//
// ─── CLASS: TaxiBooking ─────────────────────────────────────────────────────────
//
class TaxiBooking {
private:
    static vector<Taxi> taxiList;
    static vector<Taxi> taxiBookedHistory;
    static const int taxiListLimit = 4;
    static int idGenerator;

public:
    static string booking(char pickupLocation, char dropLocation, int pickupTime) {
        if (taxiList.size() < taxiListLimit) {
            taxiList.push_back(Taxi());
        }

        int min = INT_MAX;
        Taxi* taxiReady = nullptr;

        for (auto& t : taxiList) {
            if (t.getDropTime() <= pickupTime) {
                int distance = abs(pickupLocation - t.getCurrentLocation());
                if (distance < min) {
                    taxiReady = &t;
                    min = distance;
                } else if (distance == min && taxiReady != nullptr && t.getEarnings() < taxiReady->getEarnings()) {
                    taxiReady = &t;
                }
            }
        }

        if (taxiReady != nullptr) {
            taxiReady->setCustomerId(idGenerator++);
            taxiReady->setPickupLocation(pickupLocation);
            taxiReady->setDropLocation(dropLocation);
            taxiReady->setPickupTime(pickupTime);

            int travelTime = abs(dropLocation - pickupLocation);
            taxiReady->setDropTime(pickupTime + travelTime);
            taxiReady->setCurrentLocation(dropLocation);

            int earnings = ((travelTime * 15) - 5) * 10 + 100;
            taxiReady->setEarnings(taxiReady->getEarnings() + earnings);
            taxiReady->setTaxiId((int)(taxiReady - &taxiList[0]) + 1);

            taxiBookedHistory.push_back(taxiReady->clone());

            return "Taxi number " + to_string(taxiReady->getTaxiId()) + " is booked!";
        }

        return "Taxis not available";
    }

    static void display() {
        cout << "-----------------\n";
        for (const auto& t : taxiBookedHistory) {
            t.display();
            cout << "-----------------\n";
        }
    }
};

// Initialize static members
vector<Taxi> TaxiBooking::taxiList;
vector<Taxi> TaxiBooking::taxiBookedHistory;
int TaxiBooking::idGenerator = 1;

//
// ─── MAIN FUNCTION ──────────────────────────────────────────────────────────────
//
int main() {
    bool loop = true;

    while (loop) {
        cout << "\nChoose any one\n1. Book Taxi\n2. Display Details\n3. Exit\n";
        int n;
        cin >> n;

        switch (n) {
            case 1: {
                char pickupLocation, dropLocation;
                int pickupTime;
                cout << "Enter Pickup Location: ";
                cin >> pickupLocation;
                cout << "Enter Drop Location: ";
                cin >> dropLocation;
                cout << "Enter Pickup Time: ";
                cin >> pickupTime;
                cout << TaxiBooking::booking(pickupLocation, dropLocation, pickupTime) << endl;
                break;
            }

            case 2: {
                TaxiBooking::display();
                break;
            }

            case 3: {
                loop = false;
                cout << "\tThank You!!!\n";
                break;
            }

            default: {
                cout << "Invalid option!\n";
                break;
            }
        }
    }

    return 0;
} 