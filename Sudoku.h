#ifndef SUDOKU_H
#define SUDOKU_H

#include <algorithm>
#include <math.h>
#include <numeric>
#include "Searchable.h"
using std::vector;

class Sudoku : public Searchable {
private:    
    vector<vector<int> > grid;
    int sqrSize;
    int size;

public:
    Sudoku(int size) : size(size) {
        grid = vector<vector<int> >(size * size);
        sqrSize = sqrt(size);

        std::vector<int> values(size);
        std::iota(values.begin(), values.end(), 1);

        for (size_t i = 0; i < size * size; i++) {
            grid[i] = values;
        }
    }

    int getIndex(const int row, const int col) const {
        return (row * size) + col;
    }

    int getSquare(const int row, const int col) const {
        int pos = getIndex(row, col);

        if (grid[pos].size() != 1) {
            return -1;
        }

        return grid[pos][0];
    }

    bool removeValue(const int row, const int col, const int value) {
        for (size_t i = 0; i < size; i++) {
            if (i != col) {
                int currPos = getIndex(row, i);
                int sqr = getSquare(row, i);

                if (sqr == value) {
                    return false;
                } else if (sqr == -1) {
                    grid[currPos].erase(remove(grid[currPos].begin(), grid[currPos].end(), value), grid[currPos].end());
                    
                    if (getSquare(row, i) != -1) {
                        if (!removeValue(row, i, getSquare(row, i))) return false;
                    }
                }
            }
        }

        for (size_t i = 0; i < size; i++) {
            if (i != row) {
                int currPos = getIndex(i, col);
                int sqr = getSquare(i, col);

                if (sqr == value) {
                    return false;
                } else if (sqr == -1) {
                    grid[currPos].erase(remove(grid[currPos].begin(), grid[currPos].end(), value), grid[currPos].end());

                    if (getSquare(i, col) != -1) {
                        if (!removeValue(i, col, getSquare(i, col))) return false;
                    }
                }
            }
        }

        int sqrRow = (row / sqrSize) * sqrSize;
        int sqrCol = (col / sqrSize) * sqrSize;

        for (size_t i = 0; i < sqrSize; i++) {
            for (size_t j = 0; j < sqrSize; j++) {
                int currRow = sqrRow + i;
                int currCol = sqrCol + j;

                if (currRow != row && currCol != col) {
                    int currPos = getIndex(currRow, currCol);
                    int sqr = getSquare(currRow, currCol);

                    if (sqr == value) {
                        return false;
                    } else if (sqr == -1) {
                        grid[currPos].erase(remove(grid[currPos].begin(), grid[currPos].end(), value), grid[currPos].end());

                        if (getSquare(currRow, currCol) != -1) {
                            if (!removeValue(currRow, currCol, getSquare(currRow, currCol))) return false;
                        }
                    }
                }
            }
        }
        
        return true;
    }

    bool setSquare(const int row, const int col, const int value) {
        int pos = getIndex(row, col);
        vector<int> values;
        values.push_back(value);
        grid[pos] = values;

        return removeValue(row, col, value);
    }

    virtual bool isSolution() const override {
        for (size_t i = 0; i < grid.size(); i++) {
            if (grid[i].size() != 1) return false;
        }

        return true;
    }

    virtual vector<unique_ptr<Searchable> > successors() const override {
        vector<unique_ptr<Searchable> > res;

        for (size_t i = 0; i < grid.size(); i++) {
            int r = i / size;
            int c = i % size;

            if (getSquare(r, c) == -1) {
                for (size_t j = 0; j < grid[i].size(); j++) {
                    Sudoku gridCopy(*this);
                    
                    if (gridCopy.setSquare(r, c, grid[i][j])) {
                        res.push_back(std::make_unique<Sudoku>(gridCopy));
                    }
                }

                return res;
            }
        }

        return res;
    };

    virtual void write(ostream &os) const override {
        for (size_t r=0; r<size; r++) {
            for (size_t c=0; c<size; c++) {
                int value = getSquare(r,c);

                if (value == -1) {
                    os << " ";
                } else {
                    os << value;
                }
            }

            os << "\n";
        }
    }
};


#endif
