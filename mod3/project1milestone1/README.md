Create pseudocode to load data into the vector data structure and then use it to store and print that data. There is no programming work in this milestone. You will develop pseudocode to help you carry out your design in Project One.

Note: Throughout this milestone, we will use the word course to refer to the courses in the curriculum instead of class. Class has another meaning in object-oriented programming. Specifically, you must address the following rubric criteria:

Design pseudocode to define how the program opens the file, reads the data from the file, parses each line, and checks for file format errors. The Course Information document linked in the Supporting Materials section contains all the information about how the courses required in the Computer Science curriculum for ABCU will be stored in the data file. Each line will consist of information about a single course including the course number, title, and prerequisites. The Course Information document includes the course data and a diagram of how the program will execute.

Your pseudocode must validate the sample file to make certain it is formatted correctly and check for the following items:

- There are at least two parameters on each line. Some courses may not have any prerequisites.

- Any prerequisite that is provided on a line exists as a course in the file. In other words, any prerequisite at the end of a line must have another line in the file that starts with that course number.


Design pseudocode to show how to create course objects and store them in the appropriate data structure. Your pseudocode should show how to create course objects so that one course object holds data from a single line from the input file. Knowing the file format will help you parse and store each token of data in the appropriate course object instance variable. You should store each course object in the vector data structure. Once the entire file has been processed, the vector data structure will have multiple course objects, one per line in the file. Hint: You will need a loop to process all lines from the file and a struct to hold all the data from a single course.

Design pseudocode that will search the data structure for a specific course and print out course information and prerequisites. The advisors from ABCU want to be able to print out the course information and prerequisites from the data stored in the data structure for a given course. Pseudocode for printing course information using a vector data structure is provided as an example in the Pseudocode Document linked in the Supporting Materials section.

Example Pseudocode:

```
// Vector - Milestone 1
void searchCourse(Vector<Course> courses, String courseNumber) {
    for all courses
        if the course is the same as courseNumber
            print out the course information
            for each prerequisite of the course
                print the prerequisite course information
}
//Hash Table - Milestone 2

void searchCourse(HashTable<Course> courses, String courseNumber) {

}
```