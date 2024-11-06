#include <iostream>
using namespace std;

int linear_search(vector<int> nums, int x) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums.at(i) == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<int> data;
    for (int i = 1; i < 6; i++) {
        data.push_back(i);
    }
    int x = 4;
    cout << linear_search(data, x) << endl;
}