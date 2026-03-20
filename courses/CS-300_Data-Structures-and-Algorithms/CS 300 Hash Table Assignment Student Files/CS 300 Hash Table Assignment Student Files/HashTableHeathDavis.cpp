//============================================================================
// Name        : HashTable.cpp
// Author      : Heath Davis
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 4-2 Hash Table
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node* next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node*> table;
    unsigned int tableSize;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    tableSize = DEFAULT_SIZE;
    table.resize(tableSize);
    for (unsigned int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

/**
 * Constructor for specifying size of the table
 */
HashTable::HashTable(unsigned int size) {
    this->tableSize = size;
    table.resize(tableSize);
    for (unsigned int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    for (unsigned int i = 0; i < tableSize; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

/**
 * Calculate the hash value of a given key.
 */
unsigned int HashTable::hash(int key) {
    return key % tableSize;
}

/**
 * Insert a bid
 */
void HashTable::Insert(Bid bid) {
    unsigned key = hash(atoi(bid.bidId.c_str()));
    Node* newNode = new Node(bid, key);

    if (table[key] == nullptr) {
        table[key] = newNode;
    }
    else {
        newNode->next = table[key];
        table[key] = newNode;
    }
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    for (unsigned int i = 0; i < tableSize; ++i) {
        Node* current = table[i];
        if (current != nullptr) {
            cout << "Key " << i << ": ";
            while (current != nullptr) {
                cout << current->bid.bidId << ": " << current->bid.title << " | "
                    << current->bid.amount << " | " << current->bid.fund;
                current = current->next;
                if (current != nullptr) {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
    }
}

/**
 * Remove a bid
 */
void HashTable::Remove(string bidId) {
    unsigned key = hash(atoi(bidId.c_str()));
    Node* current = table[key];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            if (prev == nullptr) {
                table[key] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

/**
 * Search for the specified bidId
 */
Bid HashTable::Search(string bidId) {
    Bid bid;
    unsigned key = hash(atoi(bidId.c_str()));
    Node* current = table[key];

    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            return current->bid;
        }
        current = current->next;
    }
    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    csv::Parser file = csv::Parser(csvPath);

    try {
        for (unsigned int i = 0; i < file.rowCount(); i++) {
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');
            hashTable->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        cerr << e.what() << endl;
    }
}

/**
 * Convert a string to a double after stripping out unwanted char
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    clock_t ticks;
    HashTable* bidTable = new HashTable();

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ticks = clock();
            loadBids(csvPath, bidTable);
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();
            Bid bid = bidTable->Search(bidKey);
            ticks = clock() - ticks;

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;
    delete bidTable;
    return 0;
}