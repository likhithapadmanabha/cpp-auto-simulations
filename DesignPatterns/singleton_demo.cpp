#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

// Singleton: Only one AudioManager
class AudioManager {
private:
    static AudioManager* instance;
    AudioManager() {}
public:
    static AudioManager* getInstance() {
        static AudioManager instance;
        return &instance;
    }
    void playSound(const std::string& sound) {
        std::cout << "[Audio] Playing: " << sound << std::endl;
    }
};

AudioManager* AudioManager::instance = nullptr;

// GPS thread
void gpsTask() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "[GPS] Turn left after 300m" << std::endl;
    AudioManager::getInstance()->playSound("Navigation alert");
}

// Music thread
void musicTask() {
    std::vector<std::string> playlist = {"Song A", "Song B", "Song C"};
    for (const auto& song : playlist) {
        std::cout << "[Music] Now playing: " << song << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main() {
    std::thread gps(gpsTask);
    std::thread music(musicTask);

    gps.join();
    music.join();

    std::cout << "System shutting down." << std::endl;
}
