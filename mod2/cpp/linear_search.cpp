#include <iostream>
using namespace std;

bool linear_search(vector<int> nums, int x) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums.at(i) == x) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<int> data = {1, 2, 3, 4, 5};
    int x = 4;
    cout << linear_search(data, x) << endl;
}