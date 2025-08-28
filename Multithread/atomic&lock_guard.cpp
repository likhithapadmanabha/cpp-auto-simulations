#include <iostream>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>

std::unordered_map<int, double> signalTable;
std::mutex signalMutex;
std::atomic<bool> brakeApplied(false);  // Brake flag

// Update signal
void updateSignal(int id, double value) {
    std::lock_guard<std::mutex> lock(signalMutex);
    signalTable[id] = value;
}

// Get latest signal
double getSignal(int id) {
    std::lock_guard<std::mutex> lock(signalMutex);
    return signalTable[id];
}

// ECU thread -> Updates speed & RPM
void ecuThread() {
    double speed = 0;
    double rpm   = 800;  // idle RPM

    while (!brakeApplied) {  // run until brake is applied
        if (speed < 120) {
            speed += 5;   // accelerate
            rpm += 200;
        } else {
            speed = 0;    // reset after max
            rpm = 800;
        }

        updateSignal(0x100, speed); 
        updateSignal(0x200, rpm);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Brake pressed -> set values to 0
    updateSignal(0x100, 0);   // speed = 0
    updateSignal(0x200, 800); // idle RPM
    std::cout << "🚗 Brake applied! Vehicle stopped.\n";
}

// HMI thread -> reads & displays
void hmiThread() {
    while (!brakeApplied) {
        double speed = getSignal(0x100);
        double rpm   = getSignal(0x200);

        std::cout << "Speed: " << speed << " km/h | RPM: " << rpm << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::thread ecu(ecuThread);
    std::thread hmi(hmiThread);

    // Simulate driver pressing brake after 25 seconds
    std::this_thread::sleep_for(std::chrono::seconds(25));
    brakeApplied = true;

    ecu.join();
    hmi.join();
    return 0;
}
