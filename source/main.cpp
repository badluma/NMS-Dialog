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
const std::string GRAY = "\x1b[90m";
const std::string RED = "\x1b[31m";
const std::string GREEN = "\x1b[32m";
const std::string YELLOW = "\x1b[33m";
const std::string BLUE = "\x1b[34m";
const std::string MAGENTA = "\x1b[35m";
const std::string CYAN = "\x1b[36m";

const std::string ACC_COLOR = RED;

// Variables
bool waitForPress = false; // Initializes the waitForPress variable and sets it to false 
int choice; // Initializes the choice variable
PrintConsole topScreen, bottomScreen; // Screens to print on

// Function identifiers
void switchScreen(int screen);
void wait(int timeToWait);
void show(std::string text, double time, bool doEndl, std::string color);
void color(std::string color);
void clear(int screen);
void para(int count);
void button(u32 button);
void holdButton(u32 button, int duration);
void quitOnPress();
void showChoice(std::string option1, std::string option2);
void describe(std::string text, double time, bool doEndl);


// ----------------------------------------------------------------------------------------------------


// Main Function
int main(int argc, char* argv[])
{
    gfxInitDefault();                               // Initialize 3DS graphics
    topScreen = *consoleInit(GFX_TOP, NULL);        // Initialize top screen
    bottomScreen = *consoleInit(GFX_BOTTOM, NULL);  // Initialize bottom screen

    // // Used to let the user quit anytime by pressing Start, not yet working
    // std::thread t1(quitOnPress);
    // t1.join();
    
    switchScreen(1); // Start on top screen

    // ---------- INITIALIZATION ----------
    wait(2000);
    para(12);
    show("              BEGIN INTIALIZATION?", 2, true, RESET);
    para(1);
    switchScreen(2);
    para(12);
    show("        Hold (Y) to initialize", 1, false, RESET);
    holdButton(KEY_Y, 2000);
    clear(0);
    wait(2000); // Wait for 2 seconds

    // ------------- AWAKENING ------------
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
    show("I notice that my scanner is broken. I should", 1, true, RESET);
    show("repair it to learn more about my environment. ", 1, true, RESET);
    show("Or I can just look around myself.", 1, true, RESET);
    showChoice("Repair scanner", "Investigate the area");
    clear(0);
    if (choice == 1) {
    //    ------------------------------------------------
        //    ------------------------------------------------
        show("Alright, lets see what I need to repair this.", 1, true, RESET);
        para(1);
        show("SCANNER STATUS ...               ", 1, false, RESET);
        show("NON-OPERATIONAL", 1, true, ACC_COLOR);
        show("REQUIRED MATERIAL: ", 1, false, RESET);
        show("SODIUM", 1, true, ACC_COLOR);
        para(1);
        show("I should look for this material in the forest.", 1, false, RESET);
        showChoice("Investigate the forest", "");
        clear(0);
    }
    else if (choice == 2) {
        show("The scanner isn't too important right now.", 1, true, RESET);
        show("For now, I want to find out where I am.", 1, true, RESET);
        describe("I'm slowly heading towards the forest", 1, true);
        para(1);
        show("SCANNER STATUS ...               ", 1, false, RESET);
        show("NON-OPERATIONAL", 1, true, ACC_COLOR);
        show("REQUIRED MATERIAL: ", 1, false, RESET);
        show("SODIUM", 1, true, ACC_COLOR);
        para(1);
    }

    switchScreen(1);
    show("Perfect, there is sodium here.", 1, true, RESET);
    show("It looks like it's in a small rock formation. ", 1, true, RESET);
    switchScreen(2);

    wait(10000);
    gfxExit();
    return 0;
}





// ----------------------------------------------------------------------------------------------------





