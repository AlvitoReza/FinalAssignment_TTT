#include <iostream>
#define SIZE 3
//  Belajar relasi tod
enum GameStatus { InProgress, Draw, FirstPlayerWin, SecondPlayerWin };

enum Symbol { Dot , O, X };

class Player {  
    Symbol symbol;
    int id;
public :
    Player() : symbol(), id() { }
    Player(Symbol _symbol, int id) : symbol(_symbol), id(id) { }
    Symbol getSymbol() { return symbol; }
    int getNextMove() {
        int x;
        printf("Player %d [%c], ",  id , (symbol == 1) ? 'O' : 'X');
        std::cout << "Where you going to mark? : ";
        std::cin >> x;
        return x;
    }
    int getId() { return id; }
};

class Board {
    Symbol board[SIZE][SIZE] = {Dot};
    unsigned markCount = 0;
public :    
    //  Marking the symbol
    void markSymbol(int index, Symbol mark) {
            board[(index - 1) / SIZE][(index - 1) % SIZE] = mark;
            markCount++;
    }
    Symbol winCheck() {
        //  Vertical
        if(board[0][0] == board[1][0] && board[1][0] == board[2][0]) return board[0][0];
        else if(board[0][1] == board[1][1] && board[1][1] == board[2][1]) return board[0][1];
        else if((board[0][2] == board[1][2] && board[1][2] == board[2][2])) return board[0][2];
        //  Horizontal
        else if(board[0][0] == board[0][1] && board[0][1] == board [0][2]) return board[0][0];
        else if(board[1][0] == board[1][1] && board[1][1] == board [1][2]) return board[1][0];
        else if(board[2][0] == board[2][1] && board[2][1] == board [2][2]) return board[2][0];
        //  Diagonal
        else if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
        else if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];

        return Dot;                
    }
    int getMarkCount() { return markCount; }
    void printBoard() {
        for(int i = 0, flag = 1; i < SIZE; i++) {
            std::cout << "|";
            for(int j = 0; j < SIZE; j++, flag++) {
                if(board[i][j] == 1) std::cout << " O |";
                else if(board[i][j] == 2) std::cout << " X |";
                else std::cout << " " << flag << " |";
            }
            std::cout << "\n-------------\n";
        }
    }
};

class Game {
    Board board;
    Player firstP, secondP, *currP;
    GameStatus gameStatus;
    int moveIndex;
    bool firstPlayerTurn;
public :
    Game() : board(Board()),  currP(nullptr), gameStatus(), moveIndex(), firstPlayerTurn(false) { 
        //  Deciding who use certain symbol
        char s;
        while(firstP.getSymbol() == 0) {    
            std::cout << "Choose your symbol! (O / X) : "; std::cin >> s; 

            if(s == 'X' || s == 'x') firstP = Player(X, 1);
            else if(s == 'O' || s == 'x') firstP = Player(O, 1);
            else continue;
            secondP = Player((firstP.getSymbol() == O) ? X : O, 2);
        }
        //  Decide who play first
        int x;
        printf("Who Play First? Player 1 [%c] / ", (firstP.getSymbol() == 1) ? 'O' : 'X' );
        printf("Player 2 [%c] : ", (secondP.getSymbol() == 1) ? 'O' : 'X'); std::cin >> x;
            
        if(x == 1) firstPlayerTurn = true;
        
        currP = (firstPlayerTurn) ? &firstP : &secondP;
        printPlayerInfo();
    }  
    void play() {
        //  GameLoop
        while(gameStatus == InProgress) {
            //  Print First board
            board.printBoard();
            //  Player turn
            moveIndex = currP->getNextMove();
            //  keeping input 1 to 9
            if(moveIndex > 0 && moveIndex < 10) board.markSymbol(moveIndex, currP->getSymbol());
            else {
                std::cout << "Invalid input!\n";
                continue;
            }
            //  Win Checker before draw
            if(board.getMarkCount() > 4) gameStatus = setGameStatus();
            currP = (currP == &firstP) ? &secondP : &firstP;
        }
        //  Display last board
        board.printBoard();
        if(gameStatus == FirstPlayerWin) {
            std::cout << "The Winner Is Player " << firstP.getId();
            printf(" [%c]", (firstP.getSymbol() == 1) ? 'O' : 'X');
        } else if(gameStatus == SecondPlayerWin) {
            std::cout << "The Winner Is Player " << firstP.getId();
            printf(" [%c]", (secondP.getSymbol() == 1) ? 'O' : 'X');
        } else std::cout << "Game Is Draw\n";
    }  
    GameStatus setGameStatus() { 
        if(board.winCheck() == firstP.getSymbol()) return FirstPlayerWin;
        else if(board.winCheck() == secondP.getSymbol()) return SecondPlayerWin;
        else if(board.getMarkCount() == 9) return Draw;
        
        return InProgress;       
    }
    void printPlayerInfo() {
        printf("Player %d \tSymbol = %s\t ", firstP.getId(), (firstP.getSymbol() == X) ? "X" : "O");
        printf("Player %d \tSymbol = %s\n ", secondP.getId(), (secondP.getSymbol() == X) ? "X" : "O");
        printf("Who Play first? : %s\n", (firstPlayerTurn) ? "1" : "2");
    }
};

int main() {
    Game game;
    game.play();
}
