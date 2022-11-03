#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#include <iterator>
#include <ctime>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

// variable & function declarations
vector<int> puzzle(9);
char spaces[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

vector<int> goal{1, 2, 3, 4, 5, 6, 7, 8, 0};

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
    cout << endl << "Your 8-Puzzle is:" << endl;
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
        while (done == false) {
            cout << "Enter space " << spaces[i] << ": ";
            cin >> input;

            if (input >= 0 && input <= 8) {
                choiceCheck = puzzDuplicate(input);
                if (choiceCheck == false) {
                    cout << endl << "Error: Duplicate Input." << endl << endl;
                }
                else {
                    puzzle.at(i) = input;
                    done = true;
                }
            }
            else {
                cout << endl << "Error: Invalid Input." << endl << endl;
            }
        }
    }
    cout << endl << "Your 8-Puzzle is:" << endl;
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
void printPuzzle(vector<int> currPuzzle) {
    for (int i = 0; i <= 8; i++) {
        cout << currPuzzle.at(i);
        if (i == 2 || i == 5) {
            cout << endl;
        }
        else {
            cout << "  ";
        }
    }
    cout << endl;
}

/* ----------------------------------------------------------------------------------------- */

class Node {
    public:
        vector<int> board;
        int algorithm;
        int heuristic;
        int cost;
        struct Node* up;
        struct Node* down;
        struct Node* left;
        struct Node* right;

        Node(vector<int> puzzle, int algChoice) {
            board = puzzle;
            algorithm = algChoice;
            heuristic = determineH(puzzle, algChoice);
            cost = 0;
            up = down = left = right = NULL;
        }

        // uniform cost search h(n) = 0
        int uniformCost() { 
            return 0; 
        }

        // h(n) = # of misplaced tiles
        int misplacedTile(vector<int> puzzle) {
            int misplaced = 0;
            for (int i = 0; i < 9; i++) {
                if(puzzle.at(i) != goal.at(i)) {
                    misplaced++;
                }
            }

            if (puzzle.at(8) != 0) {
                misplaced -= 1;
            }
            return misplaced;
        }

        // h(n) = sum of misplaced tile distances
        int manhattanDistance(vector<int> puzzle) {
            int distance = 0;
            for (int i = 0; i < 9; i++) {
                if (puzzle.at(i) != 0 && puzzle.at(i) != goal.at(i)) {
                    //             x = goal state - current state      y = goal state - current state
                    distance += abs((puzzle.at(i) - 1) / 3 - i / 3) + abs((puzzle.at(i) - 1) % 3 - i % 3); // calculate spot coordinates
                }
            }
            return distance;
        }

        int determineH(vector<int> puzzle, int algChoice) {
            if (algChoice == 1) {
                algChoice = uniformCost();
            }
            else if (algChoice == 2) {
                algChoice = misplacedTile(puzzle);
            }
            else if (algChoice == 3) {
                algChoice = manhattanDistance(puzzle);
            }
            return algChoice;
        }
};

/* ----------------------------------------------------------------------------------------- */

queue<Node*> puzzQ;
vector<vector<int> > duplicate;
int maxQueue = 0, nodesExp = 0;

void printTraceback(Node* current) {
    cout << "The best state to expand with a g(n) = " << current->cost
         << " and h(n) = " << current->heuristic << " is..." << endl;
    printPuzzle(current->board);
}

// update max # of nodes in the queue at a time
void checkMax() {
    if (puzzQ.size() > maxQueue) {
        maxQueue = puzzQ.size();
    }
}

bool checkDupBoard(vector<int> curr) {
    bool ifDuplicate = false;

    for (int i = 0; i < duplicate.size(); i++) {
        if (duplicate.at(i) == curr) {
            ifDuplicate = true;
            break;
        }
    }
    return ifDuplicate;
}

// create boards for tile moving up, down, left, or right
vector<int> createUp(vector<int> board, int index) {
    vector<int> newBoard = board;
    newBoard.at(index) = board.at(index - 3);
    newBoard.at(index - 3) = 0;
    return newBoard;
}

vector<int> createDown(vector<int> board, int index) {
    vector<int> newBoard = board;
    newBoard.at(index) = board.at(index + 3);
    newBoard.at(index + 3) = 0;
    return newBoard;
}

vector<int> createRight(vector<int> board, int index) {
    vector<int> newBoard = board;
    newBoard.at(index) = board.at(index + 1);
    newBoard.at(index + 1) = 0;
    return newBoard;
}

vector<int> createLeft(vector<int> board, int index) {
    vector<int> newBoard = board;
    newBoard.at(index) = board.at(index - 1);
    newBoard.at(index - 1) = 0;
    return newBoard;
}

