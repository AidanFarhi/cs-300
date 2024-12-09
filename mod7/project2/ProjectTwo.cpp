#include <iostream>
#include <fstream>

using namespace std;

/* Course object definition */
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

int loadCourses(unordered_map<string, Course> courses, string fileName) {
    ifstream file(fileName);
    string line;
    int numCourses = 0;
    while (getline(file, line)) {
        numCourses++;
        cout << line << endl;
    }
    file.close();
    return numCourses;
}

void printMenu() {
    cout << "- Options - " << endl;
    cout << "1. Load courses" << endl;
    cout << "2. Print all CS courses" << endl;
    cout << "3. Search for a course" << endl;
    cout << "9. Exit the program" << endl;
}

bool handleUserInput(unordered_map<string, Course> courses) {
    bool result = true;
    int choice;
    string fileName;
    cout << ">";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            loadCourses(courses, fileName);
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

    // start main loop
    while (keepRunning) {
        printMenu();
        keepRunning = handleUserInput(courses);
    }
}