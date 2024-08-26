#include <iostream>
using namespace std;

// Class to represent a Player in the game
class Player
{
private:
    char symbol; // Symbol for the player ('X' or 'O')
    string name; // Name of the player

public:
    // Function to set the player's symbol
    void setSymbol(char playerSymbol)
    {
        this->symbol = playerSymbol;
    }

    // Function to set the player's name
    void setName(string playerName)
    {
        this->name = playerName;
    }

    // Function to get the player's symbol
    char getSymbol() const
    {
        return this->symbol;
    }

    // Function to get the player's name
    string getName() const
    {
        return this->name;
    }

    // Function to display player's details
    void display() const
    {
        cout << "Player: " << this->name << " (" << this->symbol << ")\n";
    }
};

// Class to represent the Tic-Tac-Toe board
class Board
{
private:
    char board[3][3]; // 3x3 board

public:
    // Function to initialize the board with empty spaces
    void initializeBoard()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                this->board[i][j] = ' ';
            }
        }
    }

    // Function to display the board
    void displayBoard() const
    {
        cout << "  0 1 2\n";
        for (int i = 0; i < 3; i++)
        {
            cout << i << " ";
            for (int j = 0; j < 3; j++)
            {
                cout << this->board[i][j];
                if (j < 2)
                    cout << "|";
            }
            cout << "\n";
            if (i < 2)
                cout << "  -----\n";
        }
    }

    // Function to place a move on the board
    bool makeMove(int row, int col, char player)
    {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && this->board[row][col] == ' ')
        {
            this->board[row][col] = player;
            return true;
        }
        return false;
    }
};

int main()
{
    // Array of Player objects
    Player players[2];

    // Set player details
    cout << "Enter the name for player X: ";
    string name;
    getline(cin, name);
    players[0].setName(name);
    players[0].setSymbol('X');

    cout << "Enter the name for player O: ";
    getline(cin, name);
    players[1].setName(name);
    players[1].setSymbol('O');

    // Initialize Board object
    Board board;
    board.initializeBoard();

    // Example usage
    board.displayBoard();
    for (int i = 0; i < 2; i++)
    {
        players[i].display();
    }

    // Making a move
    board.makeMove(0, 0, players[0].getSymbol());
    board.displayBoard();

    return 0;
}
