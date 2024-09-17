#include <iostream>
using namespace std;

// Class to represent a Player in the game
class Player
{
private:
    char symbol;            // Symbol for the player ('X' or 'O')
    string name;            // Name of the player
    static int playerCount; // Static variable to keep track of the number of Player objects created

public:
    // Constructor to increase playerCount when a new Player is created
    Player()
    {
        playerCount++;
    }
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
    // Static function to get the current number of players
    static int getPlayerCount()
    {
        return playerCount;
    }

    // Function to display player's details
    void display() const
    {
        cout << "Player: " << this->name << " (" << this->symbol << ")\n";
    }
};
// Initialize the static member variable
int Player::playerCount = 0;

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
    // Dynamically allocate an array of 2 Player objects
    Player *players = new Player[2]; // using new[] for array

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

    // Dynamically allocate the Board object
    Board *board = new Board; // using new for single object
    board->initializeBoard();

    // Display number of players
    cout << "Number of players: " << Player::getPlayerCount() << endl;

    // Example usage
    board->displayBoard();
    for (int i = 0; i < 2; i++)
    {
        players[i].display();
    }

    // Making a move
    board->makeMove(0, 0, players[0].getSymbol());
    board->displayBoard();

    // Deallocate dynamically allocated memory
    delete[] players; // using delete[] for array
    delete board;     // using delete for single object

    return 0;
}
