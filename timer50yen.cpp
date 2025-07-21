#include <iostream>
#include <chrono>
#include <cmath>
#include <string>

#include <termios.h> // For instant key detection
#include <unistd.h> // For instant key detection
#include <fcntl.h> // For non-blocking input
#include <csignal> // For signal handling (early exit causing terminal settings to change)

termios oldt; // Global variable to hold terminal settings

termios disable_terminal_buffering(){
    // Disable terminal buffering and echo (for instant key detection)
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    return oldt;
}

void restore_terminal(int signum) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl << "Terminal restored (signal " << signum << "). Exiting." << std::endl;
    exit(signum);
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

int parse_time(const std::string input){
    // If the input is correctly formatted, return the number of seconds 
    // Otherwise, return an error

    int hours = 0, minutes = 0, seconds = 0;
    int num = 0; // Stored integer to apply character operation to

    // Iterate through characters in the string
    for (int i = 0; i < input.size(); i++){

        if (isdigit(input[i])){
            num = num * 10 + (input[i] - '0');
        } else {
            if (tolower(input[i]) == 'h') hours = num;
            else if (tolower(input[i]) == 'm') minutes = num;
            else if (tolower(input[i]) == 's') seconds = num;
            else {
                // Unrecognised value
                std::cerr << "Error: Unrecognised value '" << input[i] << "' in provided timer argument.\n";
                return -1;
            }
            // reset num
            num = 0;
        }
    }

    int result = 3600 * hours + 60 * minutes + seconds;
    if (result == 0){
        std::cerr << "Error: '" << input << "' argument results in a timer countdown starting from 0\n";
    }
    return result;
}

void timer(float current_time){
    bool iterating = true;

    auto last_time = std::chrono::steady_clock::now();

    while(iterating){
        // Calculate time elapsed
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - last_time;
        current_time -= elapsed.count();
        last_time = now;

        // Display the current time
        std::cout << "\r" << "Time remaining (s): " << std::max(0.0f, std::round(current_time * 100) / 100) << std::flush;

        // Exit loop
        if (current_time <= 0){
            iterating = false;
        }

        usleep(10000);
    }
    std::cout << std::endl << "Timer complete" << std::flush;
}

int main(int argc, char* argv[]){ 

    oldt = disable_terminal_buffering();
    // Register signal handler
    std::signal(SIGINT, restore_terminal);
    std::signal(SIGTERM, restore_terminal);

    if (argc == 1){
        /// STOPWATCH MODE
        // Request space to start the stopwatch
        std::cout << "Press SPACE to start the timer...";
        char ch;
        do {
            ch = wait_for_key(' ');
        } while (ch != ' ');

        std::cout << "\r" << "Press SPACE to stop the timer..." << std::endl;

        // Run the stopwatch
        stopwatch();
    } else if (argc == 2){
        /// TIMER MODE
        int seconds = parse_time(argv[1]);

        // Exit program if bad input
        if (seconds == -1 || seconds == 0){
            restore_terminal(SIGTERM);
            return 1;
        }

        // Run the timer
        timer(seconds);
        system("paplay /usr/share/timer50yen/alarm.mp3");
    } else {
        /// ERROR MODE
    }
    

    // Restore terminal to not have instant key detection 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    std::cout << std::endl;

    return 0;
}
