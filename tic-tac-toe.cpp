#include <iostream>
using namespace std;

// Class to represent a Player in the game
class Player
{
private:
    char symbol; // Symbol for the player ('X' or 'O')
    string name; // Name of the player

public:
    // Constructor
    Player(const string &playerName, char playerSymbol) : name(playerName), symbol(playerSymbol) {}

    // Function to get the player's symbol
    char getSymbol() const
    {
        return symbol;
    }

    // Function to get the player's name
    string getName() const
    {
        return name;
    }

    // Function to display player's details
    void display() const
    {
        cout << "Player: " << name << " (" << symbol << ")\n";
    }
};

// Class to represent the Tic-Tac-Toe board
class Board
{
private:
    char board[3][3]; // 3x3 board

public:
    // Constructor to initialize the board with empty spaces
    Board()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
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
                cout << board[i][j];
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
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
        {
            board[row][col] = player;
            return true;
        }
        return false;
    }
};

int main()
{
    // Instantiate Player objects
    Player player1("Alice", 'X');
    Player player2("Bob", 'O');

    // Instantiate Board object
    Board board;

    // Example usage
    board.displayBoard();
    player1.display();
    player2.display();

    // Making a move
    board.makeMove(0, 0, player1.getSymbol());
    board.displayBoard();

    return 0;
}
