#include <iostream>
#include <vector>
using namespace std;

int main() {

    const int NUM_VALS = 8;
    vector<int> userVals(NUM_VALS);
    unsigned int i;

    cout << "Enter " << NUM_VALS << " integer values..." << endl;
    for (i = 0; i < NUM_VALS; i++) {
        cout << "> ";
        cin >> userVals.at(i);
    }

    cout << "You entered: ";
    for (i = 0; i < NUM_VALS; i++) {
        cout << userVals.at(i) << " ";
    }
    cout << endl;
}