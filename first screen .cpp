#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>

// ANSI color codes
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define BLINK   "\033[5m"

// Background colors
#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

const std::string LEGENDS_TEXT = R"(
 _      ______  _____  ______  _   _  _____   _____    ____  ______   _    _   ___   _      ____  _    _  _____  
| |    |  ____||  __ \|  ____|| \ | ||  __ \ / ____|  / __ \|  ____| | |  | | / _ \ | |    / __ \| |  | ||  __ \ 
| |    | |__   | |  | | |__   |  \| || |  | | (___   | |  | | |__    | |  | || | | || |   | |  | | |  | || |__) |
| |    |  __|  | |  | |  __|  | . ` || |  | |\___ \  | |  | |  __|   | |  | || | | || |   | |  | | |  | ||  _  / 
| |____| |____ | |__| | |____ | |\  || |__| |____) | | |__| | |      | |__| || |_| || |___| |__| | |__| || | \ \ 
|______|______||_____/|______||_| \_||_____/|_____/   \____/|_|       \____/  \___/ |______\____/ \____/ |_|  \_\
)";

void printWithAnimation(const std::string& text) {
    // Split text into lines
    std::string line;
    std::istringstream stream(text);
    
    // Rainbow colors array
    std::string colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
    int colorIndex = 0;
    
    while (std::getline(stream, line)) {
        for (char c : line) {
            // Cycle through colors for each character
            std::cout << BOLD << colors[colorIndex % 6] << c;
            colorIndex++;
            
            // Small delay for animation effect
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::cout << RESET << std::endl;
    }
}

void displayFancyTitle() {
    // Clear screen (works on most terminals)
    std::cout << "\033[2J\033[1;1H";
    
    // Display a colorful border
    std::string border(80, '*');
    std::cout << BOLD << YELLOW << border << RESET << std::endl;
    
    // Add some space
    std::cout << std::endl;
    
    // Display the animated title
    printWithAnimation(LEGENDS_TEXT);
    
    // Add some space
    std::cout << std::endl;
    
    // Display a blinking subtitle
    std::cout << BOLD << BLINK << CYAN << std::string(30, ' ') << "ADVENTURE AWAITS!" << RESET << std::endl;
    
    // Bottom border
    std::cout << std::endl;
    std::cout << BOLD << YELLOW << border << RESET << std::endl;
}
