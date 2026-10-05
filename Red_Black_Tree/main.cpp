//
//  RedBlackTree.h
//  Red-Black-tree
//
//  Created by Kareem Ahmed on 2026-10-5.
//

#include <iostream>
#include <limits>
#include "Red_Black_Tree.h"
using namespace std;
bool readInt(int& value) {
    if (cin >> value)
        return true;
    cin.clear();                                              // reset error state
    cin.ignore(numeric_limits<streamsize>::max(), '\n');      // throw away bad input
    return false;
}


int main() {
    RedBlackTree tree;

    int choice = -1, val;


    //   // Insert nodes into the tree
    // tree.insert(10);
    // tree.insert(5);
    // tree.insert(15);
    // tree.insert(3);
    // tree.insert(7);
    // tree.insert(12);
    // tree.insert(18);

    // cout << "Red-Black Tree structure:" << std::endl;
    // tree.printTree();

    // // Remove a node from the tree
    // tree.remove(5);
    // cout << "\nAfter deleting node 5:" << std::endl;
    // tree.printTree();
    // cout << "\nSearching for node 12 in the tree:" << std::endl;
    // tree.searchAndPrint(12);


    do {
        cout << "\n===== Red-Black Tree Menu =====\n"
             << "1. Insert a value\n"
             << "2. Delete a value\n"
             << "3. Search for a value\n"
             << "4. Print the tree\n"
             << "0. Exit\n"
             << "Choose an option: ";

        if (!readInt(choice)) {
            cout << "Please enter a number from the menu.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                if (readInt(val)) {
                    tree.insert(val);
                    cout << val << " inserted.\n";
                } else {
                    cout << "Invalid number.\n";
                }
                break;

            case 2:
                cout << "Enter value to delete: ";
                if (readInt(val)) {
                    tree.remove(val);     // prints "not found" itself if missing
                } else {
                    cout << "Invalid number.\n";
                }
                break;

            case 3:
                cout << "Enter value to search: ";
                if (readInt(val))
                    tree.searchAndPrint(val);
                else
                    cout << "Invalid number.\n";
                break;

            case 4:
                cout << "\nRed-Black Tree structure:\n";
                tree.printTree();
                break;

            case 0:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid option, try again.\n";
        }
    } while (choice != 0);

    return 0;
}
