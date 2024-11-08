#include <iostream>
using namespace std;

void selection_sort(vector<int>* nums) {
    for (int i = 0; i < nums->size(); i++) {
        int smallest = i;
        for (int j = i+1; j < nums->size(); j++) {
            if (nums->at(j) < nums->at(smallest)) {
                smallest = j;
            }
        }
        int temp = nums->at(i);
        nums->at(i) = nums->at(smallest);
        nums->at(smallest) = temp;
    }
}

int main() {
    vector<int> data = {5, 4, -2, 33, 2, -534, 3242, 1};
    selection_sort(&data);
    for (int n : data) {
        cout << n << " ";
    }
    cout << endl;
}