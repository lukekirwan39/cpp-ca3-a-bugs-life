#include <iostream>
using std::string;
using std::cout;
using std::endl;
using std::cin;

int main(){
    int choice;
    do{
        cout << "\n===== Bugs Life Menu =====\n";
        cout << "\n1. Initialize Bug Board (load data from file)\n";
        cout << "\n2. Display all Bugs\n";
        cout << "\n3. Find a Bug (given an id)\n";
        cout << "\n4. Tap the Bug Board (cause all to move, then fight/eat)\n";
        cout << "\n5. Display Life History of all Bugs (path taken)\n";
        cout << "\n6. Display all Cells listing their Bugs\n";
        cout << "\n7. Run simulation (generates a Tap every tenth of a second)\n";
        cout << "\n8. Exit (write Life History of all Bugs to file)\n";

        while (!(cin >> choice) || choice < 1 || choice > 8){
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter a number between 1 and 8: ";
        }

        cin.ignore();

        switch (choice){
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        case 7:
            break;

        case 8:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
            break;
        }


    }while (choice != 8);
    return 0;
}