// Function defenitions
void switchScreen(int screen) {
    if (screen == 1) {
        consoleSelect(&topScreen);                  // Select the top console
    }
    else if (screen == 2) {
        consoleSelect(&bottomScreen);               // Select the bottom consolle
    }
}
void para(int count) {
    for (int i = 0; i < count; i++)                 // Repeats the loop the number of times that is put in the count parameter
        std::cout << std::endl;                     // Start the new line
    std::cout << " ";                               // Type a space to have a border at the edge of the screen
}
void wait(int timeToWait) {
    std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
}
void show(std::string text, double time, bool doEndl, std::string color) {
    std::cout << color;                             // Sets console color to the parameter "color"
    for (char character : text) {                   // Repeats for every character in the string
        std::cout << character;                     // Prints the character
        if (!(character == ' ')) {                  // Doesn't wait if the character is a space
            wait(100 * time);                       // Waits a short time before the next character is displayed to create a typing effect
        }
    }
    if (doEndl) {                                   // Only runs if doEndl is true
        std::cout << std::endl << " ";              // Sets a space before each new line to create a border at the edge
    }
    wait(250);                                      // Wait a short time before showing the next message
}
void color(std::string colorName) {
    std::cout << colorName;                         // Sets console color to the parameter "color"
}
void clear(int screen) {
    if (screen == 1) {                              // Clear top screen
        switchScreen(1);
        consoleClear();
        std::cout << std::endl;                     // Add border on the top of the screen through an empty line
        std::cout << " ";                           // Type space at end to have a border at the edge of the screen
        
    }
    if (screen == 2) {                              // Clear bottom screen
        switchScreen(2);
        consoleClear();
        std::cout << std::endl;                     // Add border on the top of the screen through an empty line
        std::cout << " ";                           // Type space at end to have a border at the edge of the screen
    }
    if (screen == 0) {                              // Clear both screens
        switchScreen(2);
        consoleClear();
        switchScreen(1);
        consoleClear();
        std::cout << std::endl;                     // Add border on the top of the screen through an empty line
        std::cout << " ";                           // Type space at end to have a border at the edge of the screen
    }
}
void button(u32 button) {
    waitForPress = true;
    while (waitForPress && aptMainLoop()) {         // While the function is waiting for a button press, 
        gspWaitForVBlank();
        hidScanInput();                             // Scans for input with hidScanInput();
        
        u32 kDown = keysDown();                     // Sets kDown variable to button that is pressed

        if (kDown & button) {            
            waitForPress = false;                   // When the button is pressed, it stops listening for input and breaks the function
        }
    }
}
void holdButton(u32 button, int duration) {
    waitForPress = true;                            // Sets waitForPress to true to start the loop
    while (waitForPress && aptMainLoop()) {         // Runs until a button is pressed
        gspWaitForVBlank();
        hidScanInput();                             // Scans for input
        
        u32 kDown = keysDown();                     // Sets kDown variable to button that is pressed
        
        if (kDown & button) {                       // Only runs if a button is pressed
            wait(2000);
            if (kDown & button) {                   // Checks after the time is up if the button is still pressed
                waitForPress = false;               // Sets waitForPress to false to break the loop
                consoleClear();                     // Clear
                switchScreen(1);                    // both
                consoleClear();                     // consoles
            }
            else {
                holdButton(button, duration);       // If button is released, the function is started from the beginning
            }
        }
    }
}
void quitOnPress() {                                // Function made to quit the program when the START key is pressed; not yet working
    while (aptMainLoop()) {                         // Runs runs always when the program is active
        button(KEY_START);                          // Checks if the START button is pressed using the button() function
        break;                                      // Quits the program
    }
}
void showChoice(std::string option1, std::string option2) {
    switchScreen(2);                                // Switch to bottom screen
    para(14);
    show("(A) ", 1, false, ACC_COLOR);              // Shows the key to press
    show(option1, 1, true, RESET);                  // Shows the first option from the parameter
    para(1);                                        // Type a paragraph
    if (!(option2.empty())) {                       // If second option exists
        show("(B) ", 1, false, ACC_COLOR);          // Shows key to press
        show(option2, 1, true, RESET);              // Shows the second option from the parameter
    }
    waitForPress = true;                            // Sets waitForPress variable to true to run the loop below
    while (waitForPress && aptMainLoop()) {         // Repeats the loop until a button is pressed
        gspWaitForVBlank(); 
        hidScanInput();                             // Scans for input
        
        u32 kDown = keysDown();                     // Sets the variable kDown to the key that is pressed at the moment
        
        if (kDown & KEY_A) {                        // Checks if the key A is pressed
            waitForPress = false;                   // Sets waitForPress to false to break the loop
            choice = 1;                             // Sets the global choice variable to 1
            consoleClear();                         // Clears the bottom screen console
            std::cout << std::endl << " ";          // Type space at end to have a border at the edge of the screen
            break;                                  // Break the loop
        }
        
        if (kDown & KEY_B && !(option2.empty()) ) { // Checks if the key B is pressed and if a second option exists
            waitForPress = false;                   // Sets waitForPress to false to break the loop
            choice = 2;                             // Sets the global choice variable to 2
            consoleClear();                         // Clears the bottom screen console
            std::cout << std::endl << " ";          // Type space at end to have a border at the edge of the screen
            break;                                  // Break the loop
        }
    }
}
void describe(std::string text, double time, bool doEndl) {
    text = "*" + text + "*";                        // Wraps the text in two *-characters
    para(1); 
    show(text, time, doEndl, GRAY);                 // Shows the text in gray
    para(1);
}