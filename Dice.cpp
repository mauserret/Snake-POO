#include "dice.h"
#include <random>
#include <iostream>
using namespace std;

int Dice::roll() {
    random_device rd; // insert a random seed into "rd" using random_device
    mt19937 gen(rd()); // using the mt19937 random engine, generate randomness with the rd seed
    uniform_int_distribution<> dist(1, 6); // limit the values from 1 to 6 with the same chance

    int roll = dist(gen); // get the random number from 1 to 6 with the gen randomness 

    return roll;
}