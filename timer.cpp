#include <iostream>
#include <chrono>
#include <cmath>
#include <termios.h> // For instant key detection
#include <unistd.h> // For instant key detection
#include <fcntl.h> // For non-blocking input

termios disable_terminal_buffering(){
    // Disable terminal buffering and echo (for instant key detection)
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    return oldt;
}

void set_nonblocking(bool enable) {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (enable)
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    else
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

char wait_for_key(char target, bool nonblocking = false) {
    if (nonblocking) set_nonblocking(true);
    else set_nonblocking(false);
    char ch;
    ch = getchar();
    if (nonblocking) set_nonblocking(false);
    return ch;
}

void stopwatch(){
    float current_time = 0;
    bool iterating = true;

    set_nonblocking(true);
    auto last_time = std::chrono::steady_clock::now();
    while(iterating){
        
        // Calculate time elapsed
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - last_time;
        current_time += elapsed.count();
        last_time = now;

        // Display the time
        std::cout << "\r" << "Time (s): " << std::round(current_time * 100) / 100 << std::flush;

        // Get input
        if (wait_for_key(' ', true) == ' ') iterating = false;
        usleep(10000);

    }
}

int main(){ 
    termios oldt = disable_terminal_buffering();

    // Request space to start the stopwatch
    std::cout << "Press SPACE to start the timer...";
    char ch;
    do {
        ch = wait_for_key(' ');
    } while (ch != ' ');

    std::cout << "\r" << "Press SPACE to stop the timer..." << std::endl;

    // Run the stopwatch
    stopwatch();

    // Restore terminal to not have instant key detection 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    std::cout << std::endl;

    return 0;
}
