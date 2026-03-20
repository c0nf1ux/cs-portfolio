#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

// Course structure to hold course information
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;

    Course() {}

    Course(string number, string name) {
        courseNumber = number;
        courseName = name;
    }
};

// Global data structure to store courses using a map for O(log n) lookup
map<string, Course> courseMap;

/**
 * Split a string by delimiter
 */
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        // Remove whitespace and carriage returns
        token.erase(remove(token.begin(), token.end(), '\r'), token.end());
        token.erase(remove(token.begin(), token.end(), '\n'), token.end());
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

/**
 * Convert string to uppercase for case-insensitive comparison
 */
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

/**
 * Load course data from file into the data structure
 */
void loadDataStructure() {
    string filename;
    cout << "Enter the filename containing course data: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    int coursesLoaded = 0;

    // Clear existing data
    courseMap.clear();

    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> tokens = split(line, ',');

        if (tokens.size() < 2) {
            cout << "Error: Invalid line format in file" << endl;
            continue;
        }

        // Create course object
        Course course;
        course.courseNumber = tokens[0];
        course.courseName = tokens[1];

        // Add prerequisites (if any)
        for (size_t i = 2; i < tokens.size(); i++) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        // Store in map with uppercase key for case-insensitive lookup
        courseMap[toUpper(course.courseNumber)] = course;
        coursesLoaded++;
    }

    file.close();
    cout << "Data loaded successfully. " << coursesLoaded << " courses loaded." << endl;
}

/**
 * Print all courses in alphanumeric order
 */
void printCourseList() {
    if (courseMap.empty()) {
        cout << "No data loaded. Please load data first." << endl;
        return;
    }

    cout << "Here is a sample schedule:" << endl;

    // Map automatically sorts by key, so we can iterate in order
    for (const auto& pair : courseMap) {
        const Course& course = pair.second;
        cout << course.courseNumber << ", " << course.courseName << endl;
    }
}

/**
 * Print information for a specific course
 */
void printCourse() {
    if (courseMap.empty()) {
        cout << "No data loaded. Please load data first." << endl;
        return;
    }

    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    // Convert to uppercase for case-insensitive lookup
    string upperCourseNumber = toUpper(courseNumber);

    auto it = courseMap.find(upperCourseNumber);
    if (it != courseMap.end()) {
        const Course& course = it->second;
        cout << course.courseNumber << ", " << course.courseName << endl;

        if (!course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); i++) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
    else {
        cout << "Course " << courseNumber << " not found." << endl;
    }
}

/**
 * Display the main menu
 */
void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

/**
 * Main function
 */
int main() {
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadDataStructure();
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            printCourse();
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }

        cout << endl;
    }

    return 0;
}