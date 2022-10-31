#include <iostream>
#include <vector>

using namespace std;

// variable & function declarations
vector<int> puzzle(9);
char spaces[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

bool puzzDuplicate(int input);
void printPuzzle(vector<int> puzzle);

/* ----------------------------------------------------------------------------------------- */

// populates the board with -1
void defaultPuzzle() {
    for (int i = 0; i <= 8; i++) {
        puzzle.at(i) = -1;
    }
}

// user can choose a default board (test cases) between depths of 0, 2, 4, 8, 12, 16, 20, & 24
void testPuzzle() {
    int choice = 0;
    bool input = false;

    cout << endl << "Choose the depth of your default puzzle:" << endl
         << "1 - Depth 0" << endl
         << "2 - Depth 2" << endl
         << "3 - Depth 4" << endl
         << "4 - Depth 8" << endl
         << "5 - Depth 12" << endl
         << "6 - Depth 16" << endl
         << "7 - Depth 20"<< endl
         << "8 - Depth 24" << endl;

    while(!input) {
        cout << endl << "Enter your puzzle choice: ";
        cin >> choice;
        if (!(choice > 0 && choice < 9)) {
            cout << endl << "Error: Invalid Input. Please choose an option between 1-8." << endl;
        }
        else {
            input = true;
        }
    }

    if (choice == 1) {
        vector<int> depth0{1, 2, 3, 4, 5, 6, 7, 8, 0};
        puzzle = depth0;
    }
    else if (choice == 2) {
        vector<int> depth2{1, 2, 3, 4, 5, 6, 0, 7, 8};
        puzzle = depth2;
    }
    else if (choice == 3) {
        vector<int> depth4{1, 2, 3, 5, 0, 6, 4, 7, 8};
        puzzle = depth4;
    }
    else if (choice == 4) {
        vector<int> depth8{1, 3, 6, 5, 0, 2, 4, 7, 8};
        puzzle = depth8;
    }
    else if (choice == 5) {
        vector<int> depth12{1, 3, 6, 5, 0, 7, 4, 8, 2};
        puzzle = depth12;
    }
    else if (choice == 6) {
        vector<int> depth16{1, 6, 7, 5, 0, 3, 4, 8, 2};
        puzzle = depth16;
    }
    else if (choice == 7) {
        vector<int> depth20{7, 1, 2, 4, 8, 5, 6, 3, 0};
        puzzle = depth20;
    }
    else if (choice == 8) {
        vector<int> depth24{0, 7, 2, 4, 6, 1, 3, 5, 8};
        puzzle = depth24;
    }
    cout << endl;
    printPuzzle(puzzle);
}

// user can create their own 8-Puzzle
void createPuzzle() {
    int input;
    bool done = false;
    bool choiceCheck;

    cout << endl << "Puzzle Board:" << endl
         << "a  b  c" << endl
         << "d  e  f" << endl
         << "g  h  i" << endl;

    cout << "Enter 0 for space area" << endl << endl;

    for (int i = 0; i <= 8; i++) {
        done = false;
        while (!done) {
            cout << "Enter space " << spaces[i] << ": ";
            cin >> input;

            if (input < 0 || input > 8) {
                cout << endl << "Error: Invalid Input." << endl << endl;
            }
            else {
                choiceCheck = puzzDuplicate(input);
                if (!choiceCheck) {
                    cout << endl << "Error: Duplicate Input." << endl << endl;
                }
                else {
                    puzzle.at(i) = input;
                    done = true;
                }
            }
        }
    }
    cout << endl;
    printPuzzle(puzzle);
}

// checks if user puts in duplicate values when creating puzzle
bool puzzDuplicate(int input) {
    bool puzzValid = true;

    for (int i = 0; i <= 8; i++) {
        if (input == puzzle.at(i)) {
            puzzValid = false;
            break;
        }
        else {
            puzzValid = true;
        }
    }

    return puzzValid;
}

// prints puzzle
void printPuzzle(vector<int>) {
    cout << "Your 8-Puzzle is:" << endl;
    for (int i = 0; i <= 8; i++) {
        cout << puzzle.at(i);
        if (i == 2 || i == 5) {
            cout << endl;
        }
        else {
            cout << "  ";
        }
    }
    cout << endl << endl;
}

/* ----------------------------------------------------------------------------------------- */

void solvePuzzle(vector<int>, int) {

}

/* ----------------------------------------------------------------------------------------- */

int main() {
    int puzzleChoice = 0;
    int algChoice = 0;
    bool puzzleOption = false;
    bool algOption = false;

    // initial message
    cout << endl << "Welcome to Trinah's 8-Puzzle Solver" << endl << endl;
    defaultPuzzle();

    // user chooses puzzle option (default or create their own)
    while (!puzzleOption) {
        cout << "Type '1' to use a default puzzle or '2' to enter your own puzzle" << endl;
        cin >> puzzleChoice;

        if (puzzleChoice == 1) {
            puzzleOption = true;
            testPuzzle();
        }
        else if (puzzleChoice == 2) {
            puzzleOption = true;
            createPuzzle();
        }
        else {
            cout << "Error: Invalid puzzle option." << endl;
            puzzleOption = false;
        }
    }

    // user chooses algorithm choice to run 8-Puzzle
    while (!algOption) {
        cout << "Enter your choice of algorithm" << endl
             << "1 - Uniform Cost Search" << endl
             << "2 - A* with the Misplaced Tile heuristic" << endl
             << "3 - A* with the Euclidean Distance heuristic" << endl;
        cin >> algChoice;

        if (!(algChoice == 1 || algChoice == 2 || algChoice == 3)) {
            cout << endl << "Error: Invalid algorithm option." << endl << endl;
            algOption = false;
        }
        else {             
            algOption = true;
            solvePuzzle(puzzle, algChoice);
        }
    }

    return 0;
}