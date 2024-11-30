//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Aidan Farhi
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

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

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    this->root = nullptr;
}

/**
 * Recursively deletes all nodes in a Binary Search Tree
 */
void deleteTree(Node* n) {
    // base case
    if (n == nullptr) return;
    // grab the left and right nodes as variables
    Node* left = n->left;
    Node* right = n->right;
    // free the memory of the current node
    delete n;
    // call function on left node
    deleteTree(left);
    // call function on right node
    deleteTree(right);
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    deleteTree(this->root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass in root
    inOrder(this->root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // call postOrder function and pass in root
    postOrder(this->root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // call preOrder function and pass in root
    preOrder(this->root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // if root equal to nullptr
    if (this->root == nullptr) {
        // root is equal to new node bid
        this->root = new Node(bid);
    } else {
        // add Node root and bid
        addNode(this->root, bid);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // remove node root bidID
    removeNode(this->root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // set current node equal to root   
    Node* current = this->root;
    // keep looping downwards until bottom reached or matching bidId found
    while (current != nullptr) {
        if (current->bid.bidId == bidId) { // if match found, return current bid
            return current->bid;
        } else if (current->bid.bidId > bidId) { // current node is greater, traverse left
            current = current->left;
        }
        else { // current node smaller, traverse right
            current = current->right;
        }
    }
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    if (node->bid.bidId == bid.bidId) {       // if node is the same, update the bid
        node->bid = bid;
    } else if (node->bid.bidId > bid.bidId) { // if node is larger then add to left
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(bid);
        } else {
            // recurse down the left node
            addNode(node->left, bid);
        }
    } else {                                  // if node is smaller add to the right
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(bid);
        } else {
            // recurse down the right node
            addNode(node->right, bid);
        }            
    }
}

void BinarySearchTree::inOrder(Node* node) {
    // base case
    if (node == nullptr) return;
    // call inOrder on the left node
    inOrder(node->left);
    // output bidID, title, amount, fund
    cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount
        << " | " << node->bid.fund << endl;
    // call inOrder on the right node
    inOrder(node->right);
}

void BinarySearchTree::postOrder(Node* node) {
    // base case
    if (node == nullptr) return;
    // call postOrder on left node
    postOrder(node->left);
    // call postOrder on right node
    postOrder(node->right);
    // output bidID, title, amount, fund
    cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount
        << " | " << node->bid.fund << endl;
}

void BinarySearchTree::preOrder(Node* node) {
    // base case
    if (node == nullptr) return;
    // output bidID, title, amount, fund
    cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount
        << " | " << node->bid.fund << endl;
    // call preOrder on left node
    preOrder(node->left);
    // call preOrder on right right
    preOrder(node->right);
}

/**
 * Finds the minimum node of a tree or subtree.
 */
Node* findMinNode(Node* node) {
    // traverse down the left side of the tree
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

/**
 * Deletes the minimum node of a tree or subtree.
 */
Node* deleteMinNode(Node* node) {
    // if node is null, return nullptr
    if (node == nullptr) return nullptr;
    // if node has no left child, delete the node and return the right node.
    if (node->left == nullptr) {
        Node* temp = node->right;
        delete node;
        return temp;
    }
    // if node has a left child, recursively call until min is found
    node->left = deleteMinNode(node->left);
    return node;
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // if node is null, return node
    if (node == nullptr) return node;

    // search for a matching bidId in the tree
    if (bidId < node->bid.bidId) {          // if bid is less than the node's bid, go left
        node->left = removeNode(node->left, bidId);
    } else if (bidId > node->bid.bidId) {   // if bid is greater than the node's bid, go right
        node->right = removeNode(node->right, bidId);
    } else {                                // the node to delete has been found
        // case 1: node is a leaf node
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        // case 2: node has at least one child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        // case 3: node has two children
        // first find the minimum node in the right subtree which is the successor
        Node* successor = findMinNode(node->right);
        // reassign the current node with the successor's bid
        node->bid = successor->bid;
        // delete the successor
        node->right = deleteMinNode(node->right);
    }
    return node;
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
void loadBids(string csvPath, BinarySearchTree* bst) {
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
            bst->Insert(bid);
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

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

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
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

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
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;
    bst->~BinarySearchTree();

	return 0;
}
