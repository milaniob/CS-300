//============================================================================
// Name        : CS300_Project2_OM.cpp
// Author      :  Oliver Milani
// Version     : 1.0
// Description : Code that will search, sort, and print a text document with course information.
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Definition of structure course

struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};
    bool structOpen = false; //Boolean to let system know if a data structure has been opened. 

// Function that will split each string to a list of strings to be organized 
vector<string> tokenize(string s, string del = " ")
{
    vector<string> stringArray;
    int start = 0;
    int end = s.find(del);

    while (end != -1) {
        stringArray.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    stringArray.push_back(s.substr(start, end - start));

    return stringArray;

}

// Function that loads file and then will store the lines to be the course list

vector<Course> LoadDataStructure()
{
    // Creating an object of iftsream class to open file
    ifstream fin("CourseInformation.txt", ios::in);
    vector<Course> courses;
    string line;

    while (1)
    {
        
        getline(fin, line);
        // if end of file is reached then break the loop
        if (line == "-1")
            break;
        Course course;
     
        vector<string> tokenizedInformation = tokenize(line, ",");

        // Storing information on the structure course

        course.courseNumber = tokenizedInformation[0];
        course.name = tokenizedInformation[1];

        // gets prerequisites and stores them

        for (int i = 2; i < tokenizedInformation.size(); i++)
        {
            course.prerequisites.push_back(tokenizedInformation[i]);
        }
      
        courses.push_back(course);
    }

    

    fin.close();
    structOpen = true; 
    // return the list of courses
    return courses;



}

// Function to format the course list and print it out. 

void printCourse(Course course)
{
    string courseNumber = course.courseNumber;
    string name = course.name;
    vector<string> prerequisites = course.prerequisites;

    cout << courseNumber << ", ";
    cout << name << endl;
    cout << "Prerequisites: ";

    for (int i = 0; i < prerequisites.size(); i++)
    {
        
          cout << prerequisites[i] << " ";
    }

    cout << "\n\n";
}

// printing course information of all courses in proper format
void printCourseList(vector<Course> courses)
{
    int n = courses.size();
    // Sort the list using bubble sort
    if (structOpen == true) {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (courses[j].courseNumber > courses[j + 1].courseNumber)
                {
                    swap(courses[j + 1], courses[j]);
                }
            }
        }
        //use printCourse() function to print all courses in a list

        for (int i = 0; i < n; i++)
        {
            printCourse(courses[i]);
        }

    }
    else {
        cout << "No data found, please Load Data Structure.";
    }
}

// search the course for the user entered course number

void searchCourse(vector<Course> courses)
{
    int n = courses.size();
    string courseNumber;
    int f = 0;

    cout << "Enter courseNumber: ";
    cin >> courseNumber;

    for (int i = 0; i < n; i++)
    {
        // if course found then print it
        if (courses[i].courseNumber == courseNumber)
        {
            f = 1;
            printCourse(courses[i]);
            break;
        }
    }

    // if course with given course name not found then print error message
    if (f == 0)
    {
        cout << "Course with given course number not found\n";
    }
}

int main(int argc, char** argv)
{
    vector<Course> courses;
    // Print menu

    cout << "1.Load Data Structure\n";
    cout << "2.Print Course List\n";
    cout << "3.Print Course\n";
    cout << "4.Exit\n";

    int ch;

    do {
        // Prompt user to choose a menu option
        cout << "\nEnter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1: courses = LoadDataStructure(); break;
        case 2: printCourseList(courses); break;
        case 3: searchCourse(courses); break;
        case 4: cout << "Exit\n"; break;
        default: cout << ch << " is not a valid option. \n";

        }

    } while (ch != 4);

    return 0;
}