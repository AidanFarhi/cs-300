#include <iostream>
using namespace std;

bool binary_search(vector<int> nums, int x) {
    int mid = 0;
    int low = 0;
    int hi = nums.size() - 1;
    while (low <= hi) {
        mid = (hi + low) / 2;
        if (nums.at(mid) < x) {
            low = mid + 1;
        }
        else if (nums[mid] > x) {
            hi = mid - 1;
        }
        else {
            return true;
        }
    }
    return false;
}

int main() {
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int x = 9;
    cout << binary_search(data, x) << endl;
}