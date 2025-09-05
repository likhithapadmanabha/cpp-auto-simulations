#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

mutex mtx;
condition_variable cv;
queue<string> playlist;  // shared song queue
bool finished = false;   // signal when loading is done

void loader() {
    // Simulate loading 3 songs from USB
    string songs[] = {"Song1.mp3", "Song2.mp3", "Song3.mp3"};
    for (auto& s : songs) {
        this_thread::sleep_for(1s); // simulate load delay
        {
            lock_guard<mutex> lock(mtx);
            playlist.push(s);
            cout << "Loaded: " << s << endl;
        }
        cv.notify_one(); // notify player that a song is ready
    }

    // Mark loading complete
    {
        lock_guard<mutex> lock(mtx);
        finished = true;
    }
    cv.notify_one();
}

void player() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !playlist.empty() || finished; });

        while (!playlist.empty()) {
            string current = playlist.front();
            playlist.pop();
            lock.unlock(); // unlock while "playing"
            cout << "Now Playing: " << current << endl;
            this_thread::sleep_for(2s); // simulate play duration
            lock.lock();
        }

        if (finished && playlist.empty()) break;
    }
}

int main() {
    thread t1(loader);
    thread t2(player);

    t1.join();
    t2.join();

    cout << "All songs played!" << endl;
    return 0;
}
