# Tic-Tac-Toe Game

## Overview

This is a simple console-based Tic-Tac-Toe game implemented in C++. The game allows two players to take turns and make moves on a 3x3 board until one player wins or the game ends in a draw.

## Classes

### Player

- **Purpose**: Represents a player in the game.
- **Key Functions**:
  - `Player(const string& playerName, char playerSymbol)`: Constructor to initialize the player's name and symbol.
  - `char getSymbol() const`: Returns the player's symbol.
  - `string getName() const`: Returns the player's name.
  - `void display() const`: Displays the player's details.

### Board

- **Purpose**: Represents the game board where moves are made.
- **Key Functions**:
  - `Board()`: Constructor to initialize the board with empty spaces.
  - `void displayBoard() const`: Displays the current state of the board.
  - `bool makeMove(int row, int col, char player)`: Places a move on the board.

## How to Run

1. **Compile the Code**:

   ```sh
   g++ -o tic_tac_toe tic_tac_toe.cpp
   ```

2. **Run the Program**:

   ```sh
   ./tic_tac_toe
   ```

3. **Follow the Prompts**:
   - Enter names for Player 1 and Player 2.
   - Take turns entering your move by specifying the row and column.

## Example

```
Enter name for Player 1: Alice
Enter name for Player 2 : Bob

Player: Alice (X)
Player: Bob (O)
Enter your move (row and column): 0 0
```
