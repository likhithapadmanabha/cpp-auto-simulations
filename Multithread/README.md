*************LOCK_GUARD AND ATOMIC*************
This project simulates how automotive signals (like speed & RPM) between ECU and HMI using multithreading.

std::lock_guard make sures thread-safe access to the shared resource i.e.,signal table.

std::atomic is used for a brake flag to stop all threads safely.
ECU thread updates signals, HMI thread reads them, and middleware ensures safe communication.
When brake is applied, threads stop, showing real-time use of atomic & lock_guard.

*************CONTIONAL_VARIABLE*************
Simulates a car infotainment system where:

Loader thread loads songs into a shared queue.
Player thread waits until songs are available and plays them.
Uses mutex + condition_variable for safe coordination.
