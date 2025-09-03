#include <iostream>
using namespace std;

class CarAudio {
private:
    int volume;   // Encapsulation: hidden data

    // Hidden low-level function (not exposed to user)
    void applyVolumeToAmplifier() {
        cout << "[System] Amplifier set to " << volume << endl;
    }

public:
    CarAudio() : volume(10) {}

    // Abstraction: expose only high-level behavior
    void increaseVolume() {
        if (volume < 100) {
            volume++;
            applyVolumeToAmplifier();
        }
    }

    void decreaseVolume() {
        if (volume > 0) {
            volume--;
            applyVolumeToAmplifier();
        }
    }

    int getVolume() const {   // safe getter
        return volume;
    }
};

int main() {
    CarAudio audio;
    audio.increaseVolume();   // user just calls high-level function
    audio.increaseVolume();
    audio.decreaseVolume();

    cout << "Current Volume: " << audio.getVolume() << endl;
}
