#include <iostream>
using namespace std;

void insertion_sort(vector<int>* nums) {
    int i, j, temp = 0;
    for (i = 1; i < nums->size(); i++) {
        j = i;
        while (j > 0 && nums->at(j) < nums->at(j-1)) {
            temp = nums->at(j);
            nums->at(j) = nums->at(j-1);
            nums->at(j - 1) = temp;
            j--;
        }
    }
}

int main() {
    vector<int> data = {5, 3, 43, 23, 1, 6, 4, 34, 0, 9, -23};
    insertion_sort(&data);
    for (int n : data) {
        cout << n << " ";
    }
    cout << endl;
}