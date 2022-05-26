#include "Sudoku.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

#include <iostream>

using std::cout;
using std::endl;

bool fillBoard(Sudoku * board, const vector<string> & fillWith) {
    
    for (size_t row = 0; row < fillWith.size(); ++row) {
        for (size_t col = 0; col < fillWith.size(); ++col) {
            if (fillWith[row][col] != ' ') {
                const int setTo = std::stoi(fillWith[row].substr(col,1));
                if (!board->setSquare(row, col, setTo)) {
                    cout << "Error: setSquare returned false after setting square[" << row << "][" << col << "] to " << setTo << " - this should happen as the example boards are solvable\n";
                    return false;
                }
            }
        }
    }
    
    return true;
}


bool checkAnswer(Sudoku * board, const vector<string> & answer) {
    
    for (size_t row = 0; row < answer.size(); ++row) {
        for (size_t col = 0; col < answer.size(); ++col) {
            const int setTo = std::stoi(answer[row].substr(col,1));
            if (board->getSquare(row,col) != setTo) {
                cout << "Error: wrong answer in square[" << row << "][" << col << "]: should be " << setTo << " but is " << board->getSquare(row,col) << endl;
                return false;
            }
        }
    }
    
    return true;
}


int main() {
    
    {
        vector<string> easyBoard{"23 915   ",
                                 "   2  54 ",
                                 "6 7      ",
                                 
                                 "  1     9",
                                 "89 5 3 17",
                                 "5     6  ",
                                 
                                 "      9 5",
                                 " 16  7   ",
                                 "   329  1"};
        
        cout << "Making Sudoku board for an easy puzzle:\n";
        for (const auto & s : easyBoard) {
            cout << s << endl;
        }
                                 
        vector<string> easyAnswer{  "234915786",
                                    "189276543",
                                    "657438192",
                                    "461782359",
                                    "892563417",
                                    "573194628",
                                    "328641975",
                                    "916857234",
                                    "745329861"};
   
                                 
        unique_ptr<Sudoku> board(new Sudoku(9));

        if (!fillBoard(board.get(), easyBoard)) {
            cout << "Failed: When filling the board, setSquare() returned false\n";
            return 1;
        }
        
        if (!checkAnswer(board.get(), easyAnswer)) {
            cout << "Failed: The board has the wrong answer in it\n";
            board->write(cout);
            return 1;
        }
        
    }

    
    cout << "Passed: easy sudoku puzzle solved, every square had the right answer\n";
    return 0;
}
