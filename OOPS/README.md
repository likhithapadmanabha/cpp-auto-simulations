
***********DYNAMIC POLYMORPHISM***********
This code demonstrates dynamic polymorphism in C++ using a vehicle alert system.
Different alerts (Seatbelt, Door, Handbrake) are implemented as derived classes of a common Notification interface.
At runtime, the system decides which alert to show based on simulated sensor event
Real-world analogy → Car dashboard shows alerts based on active sensor

Note: virtual ~Notification() = default; 
      is used so that when deleting derived objects through a base pointer, the correct destructor is called. This prevents resource leaks and is a best practice            whenever a class has virtual functions.
      virtual makes the destructor call dynamic (runtime) instead of static (compile time).
      That’s why both derived and base destructors get executed in the right order.


***********ENCAPSULATION***********
volume is private → can’t directly set to -999.
Only controlled methods can change it.

***********ABSTRACTION***********
User calls increaseVolume() / decreaseVolume()
They don’t care about applyVolumeToAmplifier() (hidden low-level logic).

***********RAW POINTERS***********
Here I have tried to cover the below topics:
--> Passing pointers to functions → process(int* p).
--> Passing reference to pointer → clear(int*& p).
--> Memory Leak → forgetting to delete.
--> Dangling Pointer → accessing memory after delete.
