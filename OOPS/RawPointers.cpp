#include <iostream>
using namespace std;

class Sensor {
public:
    // Allocates raw memory for one sensor reading
    int* readData(int value) {
        int* data = new int(value); 
        cout << "[Sensor] Allocated data: " << *data << endl;
        return data; 
    }
};

class Processor {
public:
    // Take pointer and process it
    void process(int* data) {
        if (data) {
            cout << "[Processor] Processing data: " << *data << endl; 
        }
    }

    // Free memory safely (reference to pointer)
    void clear(int*& data) {
        delete data;  
        data = nullptr; 
        cout << "[Processor] Data cleared!" << endl;
    }
};

// Utility: simulate dangerous use of dangling pointer
void dangerousUse(int* data) {
    cout << "[Danger] Using dangling pointer: " << *data << endl;
}

int main() {
    Sensor sensor;
    Processor proc;

    // Step 1: Allocate raw sensor data
    int* sensorData = sensor.readData(80);

    // Step 2: Process it
    proc.process(sensorData);

    // Step 3: Free safely
    proc.clear(sensorData);

    // Step 4: Mistake - dereference after delete
    if (sensorData) {
        proc.process(sensorData);
    } else {
        cout << "[Main] sensorData is nullptr, safe from dangling." << endl;
    }

    // Step 5: Memory Leak 
    int* leakedData = sensor.readData(100);
    proc.process(leakedData);
    // forgot delete -> memory leak!

    return 0;
}
