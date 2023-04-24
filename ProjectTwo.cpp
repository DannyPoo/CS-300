// ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Loads the course data from a given filename into a 2D vector.
 * Each course is represented as a vector of strings, where the first
 * string is the course code, the second string is the course name,
 * and subsequent strings (if any) are the course prerequisites.
 *
 * @param filename The name of the file to load.
 * @return A 2D vector containing the course data.
 */
vector<vector<string>> loadCourses(const string& filename) {
    vector<vector<string>> courses;

    ifstream infile(filename);

    if (!infile) {
        cerr << "Unable to open file\n";
        exit(1);
    }

    string line;
    while (getline(infile, line)) {
        vector<string> course;
        istringstream iss(line);
        string token;
        while (getline(iss, token, ',')) {
            course.push_back(token);
        }
        courses.push_back(course);
    }
    infile.close();

    return courses;
}


/**
 * Prints the list of courses in the 2D vector.
 *
 * @param courses The 2D vector containing the course data.
 */
void printCourseList(const vector<vector<string>>& courses) {
    cout << "List of courses: \n";
    for (const auto& course : courses) {
        cout << course[0] << ", ";
        for (auto it = course.begin() + 1; it != course.end(); ++ it) {
            cout << *it << " ";
        }
        cout << endl;
    }
}


/**
 * Prints the prerequisites for a given course code.
 *
 * @param courses The 2D vector containing the course data.
 * @param code The course code to search for.
 */
void printCourse(const vector<vector<string>>& courses, const string& code) {
    auto it = find_if(courses.begin(), courses.end(), [&code](const vector<string>& course) {
        return course[0] == code;
        });
    if (it != courses.end()) {
        if (it->size() > 2) {
            cout << "Prerequisites for " << (*it)[0] << " " << (*it)[1] << ":\n";
            for_each(it->begin() + 2, it->end(), [](const string& prereq) {
                cout << prereq << endl;
                });
        }
        else {
            cout << (*it)[0] << " " << (*it)[1] << " has no prerequisites\n";
        }
    }
    else {
        cout << "Course not found\n";
    }
}

/*
* Main function that runs the course planner program.
* 
* Allows the user to load course data fromt a file, print the list courses, and check prerequisites for each course.
*/
int main()
{
    vector<vector<string>> courses;

    int choice = 0;
    while (choice != 4) {
        cout << "Welcome to the course planner." << endl;
        cout << " 1. Load Data Strucutre." << endl;
        cout << " 2. Print Course List." << endl;
        cout << " 3. Print Course." << endl;
        cout << " 4. Exit" << endl;

        do {
            cout << "What would you like to do? ";
            cin >> choice;
            if (choice < 1 || choice > 4) {
                cout << "Invalid choice. Please enter a nubmer between 1 and 4." << endl;
            }
        } while (choice < 1 || choice > 4);
        
        switch (choice) {
        case 1:
            courses = loadCourses("courses.txt");
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            string code;
            cout << "Please input a course number to lookup!" << endl;
            cin >> code;
            printCourse(courses, code);
            break;
        }
    }
    cout << "Good bye." << endl;
    return 0;
}
