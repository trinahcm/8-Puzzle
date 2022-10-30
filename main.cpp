#include <iostream>
#include <vector>

using namespace std;

// variable & function declarations
vector<int> puzzle(9);
char spaces[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

bool puzzDuplicate(int input);
void printPuzzle(vector<int> puzzle);

// populates the board with -1
void defaultPuzzle() {
    for (int i = 0; i <= 8; i++) {
        puzzle.at(i) = -1;
    }
}

void testPuzzle() {
    vector<int> depth = {1, 2, 3, 4, 5, 6, 0, 7, 8};
    // //puzzle = depth2;
    // printPuzzle(depth);
}

// user can create their own 8-Puzzle
void createPuzzle() {
    int input;
    int count = 0;
    bool done = false;
    bool choiceCheck;

    cout << "Puzzle Board:" << endl
         << "a  b  c" << endl
         << "d  e  f" << endl
         << "g  h  i" << endl;

    cout << "Enter 0 for space area" << endl << endl;

    for (int i = 0; i <= 8; i++) {
        done = false;
        while (!done) {
            cout << "Enter space " << spaces[count] << ": ";
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
                    count++;
                    done = true;
                    if (count == 9) {
                        break;
                    }
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
            printPuzzle(puzzle);
        }
        else if (puzzleChoice == 2) {
            puzzleOption = true;
            defaultPuzzle();
            createPuzzle();
        }
        else {
            cout << "Invalid puzzle option." << endl;
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

        if (algChoice == 1) {
            algOption = true;
        }
        else if (algChoice == 2) {
            algOption = true;
        }
        else if (algChoice == 3) {
            algOption = true;
        }
        else {
            cout << "Invalid algorithm option." << endl;
            algOption = false;
        }
    }

    return 0;
}