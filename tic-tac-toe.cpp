#include <iostream>
using namespace std;

// Abstract Base Class: Person
class Person
{
protected:
    string name;

public:
    Person() : name("Unknown") {}

    // Set and Get methods for 'name'
    void setName(const string &playerName)
    {
        name = playerName;
    }

    string getName() const
    {
        return name;
    }
};

// Derived Class: Player inherits from Person (Single Inheritance)
class Player : public Person
{
private:
    char symbol;
    static int playerCount; // Keeps track of the number of players

public:
    Player()
    {
        playerCount++;
    }

    ~Player()
    {
        playerCount--;
    }

    // Sets player's details with name and symbol
    void setPlayerDetails(const string &playerName, char playerSymbol)
    {
        setName(playerName); // Set the name using the Person base class function
        symbol = playerSymbol;
    }

    char getSymbol() const
    {
        return symbol;
    }

    // Static function to get player count
    static int getPlayerCount()
    {
        return playerCount;
    }
};

int Player::playerCount = 0;

// Abstract Base Class: GameComponent for multilevel inheritance
class GameComponent
{
public:
    // Pure virtual functions - Making GameComponent an abstract class
    virtual void initialize() = 0;    // For initialization
    virtual void display() const = 0; // For displaying game components
};

// Derived Class: Board inherits from GameComponent (Multilevel Inheritance)
class Board : public GameComponent
{
protected:
    char board[3][3]; // 3x3 board array

public:
    // Constructor initializes the board
    Board()
    {
        initialize();
    }

    // Initializes board with empty spaces
    void initialize() override
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
    }

    // Displays the Tic-Tac-Toe board
    void display() const override
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

    // Overloaded makeMove function: Allows move by row and column
    bool makeMove(int row, int col, char playerSymbol)
    {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
        {
            board[row][col] = playerSymbol;
            return true;
        }
        return false;
    }

    // Overloaded makeMove function: Allows move by single position
    bool makeMove(int position, char playerSymbol)
    {
        int row = position / 3;
        int col = position % 3;
        return makeMove(row, col, playerSymbol);
    }

    // Checks if the board is full
    bool isFull() const
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }
};

// Derived Class: TicTacToeBoard inherits from Board (Multilevel Inheritance)
class TicTacToeBoard : public Board
{
public:
    // Checks if a player has won
    bool checkWin(char playerSymbol) const
    {
        // Check rows and columns
        for (int i = 0; i < 3; i++)
        {
            if ((board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol) ||
                (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol))
            {
                return true;
            }
        }

        // Check diagonals
        if ((board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol) ||
            (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol))
        {
            return true;
        }

        return false;
    }
};

// Game Class to control the game flow
class Game
{
private:
    Player players[2];
    TicTacToeBoard board;
    int currentPlayer;

public:
    Game() : currentPlayer(0)
    {
        // Initialize player symbols
        char symbols[] = {'X', 'O'};
        for (int i = 0; i < 2; i++)
        {
            cout << "Enter the name for player " << symbols[i] << ": ";
            string name;
            getline(cin, name);
            players[i].setPlayerDetails(name, symbols[i]);
        }
        board.initialize(); // Initialize the board
    }

    // Main game loop
    void play()
    {
        bool gameWon = false;
        while (!board.isFull() && !gameWon)
        {
            board.display();
            Player &player = players[currentPlayer];
            cout << player.getName() << "'s turn (" << player.getSymbol() << ")\n";
            int choice;
            cout << "Enter 1 for row and column or 2 for position (0-8): ";
            cin >> choice;
            int row, col, pos;

            // Choose input method for the move
            if (choice == 1)
            {
                cout << "Enter row and column: ";
                cin >> row >> col;
                if (board.makeMove(row, col, player.getSymbol()))
                {
                    if (board.checkWin(player.getSymbol()))
                    {
                        board.display();
                        cout << "Congratulations! " << player.getName() << " wins the game!\n";
                        gameWon = true;
                    }
                    currentPlayer = (currentPlayer + 1) % 2;
                }
                else
                {
                    cout << "Invalid move. Try again.\n";
                }
            }
            else
            {
                cout << "Enter position (0-8): ";
                cin >> pos;
                if (board.makeMove(pos, player.getSymbol()))
                {
                    if (board.checkWin(player.getSymbol()))
                    {
                        board.display();
                        cout << "Congratulations! " << player.getName() << " wins the game!\n";
                        gameWon = true;
                    }
                    currentPlayer = (currentPlayer + 1) % 2;
                }
                else
                {
                    cout << "Invalid move. Try again.\n";
                }
            }
        }

        // Check for draw if board is full
        if (!gameWon)
        {
            board.display();
            cout << "It's a draw!\n";
        }
    }
};

int main()
{
    Game game;
    game.play();
    return 0;
}
