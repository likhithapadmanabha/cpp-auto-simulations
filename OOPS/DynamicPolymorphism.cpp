#include <iostream>
#include <memory>
#include <cstdlib>  // rand()
#include <ctime>    // time()
using namespace std;

// Base class
class Notification {
public:
    virtual void notify() = 0;
    virtual ~Notification() = default;
};

// Derived classes
class SeatbeltNotification : public Notification {
public:
    void notify() override { cout << "⚠️  Seatbelt not fastened!" << endl; }
};

class DoorNotification : public Notification {
public:
    void notify() override { cout << "⚠️  Door is open!" << endl; }
};

class HandbrakeNotification : public Notification {
public:
    void notify() override { cout << "⚠️  Handbrake is engaged!" << endl; }
};

int main() {
    srand(time(nullptr));

    // Simulate random sensor event (1=seatbelt, 2=door, 3=handbrake)
    int sensorEvent = rand() % 3 + 1;

    unique_ptr<Notification> alert;

    if (sensorEvent == 1)
        alert = make_unique<SeatbeltNotification>();
    else if (sensorEvent == 2)
        alert = make_unique<DoorNotification>();
    else
        alert = make_unique<HandbrakeNotification>();

    cout << "Sensor triggered event: " << sensorEvent << endl;

    // Runtime decides which notify() is called
    alert->notify();

    return 0;
}
