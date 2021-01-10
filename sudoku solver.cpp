#include <iostream>
using namespace std;

// function declaration
bool validateBlock(const int (&)[9][9], const int (&)[2], const int &);
bool validateRow(int[9][9], int[2], int);
bool validateColumn(const int (&)[9][9], const int (&)[2], int);
bool validateNumber(int (&)[9][9], int (&)[2], int);
void printSudoku(int (&)[9][9]);
void findEmptyNumber(const int (&)[9][9], int (&)[9 * 9][2], int &);
bool solveSudoku(int (&)[9][9]);

int main() {
    // World Hardest Sudoku
    int sudokuUnsolved[9][9] = {{8, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 3, 6, 0, 0, 0, 0, 0},
                                {0, 7, 0, 0, 9, 0, 2, 0, 0},
                                {0, 5, 0, 0, 0, 7, 0, 0, 0},
                                {0, 0, 0, 0, 4, 5, 7, 0, 0},
                                {0, 0, 0, 1, 0, 0, 0, 3, 0},
                                {0, 0, 1, 0, 0, 0, 0, 6, 8},
                                {0, 0, 8, 5, 0, 0, 0, 1, 0},
                                {0, 9, 0, 0, 0, 0, 4, 0, 0}};

    cout << "Unsolved Sudoku : " << endl;
    // pretty print sudoku unsolved
    printSudoku(sudokuUnsolved);
    cout << endl;

    // solve the unsolved sudoku
    // if the solve sudoku return true, all empty number in sudoku have been filled
    // if return false, sudoku dont have solution, because human error when creating sudoku unsolved
    if (solveSudoku(sudokuUnsolved) == true) {
        cout << "Solved Sudoku : " << endl;
        // pretty print sudoku solved
        printSudoku(sudokuUnsolved);
        cout << endl;
    } else {
        cout << "No Solution For this Sudoku!" << endl;
    }

    return 0;
}

// function to solve sudoku
bool solveSudoku(int (&sudoku)[9][9]) {
    // Initiate array to store coordinate empty number in sudoku
    int coordinateEmpty[9 * 9][2];
    // Store length of array coordinateEmpty
    int lengthCoordinateEmpty = 0;
    // Find empty number in sudoku and store coordinate in array
    findEmptyNumber(sudoku, coordinateEmpty, lengthCoordinateEmpty);

    // loop until all coordinateEmpty solved
    for (int i = 0; i < lengthCoordinateEmpty;) {
        // extract rowIndex and columnIndex in coordinate
        int rowIndex = coordinateEmpty[i][0];
        int columnIndex = coordinateEmpty[i][1];

        // first empty number
        int rowIndexFirst = coordinateEmpty[0][0];
        int columIndexFirst = coordinateEmpty[0][1];

        // increament empty number sudoku
        sudoku[rowIndex][columnIndex] += 1;

        // if number is 10 then reset number to empty and goto previous number
        // goto previous because number now is conflict to another number
        if (sudoku[rowIndex][columnIndex] == 10) {
            if (sudoku[rowIndexFirst][columIndexFirst] == 10) {
                return false;
            }

            sudoku[rowIndex][columnIndex] = 0;
            i--;
        }
        //validate number to save in sudoku, if valid goto next empty number
        else if (validateNumber(sudoku, coordinateEmpty[i], sudoku[rowIndex][columnIndex])) {
            i++;
        }
    }
    return true;
}

// function to validate number in block
bool validateBlock(const int (&sudoku)[9][9], const int (&coordinate)[2], const int &number) {
    int coordinateBlock[2];
    // find the first coordinate block of number
    coordinateBlock[0] = (coordinate[0] / 3) * 3;
    coordinateBlock[1] = (coordinate[1] / 3) * 3;

    // looping block 3x3
    for (int rowIndex = 0; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 0; columnIndex < 3; columnIndex++) {
            int row = rowIndex + coordinateBlock[0];
            int column = columnIndex + coordinateBlock[1];

            // if number in row same as number to save, then number can't save in sudoku
            // exclude if the position number to check same as number to save
            if (sudoku[row][column] == number && !(row == coordinate[0] && column == coordinate[1])) {
                return false;
            }
        }
    }
    // return true value if no same number in the block
    return true;
}

// function to validate number in row
bool validateRow(int sudoku[9][9], int coordinate[2], int number) {
    // extract coordinate to variable
    int row = coordinate[0];
    int column = coordinate[1];
    // looping number in the row
    for (int columnIndex = 0; columnIndex < 9; columnIndex++) {
        // if number in row same as number to save, then number can't save in sudoku
        // exclude if the position number to check same as number to save
        if (sudoku[row][columnIndex] == number && !(columnIndex == column)) {
            return false;
        }
    }
    // return true value if no same number in the row
    return true;
}

// function to validate number in column
bool validateColumn(const int (&sudoku)[9][9], const int (&coordinate)[2], int number) {
    // extract coordinate to variable
    int row = coordinate[0];
    int column = coordinate[1];
    // looping number in vertical row (column)
    for (int rowIndex = 0; rowIndex < 9; rowIndex++) {
        // if number in row same as number to save, then number can't save in sudoku
        // exclude if the position number to check same as number to save
        if (sudoku[rowIndex][column] == number && !(rowIndex == row)) {
            return false;
        }
    }
    // return true value if no same number in the column
    return true;
}

// function to validate the number, if can store in the sudoku return true
bool validateNumber(int (&sudoku)[9][9], int (&coordinate)[2], int number) {
    // validate number in block, row, and column
    if (!validateBlock(sudoku, coordinate, number)) {
        return false;
    } else if (!validateRow(sudoku, coordinate, number)) {
        return false;
    } else if (!validateColumn(sudoku, coordinate, number)) {
        return false;
    }

    // return true value if all validate is true
    return true;
}

// function to pretty print board sudoku
void printSudoku(int (&sudoku)[9][9]) {
    for (int i = 0; i < 9; i++) {
        // if i is 3 or 6, print line break
        if (i % 3 == 0 && i != 0) {
            cout << "------+-------+------" << endl;
        }

        // print number
        for (int j = 0; j < 9; j++) {
            // if j is 3 or 6 print line break
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            // print the number
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
}

// function to find empty number and save coordinate in array
void findEmptyNumber(const int (&sudokuUnsolved)[9][9], int (&coordinateEmpty)[9 * 9][2], int &lengthCoordinateEmpty) {
    // looping 9x9 array
    for (int rowIndex = 0; rowIndex < 9; rowIndex++) {
        for (int columnIndex = 0; columnIndex < 9; columnIndex++) {
            // if number now is 0, save to array and increment the variable length
            if (sudokuUnsolved[rowIndex][columnIndex] == 0) {
                coordinateEmpty[lengthCoordinateEmpty][0] = rowIndex;
                coordinateEmpty[lengthCoordinateEmpty][1] = columnIndex;
                lengthCoordinateEmpty++;
            }
        }
    }
}
