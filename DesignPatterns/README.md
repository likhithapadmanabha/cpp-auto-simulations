# Design Patterns (C++)

This folder contains small, runnable examples of common patterns with brief explanations.

- `singleton_audio_demo.cpp` — Singleton using a mock `AudioManager` (infotainment style).
- More patterns to add later: Factory, Observer, Strategy…

## Build
```bash
g++ -std=c++17 DesignPatterns/singleton_audio_demo.cpp -o singleton_demo
./singleton_demo
