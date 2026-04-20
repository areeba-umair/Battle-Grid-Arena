#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
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

const std::string GAME_COMPLETED_TEXT = R"(
  _____          __  __ ______    _____  ____  __  __ _____  _      ______ _______ ______ _____  
 / ____|   /\   |  \/  |  ____|  / ____|/ __ \|  \/  |  __ \| |    |  ____|__   __|  ____|  __ \ 
| |  __   /  \  | \  / | |__    | |    | |  | | \  / | |__) | |    | |__     | |  | |__  | |  | |
| | |_ | / /\ \ | |\/| |  __|   | |    | |  | | |\/| |  ___/| |    |  __|    | |  |  __| | |  | |
| |__| |/ ____ \| |  | | |____  | |____| |__| | |  | | |    | |____| |____   | |  | |____| |__| |
 \_____/_/    \_\_|  |_|______|  \_____|\____/|_|  |_|_|    |______|______|  |_|  |______|_____/ 
)";

// Random number generator for particle effects
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 5); // For random colors

// Firework particle structure
struct Particle {
    int x, y;
    int dx, dy;
    std::string color;
    char symbol;
};

void clearScreen() {
    // Clear screen (works on most terminals)
    std::cout << "\033[2J\033[1;1H";
}

std::string getRandomColor() {
    std::string colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
    return colors[dis(gen)];
}

void displayFireworks(int width, int height, int numFireworks) {
    std::vector<Particle> particles;
    
    // Create fireworks
    for (int i = 0; i < numFireworks; i++) {
        std::uniform_int_distribution<> xDis(5, width - 5);
        
        Particle firework;
        firework.x = xDis(gen);
        firework.y = height - 1;
        firework.dx = 0;
        firework.dy = -1;
        firework.color = WHITE;
        firework.symbol = '|';
        particles.push_back(firework);
    }
    
    for (int frame = 0; frame < 20; frame++) {
        clearScreen();
        
        // Update particles
        for (auto it = particles.begin(); it != particles.end();) {
            // Move the particle
            it->x += it->dx;
            it->y += it->dy;
            
            // Check if particle is a firework that needs to explode
            if (it->symbol == '|' && it->y < height / 2) {
                // Remove the firework
                it = particles.erase(it);
                
                // Create explosion particles
                for (int i = 0; i < 20; i++) {
                    Particle explosion;
                    explosion.x = it->x;
                    explosion.y = it->y;
                    
                    // Random direction
                    std::uniform_real_distribution<> angleDis(0, 2 * 3.14159);
                    std::uniform_real_distribution<> speedDis(0.5, 2.0);
                    double angle = angleDis(gen);
                    double speed = speedDis(gen);
                    
                    explosion.dx = static_cast<int>(cos(angle) * speed);
                    explosion.dy = static_cast<int>(sin(angle) * speed);
                    
                    explosion.color = getRandomColor();
                    explosion.symbol = '*';
                    
                    particles.push_back(explosion);
                }
            }
            // Check if particle is out of bounds
            else if (it->x < 0 || it->x >= width || it->y < 0 || it->y >= height) {
                it = particles.erase(it);
            }
            else {
                // Draw the particle
                std::cout << "\033[" << it->y << ";" << it->x << "H";
                std::cout << it->color << it->symbol << RESET;
                ++it;
            }
        }
        
        // Add new fireworks occasionally
        if (frame % 5 == 0 && particles.size() < 200) {
            std::uniform_int_distribution<> xDis(5, width - 5);
            
            Particle firework;
            firework.x = xDis(gen);
            firework.y = height - 1;
            firework.dx = 0;
            firework.dy = -1;
            firework.color = WHITE;
            firework.symbol = '|';
            particles.push_back(firework);
        }
        
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void displayGameCompleted() {
    clearScreen();
    
    // Display a colorful border
    std::string border(80, '=');
    std::cout << BOLD << GREEN << border << RESET << std::endl;
    
    // Add some space
    std::cout << std::endl;
    
    // Display the title with color animation
    std::istringstream stream(GAME_COMPLETED_TEXT);
    std::string line;
    
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
    
    // Add some space
    std::cout << std::endl;
    
    // Display congratulatory message with blinking effect
    std::cout << BOLD << BLINK << YELLOW << std::string(25, ' ') << "CONGRATULATIONS, HERO!" << RESET << std::endl;
    
    // Display score/stats (example)
    std::cout << std::endl;
    std::cout << CYAN << "          Final Score: " << BOLD << "9850" << RESET << std::endl;
    std::cout << CYAN << "          Enemies Defeated: " << BOLD << "127" << RESET << std::endl;
    std::cout << CYAN << "          Treasures Found: " << BOLD << "42/50" << RESET << std::endl;
    std::cout << CYAN << "          Time Played: " << BOLD << "3:45:12" << RESET << std::endl;
    
    // Bottom border
    std::cout << std::endl;
    std::cout << BOLD << GREEN << border << RESET << std::endl;
    
    // Simulate fireworks (just for fun)
    std::cout << "\nPress Enter to start celebration...";
    std::cin.get();
    
    displayFireworks(80, 20, 5);
    
    clearScreen();
    std::cout << GAME_COMPLETED_TEXT << std::endl;
    std::cout << BOLD << GREEN << "Thanks for playing! Press Enter to exit..." << RESET;
    std::cin.get();
}
