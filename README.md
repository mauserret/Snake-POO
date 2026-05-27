Mauricio Rey Hernández Curiel
Files: main.cpp, MyGame.h, Tiles.h, Dice.h, Dice.cpp

------------------------------------------------------------------------
1. DESCRIPTION
------------------------------------------------------------------------
This program is an object-oriented simulation of the classic Snakes and 
Ladders board game. Users can configure game rules directly through the 
command-line interface, the user can change the board size, number of 
players, penalty values, reward values, total turns, and simulation mode 
------------------------------------------------------------------------
2. COMPILATION INSTRUCTIONS
------------------------------------------------------------------------
Open the terminal and navigate to the directory containing all the project 
files (.cpp and .h files), and execute the following command:

Using G++:
    g++ snakes.cpp Dice.cpp -o snakes

------------------------------------------------------------------------
3. RUNNING THE PROGRAM
------------------------------------------------------------------------
Once successfully compiled, run the executable from your terminal:

.\snakes.exe

Gameplay Configuration Process:

When running the program, it will prompt you the configurations of the
games.

1. Board Tiles: The total number of boxes on the board (recomended is more than 20).
2. Snakes Count: Number of snake obstacles to place.
3. Ladders Count: Number of ladder rewards to place.
4. Penalty: Number of spaces a player drops backward when landing on a snake.
5. Reward: Number of extra spaces a player advances when landing on a ladder.
6. Players: Total number of active participants in the match.
7. Max Turns: Limit turns for simulation.
8. Game Mode: Choose 'M' for Manual control (presses 'C' to continue 
   or 'E' to exit between turns) or 'A' for Automatic simulation.

------------------------------------------------------------------------
INHERITANCE AND POLYMORPHISM 
------------------------------------------------------------------------

INHERITANCE

1. Board Tiles Hierarchy (`Tiles.h`):
   - Base Class: `Tiles`
     Defines foundational properties like a text label representing the tile type.
   - Derived Classes: `NormalTile`, `SnakeTile`, and `LadderTile`
     Inherit from `Tiles`. `SnakeTile` and `LadderTile` capture their unique 
     rules independently by storing private variables `penalty` and 
     `reward`.

2. Game Flow Modes Hierarchy (`MyGame.h`):
   - Base Class: `MyGame`
     Manages properties common to all configurations (board generation, players 
     tracking, game state execution, boundary tracking).
   - Derived Classes: `ManualGame` and `AutoGame`
     Inherit full board capabilities from `MyGame` but branch out behaviorally 
     concerning user intervention.

POLYMORPHISM

1. Dynamic Tile Modification Effects:
   The base `Tiles` class defines a pure virtual function:
       virtual int positionEffect(int currentPosition) = 0;
   
   During execution, the board layout array is represented universally as a 
   collection of base pointers: `vector<Tiles*> board`. 
   When a player lands on any given tile, the engine executes:
       position = board[position]->positionEffect(position);
   
   Through virtual , C++ evaluates at runtime whether to apply no change
   (`NormalTile`), subtract spaces (`SnakeTile`), or add spaces (`LadderTile`).

2. Dynamic Turn Controls:
   The base `MyGame` class contains a pure virtual abstraction function:
       virtual bool continueGame() = 0;
   
   The core execution system triggers this query every single turn. 
   Depending on the configured gameplay choice, a base pointer (`MyGame* game`) 
   points to either a `ManualGame` or an `AutoGame`. 
   - If it points to an `AutoGame`, `continueGame()` bypasses prompts and immediately returns `true`.
   - If it points to a `ManualGame`, `continueGame()` suspends the loop, captures keyboard inputs, validates execution keys, and halts or continues based on the response.

By employing virtual destructors (`virtual ~Tiles()` and `virtual ~MyGame()`), 
the system ensures that polymorphic cleanups cleanly tear down allocations 
without producing memory leaks.
