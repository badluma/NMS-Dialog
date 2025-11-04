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

const std::string ACC_COLOR = RED;

// Variables
bool waitForPress = false;
bool choice;
PrintConsole topScreen, bottomScreen;

// Function identifiers
void switchScreen(int screen);
void wait(int timeToWait);
void show(std::string text, double time, bool doEndl, std::string color);
void color(std::string color);
void para(int count);
void button(u32 button);
void holdButton(u32 button, int duration);
void showChoice(std::string option1, std::string option2);



// Main Function
int main(int argc, char* argv[])
{
    gfxInitDefault(); // Initialize 3DS graphics
    topScreen = *consoleInit(GFX_TOP, NULL); // Initialize top screen
    bottomScreen = *consoleInit(GFX_BOTTOM, NULL); // Initialize bottom screen

    switchScreen(1); // Start on top screen

    // Main code

    // ---------- INITIALIZATION ----------
    wait(2000);
    para(12);
    show("             BEGIN INTIALIZATION?               ", 2, true, RESET);
    para(1);
    switchScreen(2);
    para(12);
    show("        Hold (Y) to initialize", 1, false, RESET);
    holdButton(KEY_Y, 2000);
    consoleClear();
    switchScreen(1);
    consoleClear();
    wait(2000); // Wait for 2 seconds

    // ------------- AWAKENING ------------
    para(1);
    show("ATLAS SYSTEM INITIALIZATION ... ", 1, false, RESET);
    show("       COMPLETED", 1.5, true, ACC_COLOR);
    wait(1000); // Wait for 1 seconds
    show("LIFE SUPPORT SYSTEMS ... ", 1, false, RESET);
    show("              ACTIVATED", 1.5, true, ACC_COLOR);
    wait(1000); // Wait for 1 seconds
    show("SHIELD KINETIC SYSTEM ... ", 1, false, RESET);
    show("                ONLINE", 1.5, true, ACC_COLOR);
    wait(1000); // Wait for 1 seconds
    show("MULTITOOL AND MINING LASER ... ", 1, false, RESET);
    show("      OPERATIONAL", 1.5, true, ACC_COLOR);
    wait(1000); // Wait for 1 seconds
    show("RADIATION PROTECTION ... ", 1, false, RESET);
    show("                FALLING", 1.5, true, ACC_COLOR);
    wait(2000); // Wait for 2 seconds
    para(1);
    show("HELLO ", 1, false, RESET);
    show("TRAVELLER", 2.5, true, ACC_COLOR);
    show("ITERATION: ", 1, false, RESET);
    show("7X3A", 1, false, ACC_COLOR);
    show("9L2Q8Z1M4R5S6T", 0.3, false, RESET);
    show("16", 0.6, true, ACC_COLOR);
    para(1);
    wait(3000);
    show("I woke up here, ", 1, false, RESET);
    show("not knowing who I am. ", 1, true, RESET);
    show("Where I am. ", 1, false, RESET);
    show("What my purpose is.", 1, true, RESET);
    para(1);
    wait(1000);
    show("...", 5, true, RESET);
    para(1);
    wait(1000);
    show("I should look around. ", 1, true, RESET);
    show("Maybe I find something that could help me.", 1, true, RESET);
    showChoice("Search the Forest", "Check Inventory for useful items"); // Choose between the two options
    switchScreen(1); // Switch back to top screen
    return 0;

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
        consoleSelect(&topScreen); // Select the top console
    }
    else if (screen == 2) {
        consoleSelect(&bottomScreen); // Select the bottom consolle
    }
}

void para(int count) {
    for (int i = 0; i < count; i++) 
        std::cout << std::endl;
    std::cout << " "; // Type a space to have a border at the edge of the screen
}

void wait(int timeToWait) {
    std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
}
void show(std::string text, double time, bool doEndl, std::string color) {
    std::cout << color;
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
void button(u32 button) {
    waitForPress = true;
    while (waitForPress && aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();
        
        u32 kDown = keysDown(); 
        
        if (kDown & button) {            
            waitForPress = false;
            choice = true;
        }
    }
}
void holdButton(u32 button, int duration) {
    waitForPress = true;
    while (waitForPress && aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();
        
        u32 kDown = keysDown(); 
        
        if (kDown & button) {
            wait(2000);
            if (kDown & button) {
                waitForPress = false;
                choice = true;
                consoleClear();
                switchScreen(1);
                consoleClear();
            }
            else {
                holdButton(button, duration);
            }
        }
    }
}
void showChoice(std::string option1, std::string option2) {
    switchScreen(2); // Switch to bottom screen
    para(14);
    show("(A) ", 1, false, ACC_COLOR);
    show(option1, 1, true, RESET);
    para(1);
    show("(B) ", 1, false, ACC_COLOR);
    show(option2, 1, true, RESET);
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