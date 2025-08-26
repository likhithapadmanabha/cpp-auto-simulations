# Design Patterns (C++)

This folder contains small, runnable examples of common patterns with brief explanations.

- `singleton_audio_demo.cpp` — Singleton using a mock `AudioManager` (infotainment style).
- "playList" is the shared resource between gps and music threads, hence we are using mutex to handle the race condition.
- in real time infotainment systmes only one AudioManager will be used to handle the audio, hence we have used Singleton design pattern.

## Build
```bash
g++ -std=c++17 DesignPatterns/singleton_audio_demo.cpp -o singleton_demo
./singleton_demo
