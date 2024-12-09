#include <iostream>
#include <fstream>
#include <set>

using namespace std;

struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

bool isValidLine(string line) {
    vector<int> indexes;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') indexes.push_back(i);
    }
    if (indexes.size() < 1) return false;
    return true;
}

string getField(string line) {
    return line.substr(0, line.find(','));
}

void loadCourseNumbers(set<string> courseNumbers, string fileName) {
    ifstream file(fileName);
    string line;
    string courseNumber;
    while (getline(file, line)) {
        courseNumber = getField(line);
        courseNumbers.insert(courseNumber);
    }
    file.close();
}

int loadCourses(unordered_map<string, Course> courses, string fileName) {
    set<string> courseNumbers;
    loadCourseNumbers(courseNumbers, fileName);
    string line;
    int numCourses = 0;
    ifstream file(fileName);
    while (getline(file, line)) {
        cout << "line: " << line << endl;
        if (isValidLine(line)) {
            struct Course course;
            course.courseNumber = getField(line);
            line = line.substr(line.find(',')+1, line.length());
            course.courseName = getField(line);
            line = line.substr(line.find(',')+1, line.length());
            while (line.length() > 0 && line != ",") {
                course.prerequisites.push_back(getField(line));
                line = line.substr(line.find(',')+1, line.length());
            }
            cout << "courseNumber: " << course.courseNumber << endl;
            cout << "courseName: " << course.courseName << endl;
            cout << "prerequistes:" << endl;
            for (string p : course.prerequisites) {
                cout << p << endl;
            }
        }
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
    bool keepRunning = true;
    unordered_map<string, Course> courses;
    while (keepRunning) {
        printMenu();
        keepRunning = handleUserInput(courses);
    }
}
