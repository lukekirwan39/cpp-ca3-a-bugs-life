
#include <iostream>
#include <thread>

#include "Board.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

int main(){
    Board board;
    int choice;
    do{
        cout << "\n===== Bugs Life Menu =====\n";
        cout << "\n1. Initialize Bug Board (load data from file)";
        cout << "\n2. Display all Bugs";
        cout << "\n3. Find a Bug (given an id)";
        cout << "\n4. Tap the Bug Board (cause all to move, then fight/eat)";
        cout << "\n5. Display Life History of all Bugs (path taken)";
        cout << "\n6. Display all Cells listing their Bugs";
        cout << "\n7. Run simulation (generates a Tap every tenth of a second)";
        cout << "\n8. Exit (write Life History of all Bugs to file)\n";

        while (!(cin >> choice) || choice < 1 || choice > 8){
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter a number between 1 and 8: ";
        }

        cin.ignore();

        switch (choice){
        case 1:{
            std::string filename = "bugs.txt";
            board.loadBugsFromFile(filename);
            cout << "Bug board initialized.\n";
            break;
        }

        case 2:
            board.displayBoard();
            break;

        case 3:{
            int searchId;
            cout << "Enter the bug id to search: ";
            cin >> searchId;
            Bug* result = board.findBugById(searchId);
            if (result != nullptr){
                cout << "Bug found: " << endl;
                result->display();
            } else{
                cout << "Bug " << searchId << " not found." << endl;
            }
            break;
        }

        case 4:
            board.moveAll();
            board.tapBoard();
            cout<<" All bugs have moved.\n";
            break;

        case 5:
            board.displayBugHistories();
            break;

        case 6:
            board.displayCells();
            break;

        case 7: {
            board.runSimulation();
            break;
        }

        case 8:
            board.writeLifeHistoryToFile();
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
            break;
        }


    }while (choice != 8);
    return 0;
}