#include <iostream>
using namespace std;

// Base class Person
class Person
{
protected:
    string name;

public:
    Person() : name("Unknown") {}

    void setName(const string &playerName)
    {
        name = playerName;
    }

    string getName() const
    {
        return name;
    }
};

// Derived class Player inherits from Person (Single Inheritance)
class Player : public Person
{
private:
    char symbol;
    static int playerCount;

public:
    Player()
    {
        playerCount++;
    }

    ~Player()
    {
        playerCount--;
    }

    void setPlayerDetails(const string &playerName, char playerSymbol)
    {
        setName(playerName); // inherited from Person
        symbol = playerSymbol;
    }

    char getSymbol() const
    {
        return symbol;
    }

    static int getPlayerCount()
    {
        return playerCount;
    }
};

int Player::playerCount = 0;

// Base class GameComponent for multilevel inheritance
class GameComponent
{
public:
    virtual void initialize() = 0;    // Pure virtual function for initialization
    virtual void display() const = 0; // Pure virtual function for display
};

// Derived class Board inherits from GameComponent (Multilevel Inheritance)
class Board : public GameComponent
{
protected:
    char board[3][3];

public:
    Board()
    {
        initialize();
    }

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

    bool makeMove(int row, int col, char playerSymbol)
    {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
        {
            board[row][col] = playerSymbol;
            return true;
        }
        return false;
    }

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

// Derived class TicTacToeBoard inherits from Board (Extending Board for Tic-Tac-Toe specific rules)
class TicTacToeBoard : public Board
{
public:
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

// Game class to control the game flow
class Game
{
private:
    Player players[2];
    TicTacToeBoard board;
    int currentPlayer;

public:
    Game() : currentPlayer(0)
    {
        char symbols[] = {'X', 'O'};
        for (int i = 0; i < 2; i++)
        {
            cout << "Enter the name for player " << symbols[i] << ": ";
            string name;
            getline(cin, name);
            players[i].setPlayerDetails(name, symbols[i]);
        }
        board.initialize();
    }

    void play()
    {
        bool gameWon = false;
        while (!board.isFull() && !gameWon)
        {
            board.display();
            Player &player = players[currentPlayer];
            cout << player.getName() << "'s turn (" << player.getSymbol() << ")\n";
            int row, col;
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
