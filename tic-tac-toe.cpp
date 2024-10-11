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

    void setter(string playerName, char playerSymbol)
    {
        this->name = playerName;
        this->symbol = playerSymbol;
    }

    void getter() const
    {
        cout << "Player Name: " << this->name << endl;
        cout << "Player Symbol: " << this->symbol << endl;
    }

    char getSymbol() const
    {
        return this->symbol;
    }

    static int getPlayerCount()
    {
        return playerCount;
    }

    void display() const
    {
        cout << "Player: " << this->name << " (" << this->symbol << ")\n";
    }
};

int Player::playerCount = 0;

class Board
{
private:
    char board[3][3];

public:
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
};

int main()
{
    Player *players = new Player[2];

    char symbols[] = {'X', 'O'};
    for (int i = 0; i < 2; i++)
    {
        cout << "Enter the name for player " << symbols[i] << ": ";
        string name;
        getline(cin, name);
        players[i].setter(name, symbols[i]);
    }

    Board *board = new Board;
    board->initializeBoard();

    cout << "Number of players: " << Player::getPlayerCount() << endl;

    board->displayBoard();

    for (int i = 0; i < 2; i++)
    {
        cout << "Details of Player " << (i + 1) << ":" << endl;
        players[i].getter();
    }

    board->makeMove(0, 0, players[0].getSymbol());
    board->displayBoard();

    delete[] players;
    delete board;

    return 0;
}
