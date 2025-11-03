#include <iostream>
#include <cstdlib>
#include <string>
#include <3ds.h>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>

// Constants
const std::string RESET = "\x1b[0m";
const std::string RED = "\x1b[31m";
const std::string GREEN = "\x1b[32m";
const std::string YELLOW = "\x1b[33m";
const std::string BLUE = "\x1b[34m";
const std::string MAGENTA = "\x1b[35m";
const std::string CYAN = "\x1b[36m";

// Variables
bool waitForPress = false;
bool choice;
PrintConsole topScreen, bottomScreen;

// Function identifiers
void switchScreen(int screen);
void wait(int timeToWait);
void show(std::string text, double time, bool doEndl);
void color(std::string color);
void para(int count);
void showChoice(std::string option1, std::string option2);



// Main Function
int main(int argc, char* argv[])
{
    gfxInitDefault(); // Initialize 3DS graphics
    topScreen = *consoleInit(GFX_TOP, NULL); // Initialize top screen
    bottomScreen = *consoleInit(GFX_BOTTOM, NULL); // Initialize bottom screen

    switchScreen(1); // Start on top screen

    // Main code
    std::cout << std::endl;
    wait(1000); // Wait for a second
    para(1);
    show("HELLO ", 1, false);
    color(RED);
    show("TRAVELLER", 2.5, true);
    color(RESET);
    show("ITERATION: ", 1, false);
    color(RED);
    show("7X3A", 0.3, false);
    color(RESET);
    show("9L2Q8Z1M4R5S6T", 0.3, false);
    color(RED);
    show("16", 0.6, true);
    para(1);
    color(RESET);
    wait(3000);
    show("I woke up here, ", 1, false);
    show("not knowing who I am. ", 1, true);
    show("Where I am. ", 1, false);
    show("What my purpose is.", 1, true);
    para(1);
    wait(1000);
    show("...", 5, true);
    para(1);
    wait(1000);
    show("I should look around. ", 1, true);
    show("Maybe I find something that could help me.", 1, true);
    showChoice("Search the Forest", "Find a Way Out");
    switchScreen(1); // Switch back to top screen
    std::cout << "lolllollool";

    // Main loop
    while (aptMainLoop())
    {
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        // Your code goes here
        if (keysHeld() & KEY_START) {
            break; // break in order to return to hbmenu
        }

    }

    gfxExit();
    return 0;
}

// Function defenitions
void switchScreen(int screen) {
    if (screen == 1) {
        consoleSelect(&topScreen);
    }
    else if (screen == 2) {
        consoleSelect(&bottomScreen);
    }
}
void para(int count) {
    for (int i = 0; i < count; i++) 
        std::cout << std::endl;
    std::cout << " ";
}
void wait(int timeToWait) {
    std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
}
void show(std::string text, double time, bool doEndl) {
    for (char character : text) {
        std::cout << character;
        if (!(character == ' ')) {
            wait(100 * time);
        }
    }
    if (doEndl) {
        std::cout << std::endl;}
    if (doEndl) {
        std::cout << " ";
    }
    wait(250);
}
void color(std::string colorName) {
    std::cout << colorName;
}
void showChoice(std::string option1, std::string option2) {
    switchScreen(2); // Switch to bottom screen
    para(5);
    show("(A) ", 1, false);
    show(option1, 1, true);
    para(1);
    show("(B) ", 1, false);
    show(option2, 1, true);
    waitForPress = true;
    while (waitForPress && aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();
        
        u32 kDown = keysDown(); 
        
        if (kDown & KEY_A) {
            waitForPress = false;
            choice = true;
            consoleClear();
            break;
        }
        if (kDown & KEY_B) {
            waitForPress = false;
            choice = false;
            consoleClear();
            break;
        }
    }
}