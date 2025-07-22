# Timer50yen
A lightweight, basic timer with some added functionalities for the terminal

## Description
This project aims to create a **lightweight** timer that can run in the terminal. The intended features of the timer include the following:
- (*Complete*) Stopwatch
    - Count up in seconds
    - (*TBD*) Lap timing
    - (*TBD*) Reset capability
    - (*TBD*) Difference in time between laps
- (*Complete*) Timer
    - Count down from specified time
        - HhMmSs (e.g. 1h30m)
    - Alert when time has expired
        - Customisable sound

There is no reason to use this over any other timer/stopwatch application/package, this project exists for the purpose of learning C++.

### Planned additions
- Stopwatch
    - Lap timing
    - Reset capability
    - Difference in time between laps
- Timer
    - Progress bar along with seconds remaining
    - Better time formatting (HH:MM:SS)
    - Option for timer to go off at a specified time
- QoL
    - --help argument

## Dependencies
- Pulseaudio-utils

## Installation
### Fedora
Simply download the RPM file and run ``sudo dnf install path/to/your/timer50yen*.rpm``

### Ubuntu/Debian
```bash
# Install dependencies
sudo apt update
sudo apt install g++ pulseaudio-utils

# Clone, build and install
git clone https://github.com/luke50yen/timer50yen.git
cd timer50yen
make
sudo make install
```

### Arch Linux
```bash
# Install dependencies
sudo pacman -S gcc pulseaudio

# Clone, build and install
git clone https://github.com/luke50yen/timer50yen.git
cd timer50yen
make
sudo make install
```

### From Source (Any Linux)
```bash
# Make sure you have g++/gcc and pulseaudio-utils installed
git clone https://github.com/luke50yen/timer50yen.git
cd timer50yen
make
sudo make install
```


## How to use
Running
``  timer50yen  ``
will prompt you to press SPACE to start the stopwatch, you can then press SPACE again to stop the stopwatch - terminating the program.

Running
``  timer50yen HhMmSs  `` E.g. ``  timer50yen 0h30m30s  ``
will create a timer for the specified amount of time. After this time is up an alarm sound is played and the program is terminated.