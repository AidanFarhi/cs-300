//============================================================================
// Name        : HashTable.cpp
// Author      : Aidan Farhi
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 4-2 Hash Table
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

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
        Node *next;

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

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    size_t Size();
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // initialize the nodes vector with the default table size
    this->nodes = vector<Node>(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // initialize the nodes vector with the provided size
    this->nodes = vector<Node>(size);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // loop through all of the nodes in the vector
    for (Node n : this->nodes) {
        // traverse the list and delete all nodes
        Node* current = &n;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // return key modulo tableSize
    return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // create the key for the given bid
    int key = hash(stoi(bid.bidId));

    // retrieve node using key
    Node* node = &nodes[key];

    // if no entry is found for this key
    if (node->key == UINT_MAX || node->bid.bidId.empty()) {
        // assign bid to this node
        node->key = key;
        node->bid.bidId = bid.bidId;
        node->bid.title = bid.title;
        node->bid.fund = bid.fund;
        node->bid.amount = bid.amount;
    } else {
        // find the next open node and assign bid to it
        Node* newNode = new Node(bid, key);
        Node* current = node;
        while (current != nullptr) {
            if (current->next == nullptr) {
                // add new newNode to end of the list
                current->next = newNode;
                return;
            }
            current = current->next;
        }
    }
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // iterate over every node in the list
    for (Node n : this->nodes) {
        // if key not equal to UINT_MAX
        if (n.key != UINT_MAX) {
            // output key, bidID, title, amount and fund
            cout << "Key " << n.key << ": " << n.bid.bidId << " | " << n.bid.title 
                << " | " << n.bid.amount << " | " << n.bid.fund << endl;
            // node is equal to next iter
            Node* current = n.next;
            // while node not equal to nullptr
            while (current != nullptr) {
                // output key, bidID, title, amount and fund
                cout << current->key << ": " << current->bid.bidId << " | " << current->bid.title 
                    << " | " << current->bid.amount << " | " << current->bid.fund << endl;
                // node is equal to next node
                current = current->next;
            }
        }
    }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {

    // get the key for the given bidId
    int key = hash(stoi(bidId));

    // get the node for this key
    Node* n = &nodes[key];

    // check if there is an entry for this key
    if (n->key == UINT_MAX || n->bid.bidId.empty()) {
        return;
    }


    // check if the node is the only node in the list
    if (n->next == nullptr) {
        n->bid.bidId = "";   // set the bidId to an empty string
        n->bid.amount = 0.0; // set the amount to 0.0
        n->bid.fund = "";    // set the fund to an empty string
        n->bid.title = "";   // set the title to an empty string
        return;
    }

    // check if node is the first node in the list
    if (n->bid.bidId == bidId) {
        // put the next node at the front of the list
        nodes[key] = *n->next;
        // avoid stale references
        n->next = nullptr;
        return;
    }
    
    // initialize two variables to store node pointers
    Node* current = n;
    Node* temp;

    // traverse the list and remove the node with the matching bidId
    while (current->next != nullptr) {
        // if the next node bidID is equal to the current bidID
        if (current->next->bid.bidId == bidId) {
            // hold onto the next node temporarily
            temp = current->next;
            // make current node point beyond the next node
            current->next = current->next->next;
            // now free up memory held by temp
            delete temp;
            return;
        }
        current = current->next;
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {

    // initialize a bid variable
    Bid bid;

    // calculate the hash for the given bid
    int key = hash(stoi(bidId));

    // get the node for this key
    Node* n = &nodes[key];

    // if entry found for the key
    if (n->bid.bidId == bidId) {
        //return node bid
        return n->bid;
    }

    // if no entry found for the key
    if (n->key == UINT_MAX || n->bid.bidId.empty()) {
        // return bid
        return bid;
    }

    // traverse the list for a match
    while (n != nullptr) {
        // if the current node bid matches, return it
        if (n->bid.bidId == bidId) {
            return n->bid;
        }
        n = n->next;
    }
    // if no node is found, return bid
    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
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

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    bidTable = new HashTable();
    
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
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
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

    return 0;
}
