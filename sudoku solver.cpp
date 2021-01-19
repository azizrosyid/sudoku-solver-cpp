#include <iostream> // cout, cin
using namespace std;

// function declaration
bool validateBlock(const int (&)[9][9], const int (&)[2], const int &);
bool validateRow(int[9][9], int[2], int);
bool validateColumn(const int (&)[9][9], const int (&)[2], int);
bool validateNumber(int (&)[9][9], int (&)[2], int);
void printSudoku(int (&)[9][9]);
void findEmptyNumber(const int (&)[9][9], int (&)[9 * 9][2], int &);
bool solveSudoku(int (&)[9][9]);
int inputInteger(string);
void breakLine();
void resetSudoku(int (&)[9][9]);
bool inputYesNo(string);
int inputNumberRange(string, int, int);

int main() {
    int choice;
    do {
        // main menu
        cout << "Program Untuk Menyelesaikan Sudoku" << endl
             << "1. Input Sudoku" << endl
             << "2. Contoh Sudoku" << endl
             << "0. Keluar" << endl;
        choice = inputNumberRange("Pilih : ", 0, 2);
        if (choice == 1) {
            int inputSudoku[9][9];
            resetSudoku(inputSudoku);
            int choice;
            do {
                breakLine();
                printSudoku(inputSudoku);
                cout << "Note : Angka Nol merepresentasikan Cell yang kosong." << endl
                     << "Pilih : " << endl
                     << "1. Isi Sudoku" << endl
                     << "2. Selesaikan Sudoku" << endl
                     << "3. Reset Sudoku" << endl
                     << "0. Keluar" << endl;
                choice = inputNumberRange("Masukkan Angka : ", 0, 3);
                if (choice == 1) {
                    int row, col, number;
                    do {
                        breakLine();
                        printSudoku(inputSudoku);
                        row = inputNumberRange("Masukkan Baris : ", 1, 9) - 1;
                        col = inputNumberRange("Masukkan Kolom : ", 1, 9) - 1;
                        int coordinate[2] = {row, col};
                        while (true) {
                            number = inputNumberRange("Masukkan Angka yang akan di isi : ", 0, 9);
                            if (validateNumber(inputSudoku, coordinate, number) || number == 0) {
                                inputSudoku[row][col] = number;
                                break;
                            } else {
                                cout << "Angka yang anda masukkan terjadi konflik" << endl;
                            }
                        }

                        breakLine();
                        printSudoku(inputSudoku);

                    } while (inputYesNo("Apakah Anda ingin mengisi lagi ? Y/N : "));
                } else if (choice == 2) {
                    solveSudoku(inputSudoku);
                } else if (choice == 3) {
                    resetSudoku(inputSudoku);
                } else if (choice != 0) {
                    cout << "Pilihan Tidak Ada." << endl;
                    cin.ignore();
                    cin.ignore();
                }

            } while (choice != 0);
        } else if (choice == 2) {
            int sudokuUnsolved[5][9][9] = {
                {{8, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 3, 6, 0, 0, 0, 0, 0},
                 {0, 7, 0, 0, 9, 0, 2, 0, 0},
                 {0, 5, 0, 0, 0, 7, 0, 0, 0},
                 {0, 0, 0, 0, 4, 5, 7, 0, 0},
                 {0, 0, 0, 1, 0, 0, 0, 3, 0},
                 {0, 0, 1, 0, 0, 0, 0, 6, 8},
                 {0, 0, 8, 5, 0, 0, 0, 1, 0},
                 {0, 9, 0, 0, 0, 0, 4, 0, 0}},
                {{0, 7, 0, 0, 0, 0, 0, 6, 8},
                 {0, 4, 0, 0, 0, 2, 0, 1, 9},
                 {1, 5, 6, 0, 0, 4, 7, 0, 0},
                 {0, 1, 4, 6, 7, 0, 9, 0, 0},
                 {0, 0, 3, 5, 0, 0, 0, 0, 6},
                 {0, 0, 0, 9, 0, 3, 8, 4, 0},
                 {0, 0, 7, 3, 0, 0, 0, 0, 0},
                 {0, 8, 9, 0, 0, 6, 0, 5, 7},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0}},
                {{9, 0, 0, 0, 8, 0, 0, 0, 1},
                 {0, 0, 0, 4, 0, 6, 0, 0, 0},
                 {0, 0, 5, 0, 7, 0, 3, 0, 0},
                 {0, 6, 0, 0, 0, 0, 0, 4, 0},
                 {4, 0, 1, 0, 6, 0, 5, 0, 8},
                 {0, 9, 0, 0, 0, 0, 0, 2, 0},
                 {0, 0, 7, 0, 3, 0, 2, 0, 0},
                 {0, 0, 0, 7, 0, 5, 0, 0, 0},
                 {1, 0, 0, 0, 4, 0, 0, 0, 7}},
                {{0, 0, 8, 0, 3, 0, 5, 4, 0},
                 {3, 0, 0, 4, 0, 7, 9, 0, 0},
                 {4, 1, 0, 0, 0, 8, 0, 0, 2},
                 {0, 4, 3, 5, 0, 2, 0, 6, 0},
                 {5, 0, 0, 0, 0, 0, 0, 0, 8},
                 {0, 6, 0, 3, 0, 9, 4, 1, 0},
                 {1, 0, 0, 8, 0, 0, 0, 2, 7},
                 {0, 0, 5, 6, 0, 3, 0, 0, 4},
                 {0, 2, 9, 0, 7, 0, 8, 0, 0}},
                {{0, 4, 6, 0, 0, 0, 0, 0, 0},
                 {9, 0, 2, 0, 6, 0, 0, 0, 8},
                 {0, 0, 8, 4, 0, 0, 2, 5, 0},
                 {0, 0, 0, 8, 0, 0, 0, 7, 0},
                 {5, 0, 0, 7, 0, 2, 0, 0, 3},
                 {0, 1, 0, 0, 0, 6, 0, 0, 0},
                 {0, 6, 4, 0, 0, 3, 9, 0, 0},
                 {3, 0, 0, 0, 8, 0, 1, 0, 2},
                 {0, 0, 0, 0, 0, 0, 7, 3, 0}}};
            int choiceSudoku;
            breakLine();
            for (int i = 0; i < 5; i++) {
                cout << i + 1 << ". " << endl;
                printSudoku(sudokuUnsolved[i]);
                cout << endl;
            }
            cout << "Note : Angka Nol merepresentasikan Cell yang kosong." << endl;
            do {
                choiceSudoku = inputNumberRange("Pilih Sudoku yang ingin diselesaikan : ", 1, 5) - 1;
                solveSudoku(sudokuUnsolved[choiceSudoku]);
                printSudoku(sudokuUnsolved[choiceSudoku]);
            } while (inputYesNo("Apakah anda ingin menyelesaikan sudoku lagi? Y/N : "));
        } else if (choice != 0) {
            cout << "Pilihan Tidak Ada." << endl;
            cin.ignore();
            cin.ignore();
        }

    } while (choice != 0);

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

    // extract first empty number
    int rowIndexFirst = coordinateEmpty[0][0];
    int columIndexFirst = coordinateEmpty[0][1];

    // loop until all coordinateEmpty solved
    for (int i = 0; i < lengthCoordinateEmpty;) {
        // extract rowIndex and columnIndex in coordinate
        int rowIndex = coordinateEmpty[i][0];
        int columnIndex = coordinateEmpty[i][1];

        // increament empty number sudoku
        sudoku[rowIndex][columnIndex] += 1;

        // if number is 10 then reset number to empty and goto previous number
        // goto previous because number now is conflict to another number
        if (sudoku[rowIndex][columnIndex] == 10) {
            // if the first empty number is 10, then no solution for this sudoku and return false
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

int inputInteger(string message) {
    int result;
    while (cout << message && !(cin >> result)) {
        cout << "Anda salah input, ulangi sampai benar " << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore();
    return result;
}

void breakLine() {
    cout << endl;
    cout << "======================" << endl;
    cout << endl;
}

void resetSudoku(int (&sudoku)[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            sudoku[row][col] = 0;
        }
    }
}

bool inputYesNo(string message) {
    string input;
    cout << endl;
    while (true) {
        cout << message;
        getline(cin, input);
        if (toupper(input[0]) == 'Y') {
            return true;
        } else if (toupper(input[0]) == 'N') {
            return false;
        } else {
            cout << "Input Y/N !" << endl;
        }
    }
}

int inputNumberRange(string message, int min, int max) {
    int result;
    do {
        result = inputInteger(message);
        if (result < min || result > max) {
            cout << "Masukkan angka " << min << "-" << max << endl;
        } else {
            break;
        }

    } while (true);
    return result;
}
