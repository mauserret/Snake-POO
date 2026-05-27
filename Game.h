#pragma once
#include "Dice.h"
#include "Tiles.h"
#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <random>

using namespace std;

class MyGame {
protected:
    int turn = 1;
    vector<Tiles*> board;
    int tiles;
    int snakes;
    int ladders;
    int penalty;
    int reward;
    int players;
    int turns;
    char gameType;

public:
    MyGame() : tiles{30}, snakes{3}, ladders{3}, penalty{3},
           reward{3}, players{2}, turns{20}, gameType{'M'} {
        board.resize(tiles + 1);
    }

    MyGame(int tiles, int snakes, int ladders, int penalty, 
           int reward, int players, int turns, char gameType) :
           tiles{tiles}, snakes{snakes}, ladders{ladders}, penalty{penalty},
           reward{reward}, players{players}, turns{turns}, gameType{gameType} {
        board.resize(tiles + 1);      
    }

    virtual ~MyGame() {
        for (auto tile : board) {
            delete tile;
        }
    }

    void start() {
        makeBoard();
        Dice dice;
        
        vector<int> playerPositions(players + 1, 1);
        bool gameWon = false;

        while (turn <= turns) {
            if (!continueGame()) {
                break;
            }

            for(int i = 1; i <= players; i++) {
                playTurn(playerPositions[i], i, dice);
                if (playerPositions[i] == tiles) {
                    cout << "-- GAME ENDED --\n";
                    cout << "-- Player " << i << " won! --\n";
                    gameWon = true;
                    break;
                }
            }
            turn++;
            
            if (gameWon) { 
                break; 
                turn++;
            }
        }

        if (turn > turns && !gameWon) {
            cout << "-- GAME ENDED --\n";
            cout << "-- Reached maximum number of turns --\n";
        }
    }

    void playTurn(int &position, int playerNumber, Dice &dice) {
        int oldposition = position;
        int roll = dice.roll();

        position += roll;
        if (position > tiles) {
            position = tiles;
        }

        char tileLabel = board[position]->getLabel();
        position = board[position]->positionEffect(position);

        if (position < 1) position = 1;
        if (position > tiles) position = tiles;

 
        cout << "Turn: " << turn << " | "
        << "Player: " << playerNumber << " | "
        << "Old Position: " << oldposition << " | "
        << "Roll: " << roll << " | "
        << "Tile: " << tileLabel << " | "
        << "Position: " << position << " \n"; 
        }

    void makeBoard() {
        for (auto tile : board) { delete tile; }

        for (int i = 0; i <= tiles; i++) {
            board[i] = new NormalTile();
        }
        
        int snakesPlaced = 0;
        while (snakesPlaced < snakes) {
            int position = randomNum();
            if (board[position]->getLabel()=='N'){
                delete board[position];
                board[position] = new SnakeTile(penalty);
                snakesPlaced++;
            } 
        }

        int laddersPlaced = 0;
        while (laddersPlaced < ladders) {
            int position = randomNum();
            if (board[position]->getLabel() == 'N'){
                delete board[position];
                board[position] = new LadderTile(reward);
                laddersPlaced++;
            } 
        }
    }

    int randomNum() {
        random_device rd; // insert a random seed into "rd" using random_device
        mt19937 gen(rd()); // using the mt19937 random engine, generate randomness with the rd seed
        uniform_int_distribution<> dist(2, tiles-1); // limit the values from 1 to 6 with the same chance
        return dist(gen); // get the random number from 1 to 6 with the gen randomness 
    }

    virtual bool continueGame() = 0;

};

class ManualGame:public MyGame {
    public:
        ManualGame(int t, int s, int l, int p, int r, int pl, int tr, char gt) 
            : MyGame(t, s, l, p, r, pl, tr, gt) {}

        bool continueGame() override {
            while (true) {
                char option;
                cout << "Instructions: Type C to continue next turn, or E to end the game\n";
                cout << "Enter option: ";
                cin >> option;
                option = tolower(option);

                if (option == 'e') {
                    cout << "-- GAME MANUALLY ENDED --\n";
                    return false;
                }   else if (option == 'c') {
                    return true;
                } else {
                    cout << "Invalid option, please type to continue next turn, or E to end the game\n";

                }
            }
        }
};

class AutoGame:public MyGame {
    public:
        AutoGame(int t, int s, int l, int p, int r, int pl, int tr, char gt) 
                : MyGame(t, s, l, p, r, pl, tr, gt) {}
        bool continueGame() override {
            return true;
        }
};