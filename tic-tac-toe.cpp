#include <iostream>
using namespace std;

// Class to manage player's information - Name (Single Responsibility)
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

// Class to represent Player (Handles player's symbol, count, etc.)
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

    void setPlayerDetails(const string &playerName, char playerSymbol)
    {
        setName(playerName);
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

// Class to manage Board (Handles initialization, display, and moves of the board)
class Board
{
protected:
    char board[3][3];

public:
    Board()
    {
        initialize();
    }

    void initialize()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
    }

    void display() const
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

    bool makeMove(int position, char playerSymbol)
    {
        int row = position / 3;
        int col = position % 3;
        return makeMove(row, col, playerSymbol);
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

// Class to check the win conditions for the game
class TicTacToeBoard : public Board
{
public:
    bool checkWin(char playerSymbol) const
    {
        for (int i = 0; i < 3; i++)
        {
            if ((board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol) ||
                (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol))
            {
                return true;
            }
        }

        if ((board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol) ||
            (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol))
        {
            return true;
        }

        return false;
    }
};

// Game class to control the flow of the game (Manages the game loop and player turns)
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
            int choice;
            cout << "Enter 1 for row and column or 2 for position (0-8): ";
            cin >> choice;
            int row, col, pos;

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
