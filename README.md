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

## Dependencies
- Pulseaudio

## Installation

## How to use
Running
`` `timer50yen` ``
will prompt you to press SPACE to start the stopwatch, you can then press SPACE again to stop the stopwatch - terminating the program.

Running
`` `timer50yen HhMmSs` `` E.g. `` `timer50yen 0h30m30s` ``
will create a timer for the specified amount of time. After this time is up an alarm sound is played and the program is terminated.