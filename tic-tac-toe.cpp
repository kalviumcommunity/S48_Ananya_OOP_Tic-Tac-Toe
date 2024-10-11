#include <iostream>
using namespace std;

class Player
{
private:
    char symbol;
    string name;
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

    void setter(string playerName, char playerSymbol)
    {
        this->name = playerName;
        this->symbol = playerSymbol;
    }

    string getName() const
    {
        return this->name;
    }

    char getSymbol() const
    {
        return this->symbol;
    }

    static int getPlayerCount()
    {
        return playerCount;
    }
};

int Player::playerCount = 0;

class Board
{
private:
    char board[3][3];

public:
    Board()
    {
        initializeBoard();
    }

    ~Board()
    {
    }

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

    bool makeMove(int row, int col, char player)
    {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && this->board[row][col] == ' ')
        {
            this->board[row][col] = player;
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
                if (this->board[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    bool checkWin(char player) const
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            {
                return true;
            }
        }

        for (int j = 0; j < 3; j++)
        {
            if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            {
                return true;
            }
        }

        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        {
            return true;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        {
            return true;
        }

        return false;
    }
};

class Game
{
private:
    Player players[2];
    Board board;
    int currentPlayer;

public:
    Game()
    {
        currentPlayer = 0;
        char symbols[] = {'X', 'O'};
        for (int i = 0; i < 2; i++)
        {
            cout << "Enter the name for player " << symbols[i] << ": ";
            string name;
            getline(cin, name);
            players[i].setter(name, symbols[i]);
        }
        board.initializeBoard();
    }

    ~Game()
    {
    }

    void play()
    {
        bool gameWon = false;
        while (!board.isFull() && !gameWon)
        {
            board.displayBoard();
            Player &player = players[currentPlayer];
            cout << player.getName() << "'s turn (" << player.getSymbol() << ")\n";
            int row, col;
            cout << "Enter row and column: ";
            cin >> row >> col;
            if (board.makeMove(row, col, player.getSymbol()))
            {
                if (board.checkWin(player.getSymbol()))
                {
                    board.displayBoard();
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
            board.displayBoard();
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
