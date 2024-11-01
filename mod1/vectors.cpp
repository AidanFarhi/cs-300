#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<int> itemCounts(3);

    itemCounts.at(0) = 122;
    itemCounts.at(1) = 119;
    itemCounts.at(2) = 117;

    cout << itemCounts.at(1) << endl;

    vector<int> oldestPeople(5);
    int nthPerson;

    oldestPeople.at(0) = 122;
    oldestPeople.at(1) = 119;
    oldestPeople.at(2) = 117;
    oldestPeople.at(3) = 117;
    oldestPeople.at(4) = 116;

    cout << "enter N (1..5): ";
    cin >> nthPerson;
    if ((nthPerson >= 1) && (nthPerson <= 5)) {
        cout << "The " << nthPerson << "th oldest person lived ";
        cout << oldestPeople.at(nthPerson - 1) << " years." << endl;
    } else {
        cout << "N must be between 1 and 5" << endl;
    }

    return 0;
}

