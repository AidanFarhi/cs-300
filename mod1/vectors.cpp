#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<int> itemCounts(3);

    itemCounts.at(0) = 122;
    itemCounts.at(1) = 119;
    itemCounts.at(2) = 117;

    cout << itemCounts.at(1) << endl;
}

