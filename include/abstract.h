#ifndef abstract_H
#define abstract_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>p
#include <tuple>
#include <chrono>
#include <ctime>
#include <thread>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <string>
#include <limits>
#include <cctype>
#include <windows.h>
#include <filesystem>


using namespace std;


// Function Declarations (Global)

void print_withdelay(string text);
void print_introduction();

string trim(const string &str);
string getPasswordInput();
int mainMenu(int choice);
bool log_in(string user_name, string user_password);
void forgotPassword();
void logout(const string& role);

// ============================
// ADMIN CLASS
// ============================
class admin {
public:
    int adminMenu(int choice);
    int manageTeachersMenu(int choice);
    int manageStudentsMenu(int choice);
    void viewAllTeachers();
    void searchTeacher();
    void updateTeacher();
    void deleteTeacher();
    void restoreArchivedTeacher();
    void viewAllStudents();
    void searchStudents();
    void updateStudents();
    void deleteStudent();
    void restoreArchivedStudent();
    void assignTeacherToStudent();
};

// ============================
// TEACHER CLASS
// ============================
class teacher {
public:
    string id;
    string first_name;
    string last_name;
    string username;
    string password;
    string major;
    string deadline; // Deadline for assessments

    // Function declarations
    void addNewTeacher();
    void saveTeacherToFile();
    int teacherMenu(int choice);
    void changeCredentials();
    void manageAssessments();
    void manageStudents();
    void createAssessment();
    void viewAssessments();
    void viewQuestions();
    void editAssessment();
    void deleteAssessment();
    void openAssessmentForStudent();
    void reopenAssessment();
    void viewStudentResults();
    void viewAssignedStudents();

    // Deadline management
    void setDeadline();
    void viewDeadline();
    void editDeadline();
};

// ============================
// STUDENT CLASS
// ============================
class student {
public:
    string id;
    string first_name;
    string last_name;
    string userName;
    string course;
    string section;
    string password;

    // Function declarations
    void addNewStudent();
    void saveStudentToFile();
    int studentMenu(int choice);
    void changeCredentials();
    void takeAssessmentMenu();
    void viewResultsAssessmentMenu();
    void startAssessment();
    void viewLatestResult();
    void reviewPreviousAssessments();
    void viewAvailableAssessments();
};

#endif // abstract_H
