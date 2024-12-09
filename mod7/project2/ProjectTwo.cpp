#include <iostream>
using namespace std;

/* Course object definition */
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

void printMenu() {
    cout << "- Options - " << endl;
    cout << "1. Load courses" << endl;
    cout << "2. Print all CS courses" << endl;
    cout << "3. Search for a course" << endl;
    cout << "9. Exit the program" << endl;
}

bool handleUserInput(unordered_map<string, Course> courses, string fileName) {
    bool result = true;
    int choice;
    cout << ">";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "loading courses" << endl;
            break;
        case 2:
            cout << "printing CS courses" << endl;
            break;
        case 3:
            cout << "finding course" << endl;
            break;
        case 9:
            cout << "goodbye" << endl;
            result = false;
            break;
        default:
            cout << "invalid option" << endl;
            break;
    }
    return result;
}

int main() {

    // initialize data structures
    bool keepRunning = true;
    unordered_map<string, Course> courses;
    string fileName;

    // start main loop
    while (keepRunning) {
        printMenu();
        keepRunning = handleUserInput(courses, fileName);
    }
}