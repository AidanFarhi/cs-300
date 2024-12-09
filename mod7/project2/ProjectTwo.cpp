#include <iostream>
#include <fstream>
#include <set>

using namespace std;

/**
 * Represents a course with its number, name, and prerequisites.
 */
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

/**
 * Validates if the line contains at least one comma to separate fields.
 * 
 * @param line The input line from the file.
 * @return True if the line is valid, false otherwise.
 */
bool isValidLine(string line) {
    vector<int> indexes;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') indexes.push_back(i);
    }
    if (indexes.size() < 1) return false;
    return true;
}

/**
 * Extracts the first field from a line until the first comma.
 * 
 * @param line The input line from the file.
 * @return The first field in the line.
 */
string getField(string line) {
    return line.substr(0, line.find(','));
}

/**
 * Loads course numbers from a file and inserts them into a set.
 * 
 * @param courseNumbers A set to store unique course numbers.
 * @param fileName The name of the file containing course data.
 */
void loadCourseNumbers(set<string>& courseNumbers, string fileName) {
    ifstream file(fileName);
    string line;
    string courseNumber;
    while (getline(file, line)) {
        courseNumber = getField(line);
        courseNumbers.insert(courseNumber);
    }
    file.close();
}

/**
 * Loads courses from a file into an unordered map.
 *
 * @param courses An unordered map to store course data.
 * @param fileName The name of the file containing course data.
 * @return The number of courses loaded.
 */
int loadCourses(unordered_map<string, Course>& courses, string fileName) {
    set<string> courseNumbers;
    loadCourseNumbers(courseNumbers, fileName);
    string line;
    int numCourses = 0;
    ifstream file(fileName);
    while (getline(file, line)) {
        if (isValidLine(line)) {
            struct Course course;
            course.courseNumber = getField(line);
            line = line.substr(line.find(',')+1, line.length());
            course.courseName = getField(line);
            line = line.substr(line.find(',')+1, line.length());
            while (line.length() > 1 && line != ",") {
                if (getField(line).length() > 0) course.prerequisites.push_back(getField(line));
                if (line.find(',') == string::npos) break;
                line = line.substr(line.find(',')+1, line.length());
            }
            for (string p : course.prerequisites) {
                if (courseNumbers.find(p) == courseNumbers.end()) {
                    continue;
                }
            }
            courses.insert({course.courseNumber, course});
            numCourses++;
        }
    }
    file.close();
    return numCourses;
}

/**
 * Prints the list of all courses in sorted order by course number.
 * 
 * @param courses An unordered map containing course data.
 */
void printCourses(unordered_map<string, Course> courses) {
    vector<string> courseNumbers;
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }
    sort(courseNumbers.begin(), courseNumbers.end());
    for (string courseNum : courseNumbers) {
        cout << courseNum << ", " << courses.find(courseNum)->second.courseName << endl;
    }
}

/**
 * Searches for and displays details of a specific course by course number.
 * 
 * @param courses An unordered map containing course data.
 * @param courseNumber The course number to search for.
 */
void findCourse(unordered_map<string, Course> courses, string courseNumber) {
    if (courses.find(courseNumber) != courses.end()) {
        Course course = courses.at(courseNumber);
        cout << "Course Number: " << course.courseNumber << endl;
        cout << "Course Name:   " << course.courseName << endl;
        cout << "Prerequisites: ";
        for (int i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites.at(i);
            if (i != course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    } else {
        cout << "Course Number " << courseNumber << " not found" << endl;
    }
}

/**
 * Prints the menu options for the user.
 */
void printMenu() {
    cout << "- Options - " << endl;
    cout << "1. Load courses" << endl;
    cout << "2. Print all CS courses" << endl;
    cout << "3. Search for a course" << endl;
    cout << "9. Exit the program" << endl;
}

/**
 * Handles user input and executes the corresponding functionality.
 * 
 * @param courses An unordered map to store course data.
 * @return True to continue the program, false to exit.
 */
bool handleUserInput(unordered_map<string, Course>& courses) {
    bool result = true;
    int choice;
    int coursesLoaded = 0;
    string fileName;
    string courseNumber;
    cout << ">";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            coursesLoaded = loadCourses(courses, fileName);
            cout << coursesLoaded << " courses loaded" << endl;
            break;
        case 2:
            printCourses(courses);
            break;
        case 3:
            cout << "Enter course number: ";
            cin >> courseNumber;
            transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
            findCourse(courses, courseNumber);
            break;
        case 9:
            cout << "Goodbye!" << endl;
            result = false;
            break;
        default:
            cout << "Invalid Option!" << endl;
            break;
    }
    return result;
}

/**
 * Main entry point of the program.
 * 
 * @return Exit status of the program.
 */
int main() {
    bool keepRunning = true;
    unordered_map<string, Course> courses;
    while (keepRunning) {
        printMenu();
        keepRunning = handleUserInput(courses);
    }
}
