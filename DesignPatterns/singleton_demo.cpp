#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include <mutex>

// Singleton: AudioManager with shared playlist
class AudioManager {
private:
    std::queue<std::string> playlist;   // Shared resource
    std::mutex playlistMutex;           // Protects shared playlist

    AudioManager() {}
public:
    static AudioManager* getInstance() {
        static AudioManager instance;  // Thread-safe in C++11+
        return &instance;
    }

    // Add sound/music to playlist (shared resource)
    void addToPlaylist(const std::string& sound) {
        std::lock_guard<std::mutex> lock(playlistMutex);
        playlist.push(sound);
    }

    // Play next sound in playlist
    void playNext() {
        std::lock_guard<std::mutex> lock(playlistMutex);
        if (!playlist.empty()) {
            std::cout << "[Audio] Playing: " << playlist.front() << std::endl;
            playlist.pop();
        }
    }
};

// GPS thread: Adds navigation alerts to shared playlist
void gpsTask() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "[GPS] Turn left after 300m" << std::endl;
    AudioManager::getInstance()->addToPlaylist("Navigation alert");
}

// Music thread: Adds songs to shared playlist
void musicTask() {
    std::vector<std::string> songs = {"Song A", "Song B", "Song C"};
    for (const auto& song : songs) {
        std::cout << "[Music] Queued: " << song << std::endl;
        AudioManager::getInstance()->addToPlaylist(song);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

// Audio system thread: Plays from shared playlist
void audioTask() {
    for (int i = 0; i < 5; i++) { // Try playing 5 times
        AudioManager::getInstance()->playNext();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}

int main() {
    std::thread gps(gpsTask);
    std::thread music(musicTask);
    std::thread audio(audioTask);

    gps.join();
    music.join();
    audio.join();

    std::cout << "System shutting down." << std::endl;
}
