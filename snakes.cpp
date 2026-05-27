#include "Dice.h"
#include <string>
#include <limits>
#include <iostream>
#include <cctype>
#include "Game.h"

using namespace std;

int getValidInt(string message) {
    int value;
    while (true) {
        cout << message;
        cin >> value;

        // Check if user typed text instead of a number
        if(cin.fail()) {
            cin.clear(); // Clear the error flag to reassign a cin

            // Discard the bad input remaining in the terminal buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter an integer input. \n\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    int tiles   = getValidInt("Enter number of board tiles: ");
    int snakes  = getValidInt("Enter number of snakes: ");
    int ladders = getValidInt("Enter number of ladders: ");
    int penalty = getValidInt("Enter penalty squares (go back): ");
    int reward  = getValidInt("Enter reward squares (advance): ");
    int players = getValidInt("Enter number of players: ");
    int turns   = getValidInt("Enter max simulation turns: ");
    char gameType;


    MyGame *g;
    char type;

    while (true) {
        cout << "Enter M for Manual gameplay or A for Automatic gameplay. Enter option: ";
        cin >> gameType;
        gameType = toupper(gameType);
        if (gameType == 'A' || gameType == 'M') { break;} 
        else { cout << "Wrong input\n"; }
    }
        
    if (gameType == 'M') {
        g = new ManualGame(tiles, snakes, ladders, penalty, reward, players, turns, 'M');
    } else {
        g = new AutoGame(tiles, snakes, ladders, penalty, reward, players, turns, 'A');
    }

    g->start();
    delete g;
    return 0;
}