// find node children (next possible move)
void expandNode() {
    int puzzSize = puzzQ.size();
    for (int i = 0; i < puzzSize; i++) {
        Node* current = puzzQ.front();
        checkMax();

        // find index of 0 
        vector<int>::iterator it;
        it = find(current->board.begin(), current->board.end(), 0);
        int index = it - current->board.begin();

        // can move up
        if (index / 3 != 0) {
            current->up = new Node(current->board, current->algorithm);
            current->up->cost = current->cost + 1;
            current->up->board = createUp(current->board, index);
            current->up->heuristic = current->determineH(current->up->board, current->algorithm);
            if (checkDupBoard(current->up->board) == false) {
                duplicate.push_back(current->up->board);
                puzzQ.push(current->up);
                nodesExp++;
            }
        }

        // can move down
        if (index / 3 != 2) {
            current->down = new Node(current->board, current->algorithm);
            current->down->cost = current->cost + 1;
            current->down->board = createDown(current->board, index);
            current->down->heuristic = current->determineH(current->down->board, current->algorithm);
            if (checkDupBoard(current->down->board) == false) {
                duplicate.push_back(current->down->board);
                puzzQ.push(current->down);
                nodesExp++;
            }
        }

        // can move right
        if (index % 3 != 2) {
            current->right = new Node(current->board, current->algorithm);
            current->right->cost = current->cost + 1;
            current->right->board = createRight(current->board, index);
            current->right->heuristic = current->determineH(current->right->board, current->algorithm);
            if (checkDupBoard(current->right->board) == false) {
                duplicate.push_back(current->right->board);
                puzzQ.push(current->right);
                nodesExp++;
            }
        }
        
        // can move left
        if (index % 3 != 0) {
            current->left = new Node(current->board, current->algorithm);
            current->left->cost = current->cost + 1;
            current->left->board = createLeft(current->board, index);
            current->left->heuristic = current->determineH(current->left->board, current->algorithm);
            if (checkDupBoard(current->left->board) == false) {
                duplicate.push_back(current->left->board);
                puzzQ.push(current->left);
                nodesExp++;
            }
        }

        puzzQ.pop();
        checkMax();
    }
}

// main searching algorithm function
// time of algorithm is in microseconds because when put in seconds it will just output 0 if less than 0
void solvePuzzle(vector<int> puzzle, int algChoice) {
    auto start = high_resolution_clock::now();
    Node* root = new Node(puzzle, algChoice);

    bool finish = false;
    puzzQ.push(root);
    duplicate.push_back(root->board);
    checkMax();
    nodesExp++;

    while (finish == false) {
        if (puzzQ.empty()) {
            cout << "Failure: Queue is empty." << endl;
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time in microseconds taken to find goal state: " << duration.count() << endl;
            finish = true;
            break;

        }
        else if (puzzQ.front()->board == goal) { // if starting board is goal state
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            printTraceback(puzzQ.front());
            cout << endl << "Goal state!" << endl << endl
                 << "Solution depth was: " << puzzQ.front()->cost << endl // cost + 1
                 << "Number of nodes expanded: " << nodesExp << endl      // every time add to queue + 1
                 << "Max queue size: " << maxQueue << endl                // queue.size()
                 << "Time in microseconds taken to find goal state: " << duration.count() << endl;
            puzzQ.pop();
            finish = true;
            break;
        }
        else {
            if (puzzQ.front()->algorithm == 1) {
                printTraceback(puzzQ.front());
                expandNode();
                puzzQ.pop();
            }
            else {
                queue<Node*> newQueue = puzzQ;
                Node* bestNode = puzzQ.front();
                int bestH = puzzQ.front()->heuristic;
                puzzQ.pop();
                while (puzzQ.size() > 0) {
                    Node* temp = puzzQ.front();
                    puzzQ.pop();
                    if (temp->heuristic < bestNode->heuristic) { // figure out the best heuristic
                        bestH = temp->heuristic;
                        bestNode = temp;
                    }
                }

                int size = newQueue.size();
                if (newQueue.size() != 0) { // put nodes with the best heuristic inside the queue
                    for (int j = 0; j < size; j++) {
                        Node* tempNode = newQueue.front();
                        newQueue.pop();
                        if (tempNode->heuristic == bestH) {
                                puzzQ.push(tempNode);
                                printTraceback(tempNode);
                        }
                    }
                }

                if (bestNode->heuristic == 0) {
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    printTraceback(bestNode);
                    cout << endl << "Goal state!" << endl << endl
                         << "Solution depth was: " << bestNode->cost << endl // cost + 1
                         << "Number of nodes expanded: " << nodesExp << endl // every time add to queue + 1
                         << "Max queue size: " << maxQueue << endl           // queue.size()
                         << "Time in microseconds taken to find goal state: " << duration.count() << endl;
                    finish = true;
                    break;
                }
                else {
                    expandNode(); // find node children (next moves)
                    newQueue = puzzQ;
                }
            }
        }
    }
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
        cout << endl << "Enter your choice of algorithm" << endl
             << "1 - Uniform Cost Search" << endl
             << "2 - A* with the Misplaced Tile heuristic" << endl
             << "3 - A* with the Manhattan Distance heuristic" << endl
             << endl << "Enter your algorithm choice: ";
        cin >> algChoice;
        cout << endl;

        if (algChoice == 1 || algChoice == 2 || algChoice == 3) {
            algOption = true;
            solvePuzzle(puzzle, algChoice);
        }
        else {
            cout << endl << "Error: Invalid algorithm option." << endl << endl;
            algOption = false;
        }
    }

    return 0;
}