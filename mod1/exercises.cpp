#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_ELEMENTS = 3;
   vector<int> userVals(NUM_ELEMENTS);
   unsigned int i;

   userVals.at(0) = 2;
   userVals.at(1) = 4;
   userVals.at(2) = 8;

   userVals.at(0) = userVals.at(2);
   userVals.at(2) = userVals.at(0);

   for (i = 0; i < userVals.size(); ++i) {
      cout << userVals.at(i) << endl;
   }

   return 0;
}