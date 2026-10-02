#include "include/abstract.h"
namespace fs = std::filesystem;
using namespace std;
void print_withdelay(string text){
    for (int i=0; i < text.size(); i++) {
        cout << text[i];
        //Sleep(1);

    }
}
void print_introduction(){
    system("cls");
   // Sleep(3);
    print_withdelay( "\f\f\f\f\f\f\f\f\f\f\t\t\t\t\n"
          "\t\t\t\t##################################################################################################\n"
          "\t\t\t\t#                                                                                                #\n"
          "\t\t\t\t#     #######   ########           ##      ##      ###    ######  ######## ########  #######     #\n"
          "\t\t\t\t#     ##   ##   ##                ## #    # ##   ##   ## ##          ##    ##        ##    ##    #\n"
          "\t\t\t\t#     ## # ##   #######   *****  ##  ##  ##  ##  #######  ######     ##    ########  #######     #\n"
          "\t\t\t\t#     ##  ###   ##        *****  ##   ####   ##  ##   ##       ##    ##    ##        ##   ##     #\n"
          "\t\t\t\t#     #######   ########         ##    ##    ##  ##   ##  #######    ##    ########  ##    ##    #\n"
          "\t\t\t\t#           ##                                                                                   #\n"
          "\t\t\t\t#                                    Q e  -  M A S T E R                                         #\n"
          "\t\t\t\t#                         Quiz and Exam Management System (C++ Console)                          #\n"
          "\t\t\t\t#                                                                                                #\n"
          "\t\t\t\t##################################################################################################\n\n"
          "\t\t\t\t\t\t\t\t     Get started? [y/n]: ");
}
int mainMenu(int choice){
    string user_name, user_password;


    while (true) {
        system("CLS");
        cout << "\f\f\n"
             << "+================================================================================+\n"
             << "|                               Welcome to Qe-Master                             |\n"
             << "+================================================================================+\n"
             << "  [1] Log in\n"
             << "  [2] Forgot password\n"
             << "  [3] Exit\n"
             << "=================================================================================\n"
             << "  Enter your choice: ";

        // SAFE INPUT HANDLING
        if (!(cin >> choice)) { // if not a number
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            system("CLS");
            cout << "\n\t\t  Please enter a number only (1-3).\n";
            system("pause");
            continue; // go back to main menu
        }

        // Now handle valid numbers
        if (choice == 1) {
            system("CLS");
            log_in(user_name, user_password);
        }
        else if (choice == 2) {
            system("CLS");
            forgotPassword();
        }
        else if (choice == 3) {
            int exitChoice;
            while (true) {
            system("CLS");
            cout << "\f\f\n"
             << "================================================================================\n"
             << "                           Are you sure you want to exit?          \n"
             << "================================================================================\n"
             << "  [1]Yes\n"
             << "  [2]No\n"
             << "================================================================================\n"
             << "  Enter your choice: ";

                if (!(cin >> exitChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("CLS");
                    cout << "Please enter a valid number.\n";
                    system("pause");
                    continue;
                }

                if (exitChoice == 1) {
                    system("CLS");
                    cout << "\nExiting the program...\n";
                    exit(0);
                }
                else if (exitChoice == 2) {
                    break; // back to main menu
                }
                else {
                    system("CLS");
                    cout << "\nPlease enter a valid number (1 or 2).\n";
                    system("pause");
                    continue;
                }
            }
        }
        else {
            system("CLS");
            cout << "\nPlease enter a valid number (1–3).\n";
            system("pause");
            continue;
        }
    }
}
string getPasswordInput(){
    string password;
    char ch;
    while ((ch = _getch()) != '\r') { // stop on Enter key
        if (ch == '\b' && !password.empty()) { // handle backspace
            cout << "\b \b";
            password.pop_back();
        } else if (isprint(ch)) { // printable character
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}
bool log_in(string user_name, string user_password){
    admin adminObj;
    string line;

    cout << "\f\f\n"
         << "+==============================================================================+\n"
         << "|                                   LOG IN                                     |\n"
         << "+==============================================================================+\n"
         << "Enter your ID or Username/Email(0 to CANCEL): ";
    cin >> user_name;

    if (user_name == "0"){ system("cls"); mainMenu(0);}
    cout << "Enter your Password: ";
    user_password = getPasswordInput();

    // lowercase only username for flexible match (optional)
    string userLower = user_name;
    transform(userLower.begin(), userLower.end(), userLower.begin(), ::tolower);

    // ================= ADMIN LOGIN =================
    //  password remains case-sensitive
    if (userLower == "admin" && user_password == "admin123") {
        cout << "\n***Admin Login Successful!***\n";
        system("pause");
        system("CLS");
        adminObj.adminMenu(0);
        return true;
    }

    // ================= TEACHER LOGIN =================
    ifstream teacherFile("teachers.txt");
    if (teacherFile) {
        while (getline(teacherFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string id, first_name, last_name, username, password, subject;
            getline(ss, id, ',');
            getline(ss, first_name, ',');
            getline(ss, last_name, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, subject, ',');

            // lowercase username only
            string idLower = id;
            string usernameLower = username;
            transform(idLower.begin(), idLower.end(), idLower.begin(), ::tolower);
            transform(usernameLower.begin(), usernameLower.end(), usernameLower.begin(), ::tolower);

            // no lowercase transform for password
            if ((userLower == idLower || userLower == usernameLower) && user_password == password) {
                cout << "\nTeacher Login Successful! Welcome, " << first_name << "!\n";
                system("pause");
                system("CLS");

                teacher t;
                t.id = id;
                t.first_name = first_name;
                t.last_name = last_name;
                t.username = username;
                t.password = password;
                t.teacherMenu(0);
                return true;
            }
        }
        teacherFile.close();
    }

    // ================= STUDENT LOGIN =================
    ifstream studentFile("students.txt");
    if (studentFile) {
        while (getline(studentFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string id,first_name, last_name, userName, course, section, password;
            getline(ss, id, ',');
            getline(ss, first_name, ',');
            getline(ss, last_name, ',');
            getline(ss, userName, ',');
            getline(ss, course, ',');
            getline(ss, section, ',');
            getline(ss, password, ',');

            // lowercase username only
            string idLower = id;
            string userNameLower = userName;
            transform(idLower.begin(), idLower.end(), idLower.begin(), ::tolower);
            transform(userNameLower.begin(), userNameLower.end(), userNameLower.begin(), ::tolower);

            // password is compared exactly (case-sensitive)
            if ((userLower == idLower || userLower == userNameLower) && user_password == password) {
                cout << "\nStudent Login Successful! Welcome, " << first_name << "!\n";
                system("pause");
                system("CLS");

                student s;
                s.id = id;
                s.first_name = first_name;
                s.last_name = last_name;
                s.userName = userName;
                s.password = password;
                s.studentMenu(0);
                return true;
            }
        }
        studentFile.close();
    }

    // ================= INVALID LOGIN =================
    cout << "\nInvalid ID/Username or Password.\n";
    system("pause");
    system("CLS");
    return false;
}
void forgotPassword(){
    system("CLS");
    string input, newPassword;
    bool found = false;

    cout << "\f\f\n"
         << "+==============================================================================+\n"
         << "|                               FORGOT PASSWORD                                |\n"
         << "+==============================================================================+\n";

    cin.ignore();
    cout << "Enter your ID or Email/Username (0 to cancel): ";
    getline(cin, input);
    if(input == "0"){system("cls"); mainMenu(0);}
    if (input.empty()) {
        cout << "\nInput cannot be empty.\n";
        system("pause");
        return;
    }

    // lowercase version for case-insensitive comparison
    string lowerInput = input;
    transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    // Generate random OTP
    srand(time(0));
    int otp = rand() % 900000 + 100000;
    cout << "\f\f\f\n"
         << "+==============================================================================+\n"
         << "|                                     OTP                                      |\n"
         << "+==============================================================================+\n"
         << "  Your verification code is: " << otp << "\n"
         << "================================================================================\n";

    int userOTP;
    cout << "  Enter the verification code: ";
    cin >> userOTP;

    if (userOTP != otp) {
        cout << "================================================================================\n"
             << "Invalid verification code!\n";
        system("pause");
        return;
    }

    cin.ignore();

    // --- Check Teachers ---
    fstream teacherFile("teachers.txt");
    if (!teacherFile) {
        cerr << "Error opening teachers.txt!\n";
        return;
    }

    stringstream updatedTeachers;
    string line;
    found = false;

    while (getline(teacherFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, first_name, last_name,username, password, major;

        getline(ss, id, ',');
        getline(ss, first_name, ',');
        getline(ss, last_name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, major, ',');

        string lowerID = id, lowerUser = username;
        transform(lowerID.begin(), lowerID.end(), lowerID.begin(), ::tolower);
        transform(lowerUser.begin(), lowerUser.end(), lowerUser.begin(), ::tolower);

        if (lowerInput == lowerID || lowerInput == lowerUser) {
            found = true;
            cout << "\nAccount found for Teacher: " << first_name << endl
                 << "Enter new password: ";
            getline(cin, newPassword);
            password = newPassword;
            line = id + "," + first_name + ","+ last_name+"," + username + "," + password + "," + major;
        }

        updatedTeachers << line << "\n";
    }
    teacherFile.close();

    if (found) {
        ofstream outFile("teachers.txt", ios::trunc);
        outFile << updatedTeachers.str();
        outFile.close();
        cout << "\n***Password updated successfully for Teacher!***\n";
        system("pause");
        return;
    }

    // --- Check Students ---
    fstream studentFile("students.txt");
    if (!studentFile) {
        cerr << "Error opening students.txt!\n";
        return;
    }

    stringstream updatedStudents;
    found = false;

    while (getline(studentFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, first_name,last_name, userName, course, section, password;

        getline(ss, id, ',');
        getline(ss, first_name, ',');
        getline(ss, last_name, ',');
        getline(ss, userName, ',');
        getline(ss, course, ',');
        getline(ss, section, ',');
        getline(ss, password, ',');

        string lowerID = id, lowerUser = userName;
        transform(lowerID.begin(), lowerID.end(), lowerID.begin(), ::tolower);
        transform(lowerUser.begin(), lowerUser.end(), lowerUser.begin(), ::tolower);

        if (lowerInput == lowerID || lowerInput == lowerUser) {
            found = true;
            cout << "\nAccount found for Student: " << first_name << endl
                 << "Enter new password: ";
            getline(cin, newPassword);
            password = newPassword;
            line = id + "," + first_name + "," + last_name + "," + userName + "," + course + "," + section + "," + password;
        }

        updatedStudents << line << "\n";
    }
    studentFile.close();

    if (found) {
        ofstream outFile("students.txt", ios::trunc);
        outFile << updatedStudents.str();
        outFile.close();
        cout << "\n***Password updated successfully for Student!***\n";
    } else {
        cout << "\nNo account found with that ID or Email/Username.\n";
    }

    system("pause");
}
void logout(const string& role){
    system("CLS");
    char confirm;

    cout << "\n================================================================================\n"
         << "                          " << role << " Logout\n"
         << "================================================================================\n"
         << "  Are you sure you want to logout? (Y/N): ";
         cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        cout << "\n  Logging out...";
        system("pause");
        system("CLS");
        mainMenu(0);
        return;
    }

    system("CLS");
    cout << "\nLogout cancelled. Returning to " << role << " Menu...\n";
    system("pause");
    system("CLS");

    if (role == "Admin") {
        admin a;
        a.adminMenu(0);
    } else if (role == "Teacher") {
        teacher t;
        t.teacherMenu(0);
    } else if (role == "Student") {
        student s;
        s.studentMenu(0);
    } else {
        mainMenu(0);
    }
}
int admin::adminMenu(int choice){
    system("CLS");
    while(true){
        cout << "\f\f\n"
         << "+==============================================================================+\n"
         << "|                                ADMIN DASHBOARDS                              |\n"
         << "+==============================================================================+\n"
             << "  [1]Manage Teachers.\n"
             << "  [2]Manage Students.\n"
             << "  [3]Logout.\n"
             << "================================================================================\n"
             << "  Enter your choice: ";

             if (!(cin >> choice)) {
                 cin.clear();
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 system("CLS");
                 cout << "\f  Please enter a valid number.\n";
                 system("pause");
                 system("CLS");
                 continue;
             }

             if (choice == 1){
                 manageTeachersMenu(choice);
             }
             else if(choice == 2){
                 manageStudentsMenu(choice);
             }
             else if(choice == 3){
                ::logout("Admin");
             }
             else{
                system("CLS");
                cout << "\f\f  Please enter a valid number (1-3).\n";
                system("pause");
                system("CLS");
                continue;
             }
    }
}
int admin::manageTeachersMenu(int choice){
    admin admin;

    while (true) {
        system("CLS");
        cout << "\f\f\n"
         << "+==============================================================================+\n"
         << "|                                 MANAGE TEACHERS                              |\n"
         << "+==============================================================================+\n"
             << "  [1] Add New Teacher\n"
             << "  [2] View All Teachers\n"
             << "  [3] Search Teacher by ID/Name/Username\n"
             << "  [4] Update Teacher Information\n"
             << "  [5] Delete (Archive) Teacher\n"
             << "  [6] Restore Archived Teacher\n"
             << "  [7] Assign Teacher to Student\n"
             << "  [8] Back to Admin Menu\n"
             << "================================================================================\n"
             << "  Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("CLS");
            cout << "\nPlease enter a valid number.\n";
            system("pause");
            system("CLS");
            continue;
        }

        switch (choice) {
            case 1: {
                teacher t;
                t.addNewTeacher();
                break;
            }
            case 2:
                admin.viewAllTeachers();
                break;
            case 3:
                admin.searchTeacher();
                break;
            case 4:
                admin.updateTeacher();
                break;
            case 5:
                admin.deleteTeacher();
                break;
            case 6:
                admin.restoreArchivedTeacher();
                break;
            case 7:
                admin.assignTeacherToStudent();
                break;
            case 8:
                return adminMenu(choice);
            default:
                system("CLS");
                cout << "\nPlease enter a valid number (1-8).\n";
                system("pause");
                system("CLS");
                break;
        }
    }
}
void teacher::addNewTeacher(){
    system("CLS");
    srand(time(0));

    cout << "\f\f\n"
         << "+==============================================================================+\n"
         << "|                             ADD NEW TEACHERS                                 |\n"
         << "+==============================================================================+\n"
         << "*Teacher Info*\n\n";

    // Load existing IDs and usernames
    vector<string> existingIDs;
    vector<string> existingUsernames;

    ifstream file("teachers.txt");
    if (file) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string existingID, existingFirstName, existingLastName, existingUsername, existingPassword, existingMajor;
            getline(ss, existingID, ',');
            getline(ss, existingFirstName, ',');
            getline(ss, existingLastName, ',');
            getline(ss, existingUsername, ',');
            getline(ss, existingPassword, ',');
            getline(ss, existingMajor, ',');

            existingIDs.push_back(existingID);

            transform(existingUsername.begin(), existingUsername.end(), existingUsername.begin(), ::tolower);
            existingUsernames.push_back(existingUsername);
        }
        file.close();
    }

    // Generate unique Employee ID: EMP-####
    bool uniqueID = false;
    do {
        int randomNum = rand() % 9000 + 1000; // 1000–9999
        id = "EMP-" + to_string(randomNum);
        uniqueID = find(existingIDs.begin(), existingIDs.end(), id) == existingIDs.end();
    } while (!uniqueID);

    cout << "Generated Employee ID: " << id << endl;

    cin.ignore();
    cout << "\nEnter Last Name(0 to cancel): ";
    getline(cin, last_name);

    if(last_name == "0"){ system("cls"); return;}

    cout << "Enter First Name: ";
    getline(cin, first_name);

    // Ask for a unique username
    while (true) {
        cout << "Enter Username: ";
        getline(cin, username);

        string lowerUsername = username;
        transform(lowerUsername.begin(), lowerUsername.end(), lowerUsername.begin(), ::tolower);

        if (username.empty()) {
            cout << "\nUsername cannot be empty.\n";
        } else if (find(existingUsernames.begin(), existingUsernames.end(), lowerUsername) != existingUsernames.end()) {
            cout << "\nUsername already exists. Please enter a different username.\n";
        } else {
            break;
        }
    }

    // Default password = last name in ALL CAPS
    string lastNameUpper = last_name;
    transform(lastNameUpper.begin(), lastNameUpper.end(), lastNameUpper.begin(), ::toupper);
    password = lastNameUpper;

    cout << "Default Password (Last Name in ALL CAPS): " << password << "\n"
         << "Enter The Major: ";
    getline(cin, major);

    // Save teacher to file
    saveTeacherToFile();

    // Create teacher folder structure
    string teacherFolder = "teachers/" + id;
    string questionFolder = teacherFolder + "/questions";
    try {
        fs::create_directories(questionFolder); // creates all needed subfolders
        // Save basic profile info in their folder
        ofstream profile(teacherFolder + "/profile.txt");
        profile << "  ID: " << id << "\n"
                << "  Full name: " << first_name << " " << last_name<<"\n"
                << "  Username: " << username << "\n"
                << "  Major: " << major << "\n";
        profile.close();
    } catch (const std::exception& e) {
        cerr << "Error creating teacher folder: " << e.what() << endl;
    }

    cout << "\nTeacher folder created: " << teacherFolder << endl
         << "================================================================================\n"
         << "\n***Teacher added successfully!***\n";
    system("pause");
    system("CLS");
}
void teacher::saveTeacherToFile(){
    ofstream file("teachers.txt", ios::app);
    if (file.is_open()) {
        file << id << "," << last_name << "," << first_name << "," << username << "," << password << "," << major << "\n";
        file.close();

        // Create a folder for this teacher using their ID or username
        string folderName = "teachers_data/" + id;

        try {
            if (!fs::exists("teachers_data")) {
                fs::create_directory("teachers_data");
            }
            if (!fs::exists(folderName)) {
                fs::create_directory(folderName);
                cout << " Created folder for teacher: " << folderName << endl;
            }
        } catch (const fs::filesystem_error& e) {
            cerr << " Error creating folder: " << e.what() << endl;
        }
    } else {
        cout << " Error: Could not open teachers.txt for writing.\n";
    }
}
void admin::viewAllTeachers(){
    system("CLS");
    ifstream file("teachers.txt");
    if (!file) {
        cerr << "Error opening teachers.txt!\n";
        system("pause");
        return;
    }

    struct Teacher {
        string id, last_name, first_name, username, password, subject;
    };

    vector<Teacher> teachers;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Teacher t;
        getline(ss, t.id, ',');
        getline(ss, t.last_name, ',');
        getline(ss, t.first_name, ',');
        getline(ss, t.username, ',');
        getline(ss, t.password, ',');
        getline(ss, t.subject, ',');

        if (!t.id.empty() && !t.last_name.empty())
            teachers.push_back(t);
    }

    file.close();

    // 🔹 Sort alphabetically by last name (case-insensitive)
    sort(teachers.begin(), teachers.end(), [](const Teacher &a, const Teacher &b) {
        string lnameA = a.last_name, lnameB = b.last_name;
        transform(lnameA.begin(), lnameA.end(), lnameA.begin(), ::tolower);
        transform(lnameB.begin(), lnameB.end(), lnameB.begin(), ::tolower);
        return lnameA < lnameB;
    });

    cout << "\f\f\n"
         << "\n\n"
         << "+==============================================================================+\n"
         << "|                                LIST OF TEACHERS                              |\n"
         << "+==============================================================================+\n\n";


    cout << setw(12) << left << "ID"
         << setw(25) << left << "Full Name"
         << setw(20) << left << "Username"
         << setw(25) << left << "Major"
         << endl
         << string(80, '-') << endl;

    if (teachers.empty()) {
        cout << "\nNo teacher records found.\n";
    } else {
        for (const auto &t : teachers) {
            string fullname = t.last_name + ", " + t.first_name;
            cout << setw(12) << left << t.id
                 << setw(25) << left << fullname
                 << setw(20) << left << t.username
                 << setw(25) << left << t.subject
                 << endl;
        }
    }

    cout << "\n";
    system("pause");
    system("CLS");
}
void admin::searchTeacher(){
    system("CLS");
    ifstream file("teachers.txt");

    if (!file) {
        cerr << "Error opening teachers.txt!\n";
        system("pause");
        return;
    }

        cout << "\n\n"
             << "+==============================================================================+\n"
             << "|                                 SEARCH TEACHER                               |\n"
             << "+==============================================================================+\n"
             << "  Enter ID, Name, Username to search (0 to Cancel): ";
    cin.ignore();
    string query;
    getline(cin, query);

    if (query == "0"){ system("cls"); return;}

    transform(query.begin(), query.end(), query.begin(), ::tolower);

    bool found = false;
    string line;
    cout << "\nSearch Results:\n\n";
    cout << setw(12) << left << "ID"
         << setw(25) << left << "Full Name"
         << setw(20) << left << "Username"
         << setw(25) << left << "Subject" << endl
         << string(80, '  -') << endl;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, first_name, last_name, username, password, major;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, major, ',');

        string idLow = id, nameFLow = first_name,nameLLow = last_name, usernameLow = username;
        transform(idLow.begin(), idLow.end(), idLow.begin(), ::tolower);
        transform(nameFLow.begin(), nameFLow.end(), nameFLow.begin(), ::tolower);
        transform(nameLLow.begin(), nameLLow.end(), nameLLow.begin(), ::tolower);
        transform(usernameLow.begin(), usernameLow.end(), usernameLow.begin(), ::tolower);
        string fullname = last_name + ", " + first_name;


        if (idLow.find(query) != string::npos ||
            nameFLow.find(query) != string::npos || nameLLow.find(query) != string::npos ||
            usernameLow.find(query) != string::npos) {
            found = true;
            cout << setw(12) << left << id
                 << setw(25) << left << fullname
                 << setw(20) << left << username
                 << setw(25) << left << major << endl;
        }
    }

    if (!found) cout << "\nNo teacher found matching '" << query << "'.\n";

    cout << "\n";
    system("pause");
    system("CLS");
}
void admin::updateTeacher(){
    while (true) { // loop for multiple updates
        system("CLS");
        cout << "\n\n"
             << "+==============================================================================+\n"
             << "|                            UPDATE TEACHER INFO                               |\n"
             << "+==============================================================================+\n"
             << "  Enter Employee_ID or Full-Name to update(0 to cancel): ";

        string searchKey;
        cin.ignore();
        getline(cin, searchKey);

        if (searchKey == "0"){ system("cls"); return;}

        string searchLower = searchKey;
        transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        ifstream file("teachers.txt");
        if (!file) {
            cout << "\nError: Unable to open teachers.txt\n";
            system("pause");
            return;
        }

        vector<string> lines;
        vector<int> matchIndexes;
        vector<vector<string>> matchedTeachers;

        string line;
        string id, last_name, first_name, username, password, subject;
        int lineIndex = 0;

        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, last_name, ',');
            getline(ss, first_name, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, subject, ',');

            lines.push_back(line);

            string idLow = id, lastnameLow = last_name, firstnameLow = first_name;
            transform(idLow.begin(), idLow.end(), idLow.begin(), ::tolower);
            transform(lastnameLow.begin(), lastnameLow.end(), lastnameLow.begin(), ::tolower);
            transform(firstnameLow.begin(), firstnameLow.end(), firstnameLow.begin(), ::tolower);

            string fullnameLow = lastnameLow + " " + firstnameLow;

            if (idLow.find(searchLower) != string::npos || fullnameLow.find(searchLower) != string::npos) {
                matchIndexes.push_back(lineIndex);
                string fullname = last_name + ", " + first_name;
                matchedTeachers.push_back({id, fullname, username, password, subject, last_name, first_name});
            }

            lineIndex++;
        }
        file.close();

        if (matchedTeachers.empty()) {
            cout << "\nNo teacher found matching '" << searchKey << "'.\n\n";
            system("pause");
            return;
        }

        cout << "\nFound " << matchedTeachers.size() << " matching record(s):\n\n"
             << setw(5) << left << "No."
             << setw(12) << left << "ID"
             << setw(25) << left << "Full Name"
             << setw(20) << left << "Username"
             << setw(25) << left << "Major" << endl
             << string(90, '-') << endl;

        for (size_t i = 0; i < matchedTeachers.size(); ++i) {
            cout << setw(5) << left << i + 1
                 << setw(12) << left << matchedTeachers[i][0]
                 << setw(25) << left << matchedTeachers[i][1]
                 << setw(20) << left << matchedTeachers[i][2]
                 << setw(25) << left << matchedTeachers[i][4] << endl;
        }

        int choiceIndex;
        cout << "\nEnter the number of the teacher you want to update (0 to cancel): ";
        cin >> choiceIndex;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choiceIndex == 0) {
            system("cls");
            return;
        }

        if (choiceIndex < 1 || choiceIndex > (int)matchedTeachers.size()) {
            cout << "\nInvalid selection.\n";
            system("pause");
            continue;
        }

        id = matchedTeachers[choiceIndex - 1][0]; // fullname for display
        last_name = matchedTeachers[choiceIndex - 1][1];
        username = matchedTeachers[choiceIndex - 1][2];
        password = matchedTeachers[choiceIndex - 1][3];
        subject = matchedTeachers[choiceIndex - 1][4];

        system("CLS");
        cout << "\n\n"
             << "+==============================================================================+\n"
             << "|                            UPDATE TEACHER INFO                               |\n"
             << "+==============================================================================+\n"
             << "\n  Current Record:\n"
             << "--------------------------------------------------------------------------------\n"
             << "  ID: " << id << "\n"
             << "  Name: " << last_name << "\n"
             << "  Username: " << username << "\n"
             << "  Password: " << string(password.length(), '*') << "\n"
             << "  Assigned Subject: " << subject << "\n"
             << "--------------------------------------------------------------------------------\n\n";

        int choice;
        cout << "  Which information do you want to update?\n"
             << "  1. Name\n"
             << "  2. Username\n"
             << "  3. Password\n"
             << "  4. Major\n"
             << "  5. Cancel\n"
             << "--------------------------------------------------------------------------------\n"
             << " Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string newValue, confirm;
        bool confirmSave = false;

        switch (choice) {
            case 1:
                cout << "\nCurrent Name: " << last_name << "\n"
                     << "Enter New Name: ";
                getline(cin, newValue);
                break;

            case 2: {
                cout << "\n  Current Username: " << username << "\n"
                     << "Enter New Username: ";
                getline(cin, newValue);

                //  Check for duplicate username
                bool duplicate = false;
                for (size_t i = 0; i < lines.size(); ++i) {
                    if (i == (size_t)matchIndexes[choiceIndex - 1]) continue; // skip current teacher
                    stringstream ss(lines[i]);
                    string tid, tname, tuser, tpass, tsub;
                    getline(ss, tid, ',');
                    getline(ss, tname, ',');
                    getline(ss, tuser, ',');
                    getline(ss, tpass, ',');
                    getline(ss, tsub, ',');
                    if (tuser == newValue) {
                        duplicate = true;
                        break;
                    }
                }

                if (duplicate) {
                    cout << "\nError: Username '" << newValue << "' already exists! Update cancelled.\n";
                    system("pause");
                    continue; // skip saving and restart loop
                }
                break;
            }

            case 3:
                cout << "\nCurrent Password: " << string(password.length(), '*') << "\n"
                     << "Enter New Password: ";
                getline(cin, newValue);
                break;

            case 4:
                cout << "\nCurrent Subject: " << subject << "\n"
                     << "Enter New Major: ";
                getline(cin, newValue);
                break;

            case 5:
                cout << "\nUpdate cancelled.\n";
                system("pause");
                continue;

            default:
                cout << "\nInvalid choice.\n";
                system("pause");
                continue;
        }

        cout << "Are you sure you want to save changes? (Y/N): ";
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (confirm == "Y" || confirm == "y") {
            switch (choice) {
                case 1: last_name = newValue;break;
                case 2: username = newValue; break;
                case 3: password = newValue; break;
                case 4: subject = newValue; break;
            }
            confirmSave = true;
        } else {
            cout << "\nUpdate cancelled.\n";
        }

        if (confirmSave) {
            cout << "\n*** UPDATE SUCCESSFULLY! ***\n\n"
                 << "Updated Record:\n"
                 << "--------------------------------------------------------------------------------\n"
                 << "ID: " << id << "\n"
                 << "Name: " << last_name << "\n"
                 << "Username: " << username << "\n"
                 << "Password: " << string(password.length(), '*') << "\n"
                 << "Assigned Subject: " << subject << "\n"
                 << "--------------------------------------------------------------------------------\n";

            lines[matchIndexes[choiceIndex - 1]] =
                id + "," + last_name + "," + username + "," + password + "," + subject;

            ofstream out("teachers.txt");
            for (auto &l : lines) out << l << "\n";
            out.close();
        }

        string again;
        cout << "\nDo you want to update another teacher? (Y/N): ";
        cin >> again;
        if (again == "N" || again == "n") {
            system("CLS");
            return;
        }
    }
}
void admin::deleteTeacher(){
    system("CLS");
    ifstream file("teachers.txt");
    if (!file) {
        cerr << "Error: Could not open teachers.txt!\n";
        system("pause");
        return;
    }

    vector<string> records;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) records.push_back(line);
    }
    file.close();

    if (records.empty()) {
        cout << "\nNo teacher records found.\n";
        system("pause");
        return;
    }
        //ARCHIVED TEACHERS
        cout << "\n\n"
             << "+==============================================================================+\n"
             << "|                             ARCHIVED TEACHER                                 |\n"
             << "+==============================================================================+\n"
             << "  Enter Teacher ID, Full Name, or Username(0 to cancel): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string keyword;
    getline(cin, keyword);
    if (keyword == "0"){system("cls"); return;}

    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    vector<pair<int, string>> matches; // index + record
    for (int i = 0; i < (int)records.size(); i++) {
        stringstream ss(records[i]);
        string id, last_name,first_name, username, password, subject;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, subject, ',');

        string idLow = id, nameFLow = last_name, nameLLow = first_name,userLow = username;
        transform(idLow.begin(), idLow.end(), idLow.begin(), ::tolower);
        transform(nameFLow.begin(), nameFLow.end(), nameFLow.begin(), ::tolower);
        transform(nameLLow.begin(), nameLLow.end(), nameLLow.begin(), ::tolower);
        transform(userLow.begin(), userLow.end(), userLow.begin(), ::tolower);

        if (idLow.find(lowerKeyword) != string::npos ||
            nameFLow.find(lowerKeyword) != string::npos || nameLLow.find(lowerKeyword) != string::npos ||
            userLow.find(lowerKeyword) != string::npos) {
            matches.push_back({i, records[i]});
        }
    }

    if (matches.empty()) {
        cout << "\nNo teacher found matching that keyword.\n";
        system("pause");
        return;
    }

    cout << "\nMatched Teachers:\n";
    cout << "--------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < matches.size(); i++) {
        stringstream ss(matches[i].second);
        string id, last_name, first_name,username, password, major;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, major, ',');

        cout << "[" << i + 1 << "] " << last_name <<" "<< first_name<< " (" << id << ") | Username: " << username
             << " | Major: " << major << "\n";
    }
    cout << "--------------------------------------------------------------------------------\n";

    int choice;
    if (matches.size() > 1) {
        cout << "\nEnter number of the teacher to archive (0 to cancel): ";
        cin >> choice;
        if (choice == 0 || choice > (int)matches.size()) {
            cout << "\nOperation cancelled.\n";
            system("pause");
            return;
        }
    } else {
        choice = 1;
    }

    string selectedRecord = matches[choice - 1].second;
    stringstream ss(selectedRecord);
    string id, last_name, first_name, username, password, major;
    getline(ss, id, ',');
    getline(ss, last_name, ',');
    getline(ss, first_name, ',');
    getline(ss, username, ',');
    getline(ss, password, ',');
    getline(ss, major, ',');

    cout << "\n  You selected:\n"
         << "--------------------------------------------------------------------------------\n"
         << " ID: " << id << "\n"
         << " Name: " << first_name<< " " << last_name << "\n"
         << " Username: " << username << "\n"
         << " Major: " << major << "\n"
         << "--------------------------------------------------------------------------------\n";

    cout << "Are you sure you want to archive this teacher? (Y/N): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        ofstream archive("archived_teachers.txt", ios::app);
        if (archive) {
            archive << selectedRecord << "\n";
            archive.close();
            cout << "\nTeacher " << first_name <<" "<< last_name << " successfully archived!\n";
        } else {
            cerr << "\nError: Could not open archived_teachers.txt!\n";
        }

        // remove from original list
        records.erase(records.begin() + matches[choice - 1].first);
        ofstream out("teachers.txt", ios::trunc);
        for (auto &r : records) out << r << "\n";
        out.close();
    } else {
        cout << "\nArchiving cancelled.\n";
    }

    system("pause");
    system("CLS");
}
void admin::restoreArchivedTeacher() {
    system("CLS");

    ifstream file("archived_teachers.txt");
    if (!file) {
        cerr << "No archived teacher records found.\n";
        system("pause");
        return;
    }

    vector<string> archived;
    string line;

        cout << "\n\n"
             << "+==============================================================================+\n"
             << "|                             ARCHIVED TEACHER                                 |\n"
             << "+==============================================================================+\n";


    bool hasRecords = false;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, last_name, first_name, username, password, major;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, major, ',');

        archived.push_back(line);

        cout << "  ID: " << id << "\n"
             << "  Name: " << last_name << "\n"
             << "  Username: " << username << "\n"
             << "  Major: " << major << "\n"
             << "--------------------------------------------------------------------------------\n";

        hasRecords = true;
    }
    file.close();

    if (!hasRecords) {
        cout << "No archived teachers found.\n";
        system("pause");
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string search;
    cout << "\nEnter Teacher ID, Name, Username to restore(0 to Cancel): ";
    getline(cin, search);
    search = trim(search);

    if (search == "0"){system("cls"); return;}

    if (search.empty()) {
        cout << "\nInput cannot be empty.\n";
        system("pause");
        return;
    }

    string lowerSearch = search;
    transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);

    bool restored = false;
    vector<string> remaining;
    string restoredRecord;
    string restoredName;
    string restoredUsername;
    string restoredID;

    // find the record
    for (const auto &record : archived) {
        stringstream ss(record);
        string id, name, username, password, major;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, major, ',');

        string lowerName = name, lowerUser = username;
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        transform(lowerUser.begin(), lowerUser.end(), lowerUser.begin(), ::tolower);

        if (id == search || lowerName.find(lowerSearch) != string::npos || lowerUser == lowerSearch) {
            restored = true;
            restoredRecord = record;
            restoredName = name;
            restoredUsername = username;
            restoredID = id;
        } else {
            remaining.push_back(record);
        }
    }

    if (!restored) {
        cout << "\nNo matching teacher found in archive.\n";
        system("pause");
        return;
    }

    //  Confirm restore
    char confirm;
    cout << "\nAre you sure you want to restore '" << restoredName << "'? (Y/N): ";
    cin >> confirm;
    confirm = toupper(confirm);
    if (confirm != 'Y') {
        cout << "\nRestore canceled.\n";
        system("pause");
        return;
    }

    // Check for duplicates in teachers.txt
    ifstream mainFileCheck("teachers.txt");
    bool duplicate = false;
    if (mainFileCheck) {
        string mainLine;
        while (getline(mainFileCheck, mainLine)) {
            if (mainLine.empty()) continue;

            stringstream ss(mainLine);
            string id, last_name, first_name, username, password, major;
            getline(ss, id, ',');
            getline(ss, last_name, ',');
            getline(ss, first_name, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, major, ',');

            if (id == restoredID || username == restoredUsername) {
                duplicate = true;
                break;
            }
        }
        mainFileCheck.close();
    }

    if (duplicate) {
        cout << "\nCannot restore: a teacher with the same ID or username already exists in teachers.txt.\n";
        system("pause");
        return;
    }

    //  Rewrite archive without restored record
    ofstream out("archived_teachers.txt", ios::trunc);
    for (const auto &r : remaining) out << r << "\n";
    out.close();

    //  Add restored record to teachers.txt
    ofstream mainFile("teachers.txt", ios::app);
    mainFile << restoredRecord << "\n";
    mainFile.close();

    cout << "\nTeacher '" << restoredName << "' has been successfully restored!\n";
    system("pause");
}
int admin::manageStudentsMenu(int choice){
    admin admin;
    while(true){
        system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                              MANAGE STUDENTS                                 |\n"
             << "+==============================================================================+\n"
             << "  1.Add New Student.\n"
             << "  2.View All Students.\n"
             << "  3.Search Student by ID/Name.\n"
             << "  4.Update Student Information.\n"
             << "  5.Delete Student.\n"
             << "  6.Restore Archived Student\n"
             << "  7.Back to Admin Menu.\n"
             << "+==============================================================================+\n"
             << " Enter your choice: ";

             if (!(cin >> choice)) {
                 cin.clear();
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 system("CLS");
                 cout << "\f\fPlease enter a valid number.\n";
                 system("pause");
                 system("CLS");
                 continue;
             }

             if (choice == 1){
                    student students;
                students.addNewStudent();
             }
             else if(choice == 2){
                admin.viewAllStudents();
             }
             else if(choice == 3){
                admin.searchStudents();
             }
             else if(choice == 4){
                admin.updateStudents();
             }
             else if(choice == 5){
                admin.deleteStudent();
             }
             else if(choice == 6){
                restoreArchivedStudent();
             }
             else if(choice == 7){
                adminMenu(choice);
             }
             else{
                system("CLS");
                cout << "\f\fPlease enter a valid number (1-7).\n";
                system("pause");
                system("CLS");
                continue;
             }
    }
}
void student::addNewStudent(){
    srand(time(0)); // initialize random seed

    //  Load existing IDs from file to ensure uniqueness
    vector<string> existingIDs;
    ifstream idFile("students.txt");
    if (idFile) {
        string line;
        while (getline(idFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string existingID, temp;
            getline(ss, existingID, ',');
            existingID = trim(existingID);
            if (!existingID.empty()) existingIDs.push_back(existingID);
        }
        idFile.close();
    }

    //  Generate a UNIQUE Student ID: 2025-### (500–900)
    bool uniqueID = false;
    while (!uniqueID) {
        int randomNum = rand() % 401 + 500; // range 500–900
        id = "2025-" + to_string(randomNum);

        uniqueID = true;
        for (const string &existing : existingIDs) {
            if (existing == id) {
                uniqueID = false;
                break;
            }
        }
    }

    cin.ignore();
    cout << "Enter Last Name (0 to cancel): ";
    getline(cin, last_name);
    if (last_name == "0"){system("cls"); return;}

    cout << "Enter First Name: ";
    getline(cin, first_name);


    //  Ask for unique username (checked directly from file)
    while (true) {
        cout << "Enter Username: ";
        getline(cin, userName);
        userName = trim(userName);

        if (userName.empty()) {
            cout << "\nUsername cannot be empty.\n\n";
            continue;
        }

        // Convert to lowercase for comparison
        string lowerUsername = userName;
        transform(lowerUsername.begin(), lowerUsername.end(), lowerUsername.begin(), ::tolower);

        bool duplicate = false;
        ifstream checkFile("students.txt");
        if (checkFile) {
            string line;
            while (getline(checkFile, line)) {
                if (line.empty()) continue;

                stringstream ss(line);
                string existingID, existingFirstName, existingLastName,existingUserName, existingCourse, existingSection, existingPassword;

                getline(ss, existingID, ',');
                getline(ss, existingFirstName, ',');
                getline(ss, existingLastName, ',');
                getline(ss, existingUserName, ',');
                trim(existingUserName);

                // Convert existing username to lowercase
                transform(existingUserName.begin(), existingUserName.end(), existingUserName.begin(), ::tolower);

                if (existingUserName == lowerUsername) {
                    duplicate = true;
                    break;
                }
            }
            checkFile.close();
        }

        if (duplicate) {
            cout << "\nError: Username already exists in the record. Please enter a different username.\n\n";
        } else {
            break; // valid & unique
        }
    }

    cout << "Enter Course: ";
    getline(cin, course);

    cout << "Enter Section: ";
    getline(cin, section);

    //  Default password = surname in ALL CAPS
    string surnameUpper = last_name;
    transform(surnameUpper.begin(), surnameUpper.end(), surnameUpper.begin(), ::toupper);
    password = surnameUpper;

    //  Save student record
    ofstream outFile("students.txt", ios::app);
    if (outFile) {
        outFile << id << ","
                << last_name << ","
                << first_name << ","
                << userName << ","
                << course << ","
                << section << ","
                << password << "\n";
        outFile.close();
    } else {
        cout << " Error: Could not open students.txt for writing.\n";
        return;
    }

    cout << "\nStudent record saved successfully!\n"
         << "Generated ID: " << id << endl
         << "Username: " << userName << endl
         << "Default Password: " << password << " (Surname in ALL CAPS)\n";
    system("pause");
    system("CLS");
}
string trim(const string &str){  //  Helper: Trim leading/trailing spaces
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}
void student::saveStudentToFile(){
    ofstream file("students.txt", ios::app); // append mode
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    file << id << ","
         << last_name << ","
         << first_name << ","
         << userName << ","
         << course << ","
         << section << ","
         << password << endl;

    file.close();
}
void admin::viewAllStudents(){
    system("CLS");
    ifstream file("students.txt");
    if (!file) {
        cout << "No student records found.\n";
        system("pause");
        return;
    }

    struct Student {
        string id, last_name, first_name, username, course, section, password;
    };

    vector<Student> students;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Student s;
        getline(ss, s.id, ',');
        getline(ss, s.last_name, ',');
        getline(ss, s.first_name, ',');
        getline(ss, s.username, ',');
        getline(ss, s.course, ',');
        getline(ss, s.section, ',');
        getline(ss, s.password, ',');

        if (!s.id.empty() && !s.last_name.empty())
            students.push_back(s);
    }

    file.close();

    // 🔹 Sort alphabetically by last name (case-insensitive)
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        string lnameA = a.last_name, lnameB = b.last_name;
        transform(lnameA.begin(), lnameA.end(), lnameA.begin(), ::tolower);
        transform(lnameB.begin(), lnameB.end(), lnameB.begin(), ::tolower);
        return lnameA < lnameB;
    });
    // LIST OF STUDENTS
    cout << "\f\n\n"
         << "+==============================================================================+\n"
         << "|                              LIST OF STUDENTS                                |\n"
         << "+==============================================================================+\n";

    if (students.empty()) {
        cout << "\n  No students found.\n";
    } else {
        for (const auto &s : students) {
            cout << "\n  Student ID: " << s.id
                 << "\n  Name: " << s.first_name << " " << s.last_name
                 << "\n  Username: " << s.username
                 << "\n  Course: " << s.course
                 << "\n--------------------------------------------------------------------------------\n";
        }
    }

    system("pause");
}
void admin::searchStudents(){
    system("CLS");
    cout << "\f\n\n"
         << "+==============================================================================+\n"
         << "|                              SEARCH STUDENTS                                |\n"
         << "+==============================================================================+\n"
         << " Enter Student ID, Name to search(0 to cancel): ";
    cin.ignore();
    string keyword;
    getline(cin, keyword);
    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    if (keyword == "0"){system("cls"); return;}

    ifstream file("students.txt");
    if (!file) {
        cout << "Unable to open students.txt\n";
        system("pause");
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id,last_name, first_name, username, course, section;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, course, ',');
        getline(ss, section, ',');

        string lowerName = first_name, lowerFirstName = last_name;
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        transform(lowerFirstName.begin(), lowerFirstName.end(), lowerFirstName.begin(), ::tolower);

        if (lowerName.find(lowerKeyword) != string::npos || lowerFirstName.find(lowerKeyword) != string::npos ||id == keyword) {
            cout << "\nStudent Found:\n"
                 << "  ID: " << id << "\n  Full Name: " << first_name << " " << last_name
                 << "\n  Username: " << username
                 << "\n  Course: " << course
                 << "\n  Section: " << section << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "\nNo student found matching that ID or name.\n";

    file.close();
    system("pause");
}
void admin::updateStudents(){
    while (true) {
        system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                              UPDATE STUDENT INFO                             |\n"
             << "+==============================================================================+\n"
             << " Enter Student ID, Full-Name to update (0 to cancel): ";

        string searchKey;
        cin.ignore();
        getline(cin, searchKey);

        if (searchKey == "0"){system("cls"); return;}
        string searchLower = searchKey;
        transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        ifstream file("students.txt");
        if (!file) {
            cout << "\nError: Unable to open students.txt\n";
            system("pause");
            return;
        }

        vector<string> lines;
        vector<int> matchIndexes;
        vector<vector<string>> matchedStudents;

        string line;
        string id, last_name,  first_name, username, course, section, password;
        int lineIndex = 0;

        while (getline(file, line)) {



            if (line.empty()) continue;

            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, last_name, ',');
            getline(ss, first_name, ',');
            getline(ss, username, ',');
            getline(ss, course, ',');
            getline(ss, section, ',');
            getline(ss, password, ',');

            lines.push_back(line);

            string idLow = id, nameLow = last_name , nameFLow = first_name;
            transform(idLow.begin(), idLow.end(), idLow.begin(), ::tolower);
            transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
            transform(nameFLow.begin(), nameFLow.end(), nameFLow.begin(), ::tolower);

            string fullnameLow = nameLow + " " + nameFLow;
            if (idLow.find(searchLower) != string::npos || nameLow.find(searchLower) != string::npos || nameFLow.find(searchLower) != string::npos) {
                matchIndexes.push_back(lineIndex);
                string full_name = last_name + "," + first_name;
                matchedStudents.push_back({id, full_name, username, course, section, password});
            }

            lineIndex++;
        }
        file.close();

        if (matchedStudents.empty()) {
            cout << "\nNo student found matching '" << searchKey << "'.\n";
            system("pause");
            return;
        }

        cout << "\nFound " << matchedStudents.size() << "  matching record(s):\n\n";
        cout << setw(5) << left << "No."
             << setw(12) << left << "ID"
             << setw(30) << left << "  Full Name"
             << setw(20) << left << "  Username"
             << setw(20) << left << "  Course"
             << setw(40) << left << "  Section" << endl
             << string(120, '-') << endl;

        for (size_t i = 0; i < matchedStudents.size(); ++i) {
            cout << setw(5) << left << i + 1
                 << setw(14) << left << matchedStudents[i][0]
                 << setw(32) << left << matchedStudents[i][1]
                 << setw(21) << left << matchedStudents[i][2]
                 << setw(20) << left << matchedStudents[i][3]
                 << setw(30) << left << matchedStudents[i][4] << endl;
        }

        int choiceIndex;
        cout << "\nEnter the number of the student you want to update (0 to cancel): ";
        cin >> choiceIndex;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choiceIndex == 0){system("clls"); return;}

        if (choiceIndex < 1 || choiceIndex > (int)matchedStudents.size()) {
            cout << "\nInvalid selection.\n";
            system("pause");
            continue;
        }
        id = matchedStudents[choiceIndex - 1][0];
        last_name = matchedStudents[choiceIndex - 1][1];
        username = matchedStudents[choiceIndex - 1][2];
        course = matchedStudents[choiceIndex - 1][3];
        section = matchedStudents[choiceIndex - 1][4];
        password = matchedStudents[choiceIndex - 1][5];
        string full_name = first_name + " " + last_name;
        system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                              UPDATE STUDENT INFO                             |\n"
             << "+==============================================================================+\n"
             << "\n  Current Record:\n"
             << "--------------------------------------------------------------------------------\n"
             << "ID: " << id << "\n"
             << "Full Name: " << last_name << "\n"
             << "Username: " << username << "\n"
             << "Course: " << course << "\n"
             << "Section: " << section << "\n"
             << "Password: " << string(password.length(), '*') << "\n"
             << "--------------------------------------------------------------------------------\n";

        int choice;
        cout << "  Which information do you want to update?\n"
             << "  1. Name\n"
             << "  2. Username\n"
             << "  3. Course\n"
             << "  4. Section\n"
             << "  5. Password\n"
             << "  6. Cancel\n"
             << "--------------------------------------------------------------------------------\n"
             << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string newValue, confirm;
        bool confirmSave = false;

        switch (choice) {
            case 1:
                cout << "\nCurrent Name: " << last_name << "\n"
                     << "Enter New  Name (0 to cancel): ";
                getline(cin, newValue);
                if (newValue == "0"){ system("cls"); return;}
                break;

            case 2: {
                cout << "\nCurrent Username: " << username << "\n"
                     << "Enter New Username: ";
                getline(cin, newValue);

                //  Check for duplicate username
                bool duplicate = false;
                for (size_t i = 0; i < lines.size(); ++i) {
                    if (i == (size_t)matchIndexes[choiceIndex - 1]) continue;
                    stringstream ss(lines[i]);
                    string sid, sname, suser, scourse, ssection, spass;
                    getline(ss, sid, ',');
                    getline(ss, sname, ',');
                    getline(ss, suser, ',');
                    if (suser == newValue) {
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate) {
                    cout << "\n  Error: Username '" << newValue << "' already exists! Update cancelled.\n";
                    system("pause");
                    continue;
                }
                break;
            }

            case 3:
                cout << "\nCurrent Course: " << course << "\n"
                     << "Enter New Course: ";
                getline(cin, newValue);
                break;

            case 4:
                cout << "\nCurrent Section: " << section << "\n"
                     << "Enter New Section: ";
                getline(cin, newValue);
                break;

            case 5:
                cout << "\nEnter New Password: ";
                getline(cin, newValue);
                break;

            case 6:
                cout << "\nUpdate cancelled.\n";
                system("pause");
                continue;

            default:
                cout << "\nInvalid choice.\n";
                system("pause");
                continue;
        }

        cout << "Are you sure you want to save changes? (Y/N): ";
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (confirm == "Y" || confirm == "y") {
            switch (choice) {
                case 1: last_name = newValue; break;
                case 2: username = newValue; break;
                case 3: course = newValue; break;
                case 4: section = newValue; break;
                case 5: password = newValue; break;
            }
            confirmSave = true;
        } else {
            cout << "\n  Update cancelled.\n";
        }

        if (confirmSave) {
            cout << "\n*** UPDATE SUCCESSFULLY! ***\n\n"
                 << "  Updated Record:\n"
                 << "--------------------------------------------------------------------------------\n"
                 << "  ID: " << id << "\n"
                 << "  Name: " << last_name << "\n"
                 << "  Username: " << username << "\n"
                 << "  Course: " << course << "\n"
                 << "  Section: " << section << "\n"
                 << "  Password: " << string(password.length(), '*') << "\n"
                 << "--------------------------------------------------------------------------------\n";

            lines[matchIndexes[choiceIndex - 1]] =
                id + "," + last_name + "," +username + "," + course + "," + section + "," + password;

            ofstream out("students.txt");
            for (auto &l : lines) out << l << "\n";
            out.close();
        }

        string again;
        cout << "\nDo you want to update another student? (Y/N): ";
        cin >> again;
        if (again == "N" || again == "n") {
            system("CLS");
            return;
        }
    }
}
void admin::deleteStudent(){
    system("CLS");

    ifstream file("students.txt");
    if (!file) {
        cerr << "Error: Could not open students.txt!\n";
        system("pause");
        return;
    }

    vector<string> records;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) records.push_back(line);
    }
    file.close();

    if (records.empty()) {
        cout << "\n  No student records found.\n";
        system("pause");
        return;
    }

    cout << "\n================================================================================\n"
         << "                                  ARCHIVE STUDENT\n"
         << "================================================================================\n"
         << "Enter Student ID, Full Name, Username or [1] to cancel: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string keyword;
    getline(cin, keyword);

    if(keyword == "1"){system("cls"); return;}

    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    vector<pair<int, string>> matches; // index + record

    for (int i = 0; i < (int)records.size(); i++) {
        stringstream ss(records[i]);
        string id, last_name, first_name, username, course, section, password;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, course, ',');
        getline(ss, section, ',');
        getline(ss, password, ',');

        string idLow = id, nameLow = last_name, nameFLow = first_name, userLow = username;
        transform(idLow.begin(), idLow.end(), idLow.begin(), ::tolower);
        transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
        transform(nameFLow.begin(), nameFLow.end(), nameFLow.begin(), ::tolower);
        transform(userLow.begin(), userLow.end(), userLow.begin(), ::tolower);

        if (idLow.find(lowerKeyword) != string::npos ||
            nameLow.find(lowerKeyword) != string::npos || nameFLow.find(lowerKeyword) != string::npos ||
            userLow.find(lowerKeyword) != string::npos) {
            matches.push_back({i, records[i]});
        }
    }

    if (matches.empty()) {
        cout << "\nNo student found matching that keyword.\n";
        system("pause");
        return;
    }

    cout << "\nMatched Students:\n"
         << "--------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < matches.size(); i++) {
        stringstream ss(matches[i].second);
        string id, last_name, first_name, username, course, section, password;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, course, ',');
        getline(ss, section, ',');
        getline(ss, password, ',');

        cout << "[" << i + 1 << "] " << first_name << " " << last_name<< " (" << id << ") | Username: "
             << username << " | Course: " << course << " | Section: " << section << "\n";
    }
    cout << "--------------------------------------------------------------------------------\n";

    int choice;
    if (matches.size() > 1) {
        cout << "\nEnter number of the student to archive (0 to cancel): ";
        cin >> choice;
        if (choice == 0 || choice > (int)matches.size()) {
            cout << "\n  Operation cancelled.\n";
            system("pause");
            return;
        }
    } else {
        choice = 1;
    }

    string selectedRecord = matches[choice - 1].second;
    stringstream ss(selectedRecord);
    string id, last_name, first_name, username, course, section, password;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, course, ',');
        getline(ss, section, ',');
        getline(ss, password, ',');

    cout << "\nYou selected:\n"
         << "--------------------------------------------------------------------------------\n"
         << "  ID: " << id << "\n"
         << "  Name: " << first_name<< " " << last_name << "\n"
         << "  Username: " << username << "\n"
         << "  Course: " << course << "\n"
         << "  Section: " << section << "\n"
         << "--------------------------------------------------------------------------------\n";

    cout << "Are you sure you want to archive this student? (Y/N): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        ofstream archive("archived_students.txt", ios::app);
        if (archive) {
            archive << selectedRecord << "\n";
            archive.close();
            cout << "\nStudent " << first_name << " " << last_name << " successfully archived!\n";
        } else {
            cerr << "\nError: Could not open archived_students.txt!\n";
        }

        // remove from original list
        records.erase(records.begin() + matches[choice - 1].first);
        ofstream out("students.txt", ios::trunc);
        for (auto &r : records) out << r << "\n";
        out.close();
    } else if (confirm == 'N' || confirm == 'n'){
        cout << "\nArchiving cancelled.\n";
    }
    else {
        cout << "\nInvalid Input.\n";
    }

    system("pause");
    system("CLS");
}
void admin::restoreArchivedStudent(){
    system("CLS");
    ifstream archiveFile("archived_students.txt");

    if (!archiveFile) {
        cout << "No archived student records found.\n";
        system("pause");
        return;
    }

    vector<string> archivedRecords;
    string line;

    cout << "================================================================================\n"
         << "                              Archived Students     \n"
         << "================================================================================\n";

    bool hasRecords = false;
    while (getline(archiveFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, last_name, first_name, username, course, section, password;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, course, ',');
        getline(ss, section, ',');
        getline(ss, password, ',');

        archivedRecords.push_back(line);

        cout << "  ID: " << id << "\n"
             << "  Name: " << first_name << " " << last_name << "\n"
             << "  Username: " << username << "\n"
             << "  Course: " << course << "\n"
             << "  Section: " << section << "\n"
             << "--------------------------------------------------------------------------------\n";

        hasRecords = true;
    }
    archiveFile.close();

    if (!hasRecords) {
        cout << "  No archived students found.\n";
        system("pause");
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string keyword;
    cout << "\nEnter Student ID, Name to restore or [1] to cancel: ";
    getline(cin, keyword);
    keyword = trim(keyword);

    if(keyword == "1"){system("cls"); return;}

    //  Prevent empty input
    if (keyword.empty()) {
        cout << "\nInput cannot be empty.\n";
        system("pause");
        return;
    }

    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    vector<string> updatedArchive;
    string restoredRecord;
    string restoredName;
    bool found = false;

    for (const string &record : archivedRecords) {
        stringstream ss(record);
        string id, last_name, first_name, username, course, section, password;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, course, ',');
        getline(ss, section, ',');
        getline(ss, password, ',');

        string lowerName = last_name;
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

        if (id == keyword || lowerName.find(lowerKeyword) != string::npos) {
            found = true;
            restoredRecord = record;
            restoredName = first_name, last_name;
        } else {
            updatedArchive.push_back(record);
        }
    }

    if (!found) {
        cout << "\nNo archived student found matching that ID or name.\n";
        system("pause");
        return;
    }

    char confirm;
    cout << "\nAre you sure you want to restore '" << restoredName << "'? (Y/N): ";
    cin >> confirm;
    confirm = toupper(confirm);

    if (confirm != 'Y') {
        cout << "\nRestore canceled.\n";
        system("pause");
        return;
    }

    //  Proceed with restoration
    ofstream outArchive("archived_students.txt");
    for (const string &rec : updatedArchive)
        outArchive << rec << "\n";
    outArchive.close();

    ofstream studentsFile("students.txt", ios::app);
    studentsFile << restoredRecord << "\n";
    studentsFile.close();

    cout << "\n Student '" << restoredName << " ' has been successfully restored!\n";
    system("pause");
}
void admin::assignTeacherToStudent(){
    string line;
    while(true){
        system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                     TEACHER-STUDENT ASSIGNMENT MANAGER                       |\n"
             << "+==============================================================================+\n"
             << "  1. View Assignments\n"
             << "  2. Add Assignment\n"
             << "  3. Delete Assignment\n"
             << "  4. Back to Manage Teachers Menu\n"
             << "+==============================================================================+\n"
             << " Enter your choice: ";
        int choice;
        cin >> choice;

        // Helper lambda to detect delimiter automatically
        auto getFields = [](string line) {
            char delim = (line.find('|') != string::npos) ? '|' : ',';
            vector<string> parts;
            stringstream ss(line);
            string temp;
            while(getline(ss, temp, delim)) parts.push_back(temp);
            return parts;
        };

        if(choice == 1){
            // ===== View Assignments =====
            ifstream studentFile("students.txt");
            ifstream teacherFile("teachers.txt");
            ifstream assignFile("assignments.txt");

            vector<string> studentLines, teacherLines, assignmentLines;
            while(getline(studentFile,line)) studentLines.push_back(line);
            while(getline(teacherFile,line)) teacherLines.push_back(line);
            while(getline(assignFile,line)) assignmentLines.push_back(line);

            studentFile.close();
            teacherFile.close();
            assignFile.close();

            cout << left << setw(12) << "Student ID"
                 << setw(20) << "  Student Name"
                 << setw(12) << "  Teacher ID"
                 << setw(20) << "  Teacher Name"
                 << setw(15) << "  Major" << endl;
            cout << "--------------------------------------------------------------------------------\n";

            int index = 1;
            for(auto &assign : assignmentLines){
                size_t delim = assign.find('|');
                string sid = assign.substr(0, delim);
                string tid = assign.substr(delim+1);

                string sName="", tName="", tMajor="";

                for(auto &sLine: studentLines){
                    auto fields = getFields(sLine);
                    if(fields.size() >= 2 && fields[0]==sid) sName = fields[1];
                }

                for(auto &tLine: teacherLines){
                    auto fields = getFields(tLine);
                    if(fields.size() >= 4 && fields[0]==tid){
                        tName = fields[1];
                        tMajor = fields[5];
                    }
                }

                cout << left << setw(3) << index++
                     << setw(12) << sid
                     << setw(20) << sName
                     << setw(12) << tid
                     << setw(20) << tName
                     << setw(15) << tMajor << endl;
            }

            cout << "\nPress any key to continue...";
            _getch();
        }

        else if(choice == 2){
            // ===== Add Assignment =====
            string studentID, teacherID;
            vector<string> validStudents, validTeachers;

            cout << "\nAvailable Students:\n";
            ifstream studentFile("students.txt");
            while(getline(studentFile,line)){
                auto fields = getFields(line);
                if(fields.size() >= 2){
                    string id = fields[0];
                    string name = fields[1];
                    validStudents.push_back(id);
                    cout << id << " - " << name << "\n";
                }
            }
            studentFile.close();

            if(validStudents.empty()){
                cout << "\nNo students available!\nPress any key to continue...";
                _getch();
                continue;
            }

            cout << "\nEnter Student ID to assign (0 to cancel): ";
            cin >> studentID;
            if (studentID == "0"){system("cls"); return;}
            if(find(validStudents.begin(), validStudents.end(), studentID) == validStudents.end()){
                cout << "\nInvalid Student ID!\nPress any key to continue...";
                _getch();
                continue;
            }

            cout << "\nAvailable Teachers:\n";
            ifstream teacherFile("teachers.txt");
            while(getline(teacherFile,line)){
                auto fields = getFields(line);
                if(fields.size() >= 4){
                    string id = fields[0];
                    string name = fields[1];
                    string subject = fields[3];
                    validTeachers.push_back(id);
                    cout << id << " - " << name << " (" << subject << ")\n";
                }
            }
            teacherFile.close();

            cout << "Enter Teacher ID to assign (0 to cancel): ";
            cin >> teacherID;
            if (teacherID == "0"){system("cls"); return;}

            if(find(validTeachers.begin(), validTeachers.end(), teacherID) == validTeachers.end()){
                cout << "Invalid Teacher ID!\nPress any key to continue...";
                _getch();
                continue;
            }

            // Check duplicate
            ifstream assignFileIn("assignments.txt");
            bool exists=false;
            while(getline(assignFileIn,line)){
                size_t delim = line.find('|');
                string sid = line.substr(0,delim);
                string tid = line.substr(delim+1);
                if(sid==studentID && tid==teacherID) exists=true;
            }
            assignFileIn.close();

            if(exists){
                cout << "\nThis assignment already exists!\n";
            } else{
                ofstream assignFileOut("assignments.txt", ios::app);
                assignFileOut << studentID << "|" << teacherID << "\n";
                assignFileOut.close();
                cout << "\n***Teacher " << teacherID << " assigned to Student " << studentID << " successfully!***\n";

                // Ask if user wants to auto-open all existing assessments for this student
                cout << "\n==============================================================================\n";
                cout << "Would you like to automatically open ALL existing assessments\n";
                cout << "from this teacher for the student? (Y/N): ";
                char autoOpen;
                cin >> autoOpen;
                autoOpen = toupper(autoOpen);

                if(autoOpen == 'Y'){
                    // Load teacher's assessments
                    string teacherFolder = "teachers/" + teacherID;
                    string assessFile = teacherFolder + "/assessments.txt";

                    if(fs::exists(assessFile)){
                        ifstream aFile(assessFile);
                        vector<pair<string,string>> assessmentData; // title, type
                        string aLine;

                        while(getline(aFile, aLine)){
                            if(aLine.empty()) continue;
                            stringstream ss(aLine);
                            string title, type;
                            getline(ss, title, '|');
                            getline(ss, type, '|'); // read type (second field)
                            assessmentData.push_back({title, type});
                        }
                        aFile.close();

                        if(!assessmentData.empty()){
                            // Open all assessments for this student
                            ofstream openFile("open_assessments.txt", ios::app);
                            int count = 0;

                            for(const auto& [title, type] : assessmentData){
                                // Check if already opened
                                bool alreadyOpen = false;
                                ifstream checkFile("open_assessments.txt");
                                string checkLine;
                                while(getline(checkFile, checkLine)){
                                    if(checkLine.find(studentID + "|" + teacherID + "|" + title) != string::npos){
                                        alreadyOpen = true;
                                        break;
                                    }
                                }
                                checkFile.close();

                                if(!alreadyOpen){
                                    openFile << studentID << "|" << teacherID << "|" << title << "|NEW|"
                                             << type << "\n";
                                    count++;
                                }
                            }
                            openFile.close();

                            cout << "\nSuccessfully opened " << count << " assessment(s) for the student!\n";
                        } else{
                            cout << "\nNote: This teacher has no assessments created yet.\n";
                        }
                    } else{
                        cout << "\nNote: This teacher has no assessments created yet.\n";
                    }
                } else{
                    cout << "\nNote: The teacher will need to manually 'Open Assessment for Student'\n";
                }
            }

            cout << "\nPress any key to continue...";
            _getch();
        }

        else if(choice == 3){
            // ===== Delete Assignment =====
            vector<string> assignmentLines;
            ifstream assignFile("assignments.txt");
            while(getline(assignFile,line)) assignmentLines.push_back(line);
            assignFile.close();

            if(assignmentLines.empty()){
                cout << "\n  No assignments to delete.\nPress any key to continue...";
                _getch();
                continue;
            }

            // Load students and teachers
            vector<string> studentLines, teacherLines;
            ifstream sFile("students.txt"), tFile("teachers.txt");
            while(getline(sFile,line)) studentLines.push_back(line);
            while(getline(tFile,line)) teacherLines.push_back(line);
            sFile.close();
            tFile.close();

            cout << left << setw(5) << "  No"
                 << setw(12) << "  Student ID"
                 << setw(20) << "  Student Name"
                 << setw(12) << "  Teacher ID"
                 << setw(20) << "  Teacher Name"
                 << setw(15) << "  Subject" << endl
                 << "--------------------------------------------------------------------------------\n";

            int index = 1;
            for(auto &a: assignmentLines){
                size_t delim = a.find('|');
                string sid = a.substr(0,delim);
                string tid = a.substr(delim+1);
                string sName="", tName="", tSubject="";

                for(auto &sLine: studentLines){
                    auto fields = getFields(sLine);
                    if(fields.size() >= 2 && fields[0]==sid) sName = fields[1];
                }

                for(auto &tLine: teacherLines){
                    auto fields = getFields(tLine);
                    if(fields.size() >= 4 && fields[0]==tid){
                        tName = fields[1];
                        tSubject = fields[3];
                    }
                }

                cout << left << setw(5) << index++
                     << setw(12) << sid
                     << setw(20) << sName
                     << setw(12) << tid
                     << setw(20) << tName
                     << setw(15) << tSubject << endl;
            }

            int delIndex;
            cout << "\nEnter the number of the assignment to delete (0 to cancel): ";
            cin >> delIndex;
            if (delIndex == 0){system("cls"); return;}
            if(delIndex < 1 || delIndex > (int)assignmentLines.size()){
                cout << "Invalid selection!\nPress any key to continue...";
                _getch();
                continue;
            }

            cout << "Are you sure you want to delete this assignment? (Y/N): ";
            char conf; cin >> conf;
            if(conf != 'Y' && conf != 'y'){
                cout << "Deletion cancelled.\nPress any key to continue...";
                _getch();
                continue;
            }

            assignmentLines.erase(assignmentLines.begin() + delIndex - 1);
            ofstream assignFileOut("assignments.txt");
            for(auto &a: assignmentLines) assignFileOut << a << "\n";
            assignFileOut.close();

            cout << "  \nAssignment deleted successfully.\nPress any key to continue...";
            _getch();
        }

        else if(choice==4) break;
        else{
            cout << "\nPlease enter a valid number.\n";
            _getch();
        }
    }
}
int teacher::teacherMenu(int choice){
    while (true) {
             system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                              TEACHER DASHBOARD                               |\n"
             << "+==============================================================================+\n"
             << "  1. Manage Assessment\n"
             << "  2. Manage Students\n"
             << "  3. Change Username/Password\n"
             << "  4. Logout\n"
             << "+==============================================================================+\n"
             << " Enter your choice: ";
        cin >> choice;

        if (cin.fail()) { // input validation
            cin.clear();
            cin.ignore(10000, '\n');
            system("CLS");
            cout << "\nInvalid input. Please enter a number.\n";
            system("pause");
            system("CLS");
            continue;
        }

        if (choice == 1) {
            system("CLS");
            manageAssessments();
        }
        else if (choice == 2) {
            system("CLS");
            manageStudents();
        }
        else if (choice == 3) {
            system("CLS");
            changeCredentials();
        }
        else if (choice == 4) {
            system("CLS");
            ::logout("Teacher");
            break;
        }
        else {
            system("CLS");
            cout << "\nPlease enter a valid number (1–4).\n";
            system("pause");
            system("CLS");
        }
    }

    return 0;
}
void teacher::changeCredentials(){
    system("CLS");
    fstream file("teachers.txt", ios::in);
    if (!file) {
        cerr << "Error opening teachers.txt!\n";
        system("pause");
        return;
    }

    // Read all teacher records
    vector<string> records;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) records.push_back(line);
    }
    file.close();

    string currentID = id;
    bool found = false;
    bool updated = false; // track if changes were saved

    for (string &record : records) {
        stringstream ss(record);
        string tID, FName, LName, tUsername, tPassword, tSubject;
        getline(ss, tID, ',');
        getline(ss, FName, ',');
        getline(ss, LName, ',');
        getline(ss, tUsername, ',');
        getline(ss, tPassword, ',');
        getline(ss, tSubject, ',');

        if (tID == currentID) {
            found = true;

            cout << "\n================================================================================\n"
                 << "                            CHANGE CREDENTIALS\n"
                 << "================================================================================\n"
                 << "  Current Username: " << tUsername << "\n"
                 << "  Current Password: " << tPassword << "\n"
                 << "================================================================================\n";

            string newUsername, newPassword;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer safely

            cout << "Enter New Username (leave blank to keep current): ";
            getline(cin, newUsername);

            cout << "Enter New Password (leave blank to keep current): ";
            getline(cin, newPassword);

            // ✅ If both are blank, return to menu without changes
            if (newUsername.empty() && newPassword.empty()) {
                cout << "\n[INFO] No input provided. Returning to Teacher Menu...\n\n";
                system("pause");
                return; // exit function immediately
            }

            // Keep old values if only one field is blank
            if (newUsername.empty()) newUsername = tUsername;
            if (newPassword.empty()) newPassword = tPassword;

            // ✅ If no actual change, skip update
            if (newUsername == tUsername && newPassword == tPassword) {
                cout << "\n[INFO] No changes detected. Returning to Teacher Menu...\n\n";
                system("pause");
                return; // exit function immediately
                system("cls");
            }

            // Confirm before saving
            char confirm;
            while (true) {
                cout << "\nConfirm changes? (Y/N): ";
                cin >> confirm;

                if (confirm == 'Y' || confirm == 'y') {
                    record = tID + "," + FName + "," + LName + "," + newUsername + "," + newPassword + "," + tSubject;
                    updated = true;
                    cout << "\n[SUCCESS] Credentials updated successfully!\n";
                    break;
                }
                else if (confirm == 'N' || confirm == 'n') {
                    cout << "\n[CANCELLED] No changes were made.\n";
                    return; // directly return to menu
                }
                else {
                    cout << "\nInvalid input! Please enter Y or N.\n";
                }
            }
            break;
        }
    }

    if (!found) {
        cout << "\n[ERROR] Teacher record not found.\n";
    }
    else if (updated) {
        // ✅ Only rewrite if update confirmed
        ofstream out("teachers.txt", ios::trunc);
        for (auto &r : records) out << r << "\n";
        out.close();
    }

    cout << "\n";
    system("pause");
}
void teacher::manageAssessments(){
    int choice;
    while (true) {
        system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                              MANAGE ASSESSMENT                               |\n"
             << "+==============================================================================+\n"
             << "  1. Create New Quiz/Exam/Long Quiz\n"
             << "  2. View All Assessments\n"
             << "  3. View Questions per Assessment\n"
             << "  4. Edit Assessment\n"
             << "  5. Delete Assessment\n"
             << "  6. Back to Teacher Menu\n"
             << "+==============================================================================+\n"
             << " Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  Invalid input.\n";
            _getch();
            continue;
        }

        switch (choice) {
            case 1: createAssessment(); break;
            case 2: viewAssessments(); break;
            case 3: viewQuestions(); break;
            case 4: editAssessment(); break;
            case 5: deleteAssessment(); break;
            case 6: return;
            default:
                cout << "Invalid choice.\n";
                _getch();
                break;
        }
    }
}
void teacher::createAssessment(){
    system("CLS");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string type, title, totalTime, subj, numQuestionsStr, deadline;
    int numQuestions = 0;
    bool validInput = false;

    // Loop until valid input is provided
    while (!validInput) {
        system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                              CREATE ASSESSMENT                               |\n"
             << "+==============================================================================+\n"
             << "\nEnter type (Quiz / Long Quiz / Exam) or [1] to cancel: ";
        getline(cin, type);
        if(type == "1"){ system("cls"); return;}
        cout << "Enter title: ";
        getline(cin, title);

        cout << "Enter subject: ";
        getline(cin, subj);

        cout << "Enter total time (in minutes): ";
        getline(cin, totalTime);

        cout << "Enter number of questions: ";
        getline(cin, numQuestionsStr);

        cout << "Enter deadline (YYYY-MM-DD HH:MM): ";
        getline(cin, deadline);

        // Validation for empty fields
        if (type.empty() || title.empty() || subj.empty() || totalTime.empty() ||
            numQuestionsStr.empty() || deadline.empty()) {
            cout << "\nError: All fields are required. Please try again.\n";
            _getch();
            continue;
        }

        // Validate type - must be Quiz, Long Quiz, or Exam (case insensitive)
        string typeLower = type;
        transform(typeLower.begin(), typeLower.end(), typeLower.begin(), ::tolower);
        typeLower = trim(typeLower); // Remove leading/trailing spaces

        if (typeLower != "quiz" && typeLower != "long quiz" && typeLower != "exam") {
            cout << "\n  Invalid type! Please enter one of the following:\n";
            cout << "   - Quiz\n";
            cout << "   - Long Quiz\n";
            cout << "   - Exam\n";
            _getch();
            continue;
        }

        // Validate title - must contain at least one letter
        bool hasLetter = false;
        for (char c : title) {
            if (isalpha(c)) {
                hasLetter = true;
                break;
            }
        }
        if (!hasLetter) {
            cout << "\nInvalid title! Title must contain at least one letter.\n";
            _getch();
            continue;
        }

        // Validate subject - must contain at least one letter
        hasLetter = false;
        for (char c : subj) {
            if (isalpha(c)) {
                hasLetter = true;
                break;
            }
        }
        if (!hasLetter) {
            cout << "\nInvalid subject! Subject must contain at least one letter.\n";
            _getch();
            continue;
        }

        // Validate totalTime is a number
        bool validTime = true;
        for (char c : totalTime) {
            if (!isdigit(c)) {
                validTime = false;
                break;
            }
        }

        if (!validTime) {
            cout << "\nInvalid time. Please enter a valid number for minutes.\n";
            _getch();
            continue;
        }

        // Validate that numQuestionsStr contains only digits
        bool validNumber = true;
        for (char c : numQuestionsStr) {
            if (!isdigit(c)) {
                validNumber = false;
                break;
            }
        }

        if (!validNumber) {
            cout << "\nInvalid number of questions. Please enter a valid positive integer only.\n";
            _getch();
            continue;
        }

        try {
            numQuestions = stoi(numQuestionsStr);
            if (numQuestions <= 0) {
                cout << "\nNumber of questions must be greater than 0.\n";
                _getch();
                continue;
            }
            if (numQuestions > 500) {
                cout << "\nNumber of questions is too large (max 500).\n";
                _getch();
                continue;
            }

            int timeMinutes = stoi(totalTime);
            if (timeMinutes <= 0) {
                cout << "\nTime must be greater than 0 minutes.\n";
                _getch();
                continue;
            }
            if (timeMinutes > 600) {
                cout << "\nTime is too large (max 600 minutes / 10 hours).\n";
                _getch();
                continue;
            }

            // Deadline can be past or future — no validation check needed
            validInput = true; // All validations passed
        } catch (...) {
            cout << "\nInvalid input. Please enter valid positive numbers.\n";
            _getch();
            continue;
        }
    }

    // Create teacher folder
    string teacherFolder = "teachers/" + id;
    fs::create_directories(teacherFolder + "/questions");

    ofstream assessmentsFile(teacherFolder + "/assessments.txt", ios::app);
    string fileName = title + ".txt";

    //  Save deadline as well
    assessmentsFile << title << "|" << type << "|" << subj << "|"
                    << totalTime << "|" << numQuestions << "|"
                    << deadline << "|" << fileName << "\n";
    assessmentsFile.close();

    ofstream qFile(teacherFolder + "/questions/" + fileName);

    // Collect all questions first, then write to file
    vector<string> allQuestions;

    for (int i = 1; i <= numQuestions; ++i) {
        bool questionValid = false;

        while (!questionValid) {
            cout << "\nQuestion " << i << " type (MCQ / ID): ";
            string qtype; getline(cin, qtype);
            qtype = trim(qtype);

            // Validate question type
            string qtypeLower = qtype;
            transform(qtypeLower.begin(), qtypeLower.end(), qtypeLower.begin(), ::tolower);

            if (qtypeLower != "mcq" && qtypeLower != "id") {
                cout << "\nInvalid question type! Please enter 'MCQ' or 'ID' only.\n";
                _getch();
                continue;
            }

            cout << "Enter question: ";
            string question; getline(cin, question);
            question = trim(question);

            if (question.empty()) {
                cout << "\nQuestion cannot be empty. Please try again for this question.\n";
                _getch();
                continue;
            }

            string questionLine = "Q" + to_string(i) + "|" + qtype + "|" + question;

            bool choicesValid = true;
            if (qtypeLower == "mcq") {
                vector<string> choices;
                for (int c = 1; c <= 4; ++c) {
                    cout << "Choice " << c << ": ";
                    string choice; getline(cin, choice);
                    choice = trim(choice);

                    if (choice.empty()) {
                        cout << "\nChoice cannot be empty. Please re-enter this question.\n";
                        _getch();
                        choicesValid = false;
                        break;
                    }
                    choices.push_back(choice);
                }

                if (!choicesValid) {
                    continue; // Retry this question
                }

                // Add choices to question line
                for (int c = 0; c < 4; ++c) {
                    questionLine += "|C" + to_string(c + 1) + ":" + choices[c];
                }
            }

            cout << "Correct answer: ";
            string ans; getline(cin, ans);
            ans = trim(ans);

            if (ans.empty()) {
                cout << "\nAnswer cannot be empty. Please re-enter this question.\n";
                _getch();
                continue; // Retry this question
            }

            questionLine += "|ANS:" + ans;
            allQuestions.push_back(questionLine);
            questionValid = true; // Question successfully entered
        }
    }

    // Now write all questions to file
    for (const auto& q : allQuestions) {
        qFile << q << "\n";
    }

    qFile.close();

    cout << "\nAssessment \"" << title << "\" for subject \"" << subj
         << "\" saved successfully!\n";
    _getch();
}
void teacher::viewAssessments(){
    system("CLS");
    string teacherFolder = "teachers/" + id;
    ifstream file(teacherFolder + "/assessments.txt");

    if (!file.is_open()) {
        cout << "\nNo assessments found for you.\n";
        _getch();
        return;
    }

    cout << left << setw(25) << "Title"
         << setw(15) << "Type"
         << setw(15) << "Subject"
         << setw(10) << "Time"
         << setw(10) << "Items" << endl
         << "--------------------------------------------------------------------------------\n";

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string title, type, subj, time, num, fileName;
        getline(ss, title, '|');
        getline(ss, type, '|');
        getline(ss, subj, '|');
        getline(ss, time, '|');
        getline(ss, num, '|');
        getline(ss, fileName, '|');

        cout << left << setw(25) << title
             << setw(15) << type
             << setw(15) << subj
             << setw(10) << time
             << setw(10) << num << endl;
    }

    file.close();
    cout << "\nPress any key to return...";
    _getch();
}
void teacher::viewQuestions(){
    system("CLS");
    string teacherFolder = "teachers/" + id;
    string filePath = teacherFolder + "/assessments.txt";

    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "\nNo assessments found.\n";
        _getch();
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    file.close();

    if (lines.empty()) {
        cout << "\nNo assessments available.\n";
        _getch();
        return;
    }

    cout << "\nList of Assessments:\n";
    for (int i = 0; i < lines.size(); ++i) {
        stringstream ss(lines[i]);
        string title; getline(ss, title, '|');
        cout << i + 1 << ". " << title << endl;
    }

    int choice;
    cout << "\nEnter number to view questions or [0] to cancel: ";
    cin >> choice;
    cin.ignore();

    if (choice == 0 ){ system("cls"); return;}

    if (choice < 1 || choice > (int)lines.size()) {
        cout << "\nInvalid choice!\n";
        _getch();
        return;
    }

    // Extract file name for selected assessment
    stringstream ss(lines[choice - 1]);
    string title, type, subj, time, num, deadline, fileName;
    getline(ss, title, '|');
    getline(ss, type, '|');
    getline(ss, subj, '|');
    getline(ss, time, '|');
    getline(ss, num, '|');
    getline(ss, deadline, '|');  // Read deadline field
    getline(ss, fileName, '|');   // Now read fileName (7th field)

    string questionPath = teacherFolder + "/questions/" + fileName;

    ifstream qfile(questionPath);
    if (!qfile.is_open()) {
        cout << "\n  No question file found for this assessment.\n";
        _getch();
        return;
    }

    cout << "\n================================================================================\n"
         << "  QUESTIONS for: " << title << "\n"
         << "================================================================================\n\n";

    string qline;
    int qnum = 1;
    while (getline(qfile, qline)) {
        if (qline.empty()) continue;
        cout << "Q" << qnum++ << ": " << qline << endl;
    }

    qfile.close();
    cout << "\n================================================================================\n"
         << "End of questions.\n";
    _getch();
}
void teacher::editAssessment(){
    system("CLS");
    string teacherFolder = "teachers/" + id;
    string filePath = teacherFolder + "/assessments.txt";

    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "\nNo assessments found.\n";
        _getch();
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    file.close();

    if (lines.empty()) {
        cout << "\nNo assessments to edit.\n";
        _getch();
        return;
    }

    cout << "\nList of Assessments:\n";
    for (int i = 0; i < lines.size(); ++i) {
        stringstream ss(lines[i]);
        string title; getline(ss, title, '|');
        cout << i + 1 << ". " << title << endl;
    }

    int editIndex;
    cout << "\nEnter number to edit or [0] to cancel: ";
    cin >> editIndex;
    cin.ignore();
    if (editIndex == 0){ system("cls"); return;}
    if (editIndex < 1 || editIndex > (int)lines.size()) {
        cout << "\n  Invalid choice!\n";
        _getch();
        return;
    }

    // Extract assessment details including deadline
    stringstream ss(lines[editIndex - 1]);
    string title, type, subj, time, num, deadline, fileName;
    getline(ss, title, '|');
    getline(ss, type, '|');
    getline(ss, subj, '|');
    getline(ss, time, '|');
    getline(ss, num, '|');
    getline(ss, deadline, '|');
    getline(ss, fileName, '|');

    cout << "\n  Current Details:\n";
    cout << "  Title: " << title << "\n";
    cout << "  Type: " << type << "\n";
    cout << "  Subject: " << subj << "\n";
    cout << "  Time: " << time << " minutes\n";
    cout << "  Number of Questions: " << num << "\n";
    cout << "  Deadline: " << deadline << "\n";

    string newTitle, newType, newTime, newDeadline;
    int newNum;

    cout << "\nEnter new title (leave blank to keep same): ";
    getline(cin, newTitle);
    if (newTitle.empty()) newTitle = title;

    cout << "Enter new type (leave blank to keep same): ";
    getline(cin, newType);
    if (newType.empty()) newType = type;

    cout << "Enter new total time (leave blank to keep same): ";
    getline(cin, newTime);
    if (newTime.empty()) newTime = time;

    cout << "Enter new number of questions (0 to keep same): ";
    cin >> newNum;
    cin.ignore();
    if (newNum == 0) newNum = stoi(num);

    cout << "  Enter new deadline (leave blank to keep same) : ";
    getline(cin, newDeadline);
    if (newDeadline.empty()) newDeadline = deadline;

    string newFileName = newTitle + ".txt";
    string oldPath = teacherFolder + "/questions/" + fileName;
    string newPath = teacherFolder + "/questions/" + newFileName;

    // Rename file if needed
    if (fileName != newFileName && fs::exists(oldPath)) {
        fs::rename(oldPath, newPath);
    } else if (!fs::exists(newPath)) {
        newPath = oldPath;
    }

    // ===== SHOW QUESTIONS FIRST =====
    ifstream qFile(newPath);
    vector<string> qLines;
    string qline;
    int qNum = 1;

    cout << "\n================================================================================\n"
         << "  Current Questions for: " << title << "\n"
         << "==============================================================================\n";

    while (getline(qFile, qline)) {
        if (qline.empty()) continue;
        cout << "Q" << qNum++ << ": " << qline << "\n";
        qLines.push_back(qline);
    }
    qFile.close();

    if (qLines.empty()) {
        cout << "\n  (No questions found.)\n";
    }

    cout << "\n==============================================================================\n"
         << " Do you want to edit the questions? (y/n): ";
    char editQ; cin >> editQ; cin.ignore();

    if (editQ == 'y' || editQ == 'Y') {
        for (int i = 0; i < qLines.size(); ++i) {
            cout << "\n--------------------------------------------------------------------------------\n"
                 << "  Current: " << qLines[i] << "\n"
                 << "  Edit this question? (y/n): ";
            char choice; cin >> choice; cin.ignore();

            if (choice == 'y' || choice == 'Y') {
                stringstream qs(qLines[i]);
                string qLabel, qType, qText, temp;
                vector<string> choices;
                string ans;

                getline(qs, qLabel, '|');
                getline(qs, qType, '|');
                getline(qs, qText, '|');

                while (getline(qs, temp, '|')) {
                    if (temp.rfind("C", 0) == 0) choices.push_back(temp);
                    else if (temp.rfind("ANS:", 0) == 0) ans = temp.substr(4);
                }

                cout << "\n  Question Type: " << qType << "\n";
                cout << "  Current Question: " << qText << "\n";
                cout << "  Current Answer: " << ans << "\n";

                cout << "\nEnter new question text (leave blank to keep same): ";
                string newQ; getline(cin, newQ);
                if (!newQ.empty()) qText = newQ;

                if (qType == "MCQ" || qType == "mcq") {
                    for (int c = 0; c < (int)choices.size(); ++c) {
                        cout << "  Current " << choices[c] << "\n";
                        cout << "  Edit this choice? (y/n): ";
                        char editC; cin >> editC; cin.ignore();

                        if (editC == 'y' || editC == 'Y') {
                            cout << "Enter new choice text: ";
                            string newC; getline(cin, newC);
                            if (!newC.empty()) {
                                choices[c] = "C" + to_string(c + 1) + ":" + newC;
                            }
                        }
                    }
                }

                cout << "Enter new correct answer (leave blank to keep same): ";
                string newA; getline(cin, newA);
                if (!newA.empty()) ans = newA;

                // Rebuild question line
                string rebuilt = qLabel + "|" + qType + "|" + qText;
                for (auto &c : choices) rebuilt += "|" + c;
                rebuilt += "|ANS:" + ans;

                qLines[i] = rebuilt;
            }
        }

        // Save updated questions
        ofstream qOut(newPath);
        for (auto &ql : qLines) qOut << ql << "\n";
        qOut.close();
    }else if (editQ == 'N' || editQ == 'n'){
        cout << "Cancel update!";
        return;
    }else{
        cout << "invalid input!";
        return;
    }

    // Update assessment info (include deadline)
    lines[editIndex - 1] = newTitle + "|" + newType + "|" + subj + "|" +
                           newTime + "|" + to_string(newNum) + "|" +
                           newDeadline + "|" + newFileName;

    ofstream out(filePath);
    for (auto &l : lines) out << l << "\n";
    out.close();

    cout << "\nAssessment and questions updated successfully!\n";
    _getch();
}
void teacher::deleteAssessment(){
    system("CLS");
    string teacherFolder = "teachers/" + id;
    ifstream file(teacherFolder + "/assessments.txt");

    if (!file.is_open()) {
        cout << "\n  No assessments found.\n";
        _getch();
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    file.close();

    if (lines.empty()) {
        cout << "\nNo assessments to delete.\n";
        _getch();
        return;
    }

    cout << "\nList of Assessments:\n";
    for (int i = 0; i < lines.size(); ++i) {
        stringstream ss(lines[i]);
        string title; getline(ss, title, '|');
        cout << i + 1 << ". " << title << endl;
    }

    int delIndex;
    cout << "\nEnter number to delete (0 to cancel): ";
    cin >> delIndex;
    cin.ignore();

    if (delIndex == 0) {
        cout << "\nDeletion cancelled.\n";
        _getch();
        return;
    }

    if (delIndex < 1 || delIndex > (int)lines.size()) {
        cout << "Invalid choice!\n";
        _getch();
        return;
    }

    // Get details for confirmation
    stringstream ss(lines[delIndex - 1]);
    string title, type, subj, time, num, deadline, fileName;
    getline(ss, title, '|');
    getline(ss, type, '|');
    getline(ss, subj, '|');
    getline(ss, time, '|');
    getline(ss, num, '|');
    getline(ss, deadline, '|');
    getline(ss, fileName, '|');

    // Confirm deletion
    char confirm;
    cout << "\nAre you sure you want to delete this assessment?\n"
         << "Title: " << title << "\nSubject: " << subj << "\nType: " << type << "\n"
         << "This will permanently delete the question file as well.\n"
         << "Enter Y to confirm, N to cancel: ";
    cin >> confirm;
    confirm = toupper(confirm);

    if (confirm != 'Y') {
        cout << "\n  Deletion cancelled.\n";
        _getch();
        return;
    }

    // Proceed with deletion
    lines.erase(lines.begin() + delIndex - 1);
    ofstream out(teacherFolder + "/assessments.txt");
    for (auto &l : lines) out << l << "\n";
    out.close();

    // Delete question file if exists
    string questionPath = teacherFolder + "/questions/" + fileName;
    if (fs::exists(questionPath)) {
        fs::remove(questionPath);
    }

    cout << "\n  Assessment \"" << title << "\" deleted successfully.\n";
    _getch();
}
void teacher::manageStudents(){
    int choice;
    while (true) {
        system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                                MANAGE STUDENTS                               |\n"
             << "+==============================================================================+\n"
             << "  1. View Assigned Students\n"
             << "  2. Open Assessment for Student\n"
             << "  3. Reopen Assessment\n"
             << "  4. View Student Results\n"
             << "  5. Back to Teacher Menu\n"
             << "+==============================================================================+\n"
             << "  Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  Invalid input.\n";
            _getch();
            continue;
        }

        switch (choice) {
            case 1: viewAssignedStudents(); break;
            case 2: openAssessmentForStudent(); break;
            case 3: reopenAssessment(); break;
            case 4: viewStudentResults(); break;
            case 5: return;
            default:
                cout << "  Invalid choice.\n";
                _getch();
                break;
        }
    }
}
void teacher::viewAssignedStudents(){
    system("CLS");
    cout << "\n================================================================================\n"
         << "                          Assigned Students \n"
         << "================================================================================\n";

    ifstream assignFile("assignments.txt");
    ifstream studentFile("students.txt");

    if (!assignFile.is_open() || !studentFile.is_open()) {
        cout << "Error: Missing file(s)!\n";
        _getch();
        return;
    }

    struct Student {
        string id, last_name, first_name, username, course, section, password;
    };

    vector<Student> students;
    string line;

    // 🔹 Load all students from students.txt
    while (getline(studentFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Student s;
        getline(ss, s.id, ',');
        getline(ss, s.last_name, ',');
        getline(ss, s.first_name, ',');
        getline(ss, s.username, ',');
        getline(ss, s.course, ',');
        getline(ss, s.section, ',');
        getline(ss, s.password, ',');

        if (!s.id.empty()) students.push_back(s);
    }
    studentFile.close();

    // 🔹 Collect assigned student IDs for this teacher
    vector<string> assignedIDs;
    while (getline(assignFile, line)) {
        size_t delim = line.find('|');
        if (delim == string::npos) continue;

        string sid = line.substr(0, delim);
        string tid = line.substr(delim + 1);

        if (tid == id) // only those assigned to this teacher
            assignedIDs.push_back(sid);
    }
    assignFile.close();

    // 🔹 Filter assigned students
    vector<Student> assignedStudents;
    for (const auto &sid : assignedIDs) {
        for (const auto &s : students) {
            if (s.id == sid) {
                assignedStudents.push_back(s);
                break;
            }
        }
    }

    if (assignedStudents.empty()) {
        cout << "\n  No students assigned yet.\n";
        cout << "\n  Press any key to continue...";
        _getch();
        return;
    }

    // 🔹 Sort alphabetically by last name (case-insensitive)
    sort(assignedStudents.begin(), assignedStudents.end(), [](const Student &a, const Student &b) {
        string lnameA = a.last_name, lnameB = b.last_name;
        transform(lnameA.begin(), lnameA.end(), lnameA.begin(), ::tolower);
        transform(lnameB.begin(), lnameB.end(), lnameB.begin(), ::tolower);
        return lnameA < lnameB;
    });

    // 🔹 Display students
    for (const auto &s : assignedStudents) {
        cout << "Student ID: " << s.id << "\n";
        cout << "Name      : " << s.first_name << " " << s.last_name << "\n";
        cout << "Course    : " << s.course << "\n";
        cout << "Section   : " << s.section << "\n";
        cout << "--------------------------------------------------------------------------------\n";
    }

    cout << "\n  Press any key to continue...";
    _getch();
}
void teacher::openAssessmentForStudent(){
    system("CLS");
    cout << "\n================================================================================\n"
         << "                       OPEN ASSESSMENT FOR STUDENT\n"
         << "================================================================================\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Load assigned students
    vector<pair<string, string>> assignedStudents; // id, name
    ifstream assignFile("assignments.txt");

    if(!assignFile.is_open()){
        cout << "\n  Error: Could not open assignments file.\n"
             << "  Please ensure assignments.txt exists.\n";
        _getch();
        return;
    }

    string line;
    while (getline(assignFile, line)) {
        if (line.empty()) continue;
        size_t delim = line.find('|');
        if (delim == string::npos) continue;
        string sid = line.substr(0, delim);
        string tid = line.substr(delim + 1);

        // Trim whitespace
        sid.erase(remove_if(sid.begin(), sid.end(), ::isspace), sid.end());
        tid.erase(remove_if(tid.begin(), tid.end(), ::isspace), tid.end());

        if (tid != id) continue;

        // load name from students.txt
        ifstream studentFile("students.txt");
        string studentLine;
        while (getline(studentFile, studentLine)) {
            if (studentLine.empty()) continue;
            stringstream ss(studentLine);
            string sID, sName;
            getline(ss, sID, ',');
            getline(ss, sName, ',');

            if (sID == sid) {
                assignedStudents.push_back({sid, sName});
                break;
            }
        }
        studentFile.close();
    }
    assignFile.close();

    if (assignedStudents.empty()) {
        cout << "\n   No students assigned to you yet.\n";
        cout << "\n  Please contact an administrator to assign students to you.\n";
        cout << "\n  Press any key to continue...";
        _getch();
        return;
    }

    // Display students
    cout << "\n                       Your Assigned Students:\n";
    cout << "================================================================================\n";
    for (size_t i = 0; i < assignedStudents.size(); ++i)
        cout << i + 1 << ". " << assignedStudents[i].second << " (ID: " << assignedStudents[i].first << ")\n";
    cout << "================================================================================\n";

    cout << "\n  Select student number (or 0 to cancel): ";
    string choiceStr;
    getline(cin, choiceStr);

    if(choiceStr.empty() || !all_of(choiceStr.begin(), choiceStr.end(), ::isdigit)){
        cout << "\n  Invalid input. Returning to menu.\n";
        _getch();
        return;
    }

    int choice = stoi(choiceStr);

    if(choice == 0) return; // Cancel

    if (choice < 1 || choice > (int)assignedStudents.size()){
        cout << "\n  Invalid selection. Returning to menu.\n";
        _getch();
        return;
    }

    string studentID = assignedStudents[choice - 1].first;
    string studentName = assignedStudents[choice - 1].second;

    // Load teacher assessments
    vector<string> assessments;
    string teacherFolder = "teachers/" + id;
    string assessFilePath = teacherFolder + "/assessments.txt";

    if(!fs::exists(assessFilePath)){
        cout << "\n   You have not created any assessments yet.\n";
        cout << "\n  Please create an assessment first from the 'Manage Assessment' menu.\n";
        cout << "\n  Press any key to continue...";
        _getch();
        return;
    }

    ifstream assessFile(assessFilePath);
    if(!assessFile.is_open()){
        cout << "\nError: Could not open your assessments file.\n";
        _getch();
        return;
    }

    while (getline(assessFile, line)) {
        if (line.empty()) continue;
        string title;
        stringstream ss(line);
        getline(ss, title, '|');
        if (!title.empty()) assessments.push_back(title);
    }
    assessFile.close();

    if (assessments.empty()) {
        cout << "\n  You have not created any assessments yet.\n"
             << "\n  Please create an assessment first from the 'Manage Assessment' menu.\n"
             << "\n  Press any key to continue...";
        _getch();
        return;
    }

    // Display assessments
    cout << "\n                         Your Assessments:\n"
         << "================================================================================\n";
    for (size_t i = 0; i < assessments.size(); ++i)
        cout << i + 1 << ". " << assessments[i] << "\n"
             << "================================================================================\n";

    cout << "\n  Select assessment number (or 0 to cancel): ";
    string assessChoiceStr;
    getline(cin, assessChoiceStr);

    if(assessChoiceStr.empty() || !all_of(assessChoiceStr.begin(), assessChoiceStr.end(), ::isdigit)){
        cout << "\n  Invalid input. Returning to menu.\n";
        _getch();
        return;
    }

    int assessChoice = stoi(assessChoiceStr);

    if(assessChoice == 0) return; // Cancel

    if (assessChoice < 1 || assessChoice > (int)assessments.size()){
        cout << "\n  Invalid selection. Returning to menu.\n";
        _getch();
        return;
    }

    string selectedAssessment = assessments[assessChoice - 1];

    // Get assessment type from assessments.txt
    string assessmentType = "quiz"; // default
    ifstream assessTypeFile(assessFilePath);
    string assessTypeLine;
    while(getline(assessTypeFile, assessTypeLine)){
        if(assessTypeLine.empty()) continue;
        stringstream ss(assessTypeLine);
        string aTitle, aType;
        getline(ss, aTitle, '|');
        getline(ss, aType, '|');
        if(aTitle == selectedAssessment){
            assessmentType = aType;
            break;
        }
    }
    assessTypeFile.close();

    // Check if assessment already opened for this student
    ifstream checkFile("open_assessments.txt");
    bool alreadyOpened = false;
    string checkLine;
    while(getline(checkFile, checkLine)){
        if(checkLine.find(studentID + "|" + id + "|" + selectedAssessment) != string::npos){
            // Check status
            stringstream ss(checkLine);
            string sid, tid, title, status;
            getline(ss, sid, '|');
            getline(ss, tid, '|');
            getline(ss, title, '|');
            getline(ss, status, '|');

            if(status == "NEW" || status == "IN_PROGRESS"){
                alreadyOpened = true;
                cout << "\n   Warning: This assessment is already OPEN for this student!\n"
                     << "  Current Status: " << status << "\n"
                     << "\n  Press any key to continue...";
                _getch();
                return;
            } else if(status == "COMPLETED"){
                cout << "\n  Note: This assessment was already completed by the student.\n"
                     << "  If you want them to retake it, use 'Reopen Assessment' option instead.\n"
                     << "\n  Press any key to continue...";
                _getch();
                return;
            }
        }
    }
    checkFile.close();

    // Save to open_assessments.txt with status NEW
    ofstream openFile("open_assessments.txt", ios::app);
    if(!openFile.is_open()){
        cout << "\nError: Could not open assessments file for writing.\n"
             << "  Please check file permissions.\n";
        _getch();
        return;
    }

    openFile << studentID << "|" << id << "|" << selectedAssessment << "|NEW|" << assessmentType << "\n";
    openFile.close();

    cout << "\n  Assessment '" << selectedAssessment
         << "' is now OPEN for student: " << studentName << "!\n"
         << "\nThe student can now see and take this assessment.\n"
         << "\nPress any key to continue...";
    _getch();
}
void teacher::reopenAssessment(){
    system("CLS");
    cout << "\n  [Reopen Assessment]\n"
         << "  Allows a student to retake a previously completed assessment.\n\n";

    ifstream openFile("open_assessments.txt");
    if (!openFile) {
        cout << "  No assessments found.\n";
        _getch();
        return;
    }

    vector<string> lines;
    string line;
    while (getline(openFile, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    openFile.close();

    // lineNo, studentID, title, status
    vector<tuple<int, string, string, string>> completedAssessments;

    for (size_t i = 0; i < lines.size(); i++) {
        stringstream ss(lines[i]);
        string sid, tid, title, status, type;
        getline(ss, sid, '|');
        getline(ss, tid, '|');
        getline(ss, title, '|');
        getline(ss, status, '|');
        getline(ss, type, '|');

        // Only get completed assessments for this teacher
        if (tid == id && status == "COMPLETED") {
            completedAssessments.push_back({ (int)i, sid, title, status });
        }
    }

    if (completedAssessments.empty()) {
        cout << "No completed assessments to reopen.\n";
        _getch();
        return;
    }

    // Display list of completed assessments
    cout << "Completed Assessments:\n";
    for (size_t i = 0; i < completedAssessments.size(); i++) {
        cout << i + 1 << ". StudentID: " << get<1>(completedAssessments[i])
             << " | Assessment: " << get<2>(completedAssessments[i]) << "\n";
    }

    // Get user choice
    cout << "\nSelect assessment number to reopen: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
    string choiceStr;
    getline(cin, choiceStr);

    // Validate input
    if (choiceStr.empty() || !all_of(choiceStr.begin(), choiceStr.end(), ::isdigit)) {
        cout << "Invalid input.\n";
        _getch();
        return;
    }

    int choice = stoi(choiceStr);
    if (choice < 1 || choice >(int)completedAssessments.size()) {
        cout << "Invalid choice.\n";
        _getch();
        return;
    }

    int targetLine = get<0>(completedAssessments[choice - 1]);
    string studentID = get<1>(completedAssessments[choice - 1]);
    string title = get<2>(completedAssessments[choice - 1]);

    // Parse the selected line safely (even if file has more columns)
    vector<string> fields;
    string part;
    stringstream ss2(lines[targetLine]);
    while (getline(ss2, part, '|')) fields.push_back(part);

    // Update only the status (last column)
    if (fields.size() >= 4) {
        fields[3] = "NEW"; // change status to NEW
        string newLine = fields[0];
        for (size_t j = 1; j < fields.size(); j++)
            newLine += "|" + fields[j];
        lines[targetLine] = newLine;
    } else {
        cout << "Error: Invalid line format.\n";
        _getch();
        return;
    }

    // Save all lines back to file
    ofstream outFile("open_assessments.txt");
    for (auto& l : lines) outFile << l << "\n";
    outFile.close();

    cout << "\nAssessment '" << title << "' has been reopened for student: " << studentID << "\n";
    cout << "Press any key to continue...";
    _getch();
}
void teacher::viewStudentResults(){
    system("CLS");
    ifstream resFile("results.txt");
    if (!resFile.is_open()) {
        cout << "No results found.\n"; _getch(); return;
    }

    vector<vector<string>> results;
    string line;
    while (getline(resFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<string> record;
        string tmp;
        while (getline(ss, tmp, '|')) record.push_back(tmp);
        results.push_back(record);
    }
    resFile.close();

    if (results.empty()) {
        cout << "No results available.\n"; _getch(); return;
    }

    cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                                 STUDENTS RESULTS                             |\n"
             << "+==============================================================================+\n"
             << "Search by Student ID, Name, or Assessment Title (leave empty to show all): ";
    string query;
    cin.ignore();
    getline(cin, query);
    query = trim(query);

    // Table Header
    cout << "\n"
         << left << setw(12) << "StudentID"
         << setw(20) << "Assessment"
         << setw(10) << "Score"
         << setw(10) << "Total"
         << setw(12) << "Date" << "\n"
         << string(84, '-') << "\n";

    int count = 0;
    for (auto &r : results) {
        string sid = r.size() > 0 ? r[0] : "";
        string title = r.size() > 2 ? r[2] : "";
        string score = r.size() > 3 ? r[3] : "";
        string total = r.size() > 4 ? r[4] : "";
        string date = r.size() > 5 ? r[5] : "";

        string studentName = sid; // fallback
        // Optionally, load student name from student file
        ifstream studentFile("students.txt");
        string stLine;
        while (getline(studentFile, stLine)) {
            stringstream ssS(stLine);
            string sId, sName, dummy;
            getline(ssS, sId, '|'); getline(ssS, sName, '|');
            if (sId == sid) { studentName = sName; break; }
        }
        studentFile.close();

        // Filter by search query
        if (!query.empty() &&
            studentName.find(query) == string::npos &&
            sid.find(query) == string::npos &&
            title.find(query) == string::npos)
            continue;

        cout << left << setw(12) << sid
             << setw(20) << title
             << setw(10) << score
             << setw(10) << total
             << setw(12) << date << "\n";

        count++;
    }

    if (count == 0) cout << "No matching results found.\n";

    cout << "\nPress any key to return to menu...";
    _getch();
}
int student::studentMenu(int choice){
    while (true) {
        system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                              STUDENT DASHBOARD                               |\n"
             << "+==============================================================================+\n"
             << "  1. Take Assessment\n"
             << "  2. View Results Assessment\n"
             << "  3. Change Username/Password\n"
             << "  4. Logout\n"
             << "+==============================================================================+\n"
             << " Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            system("pause");
            continue;
        }

        switch (choice) {
            case 1:
                takeAssessmentMenu();
                break;
            case 2:
                viewResultsAssessmentMenu();
                break;
            case 3:
                changeCredentials();
                break;
            case 4:
                ::logout("Student");
                return 0;
            default:
                cout << "\nInvalid choice. Please enter 1–4.\n";
                system("pause");
        }
    }
}
void student::takeAssessmentMenu(){
    int choice;

    while (true) {
        system("CLS");
        cout << "\f\n\n"
             << "+==============================================================================+\n"
             << "|                                TAKE ASSESSMENT                               |\n"
             << "+==============================================================================+\n"
             << "  1. View Available Assessments\n"
             << "  2. Start Assessment\n"
             << "  3. Back to Student Menu\n"
             << "+==============================================================================+\n"
             << "  Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            system("pause");
            continue;
        }

        switch (choice) {
            case 1:
                viewAvailableAssessments();
                break;
            case 2:
                startAssessment();
                break;
            case 3:
                return;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                system("pause");
        }
    }
}
void student::viewAvailableAssessments() {
    system("CLS");
    cout << "\nAvailable Assessments:\n";

    ifstream openFile("open_assessments.txt");
    string line;
    vector<pair<string,string>> newAssessments;

    vector<string> allLines;
    while (getline(openFile, line)) {
        if (line.empty()) continue;
        allLines.push_back(line);
        stringstream ss(line);
        string sid, tid, title, status, type;
        getline(ss, sid, '|');
        getline(ss, tid, '|');
        getline(ss, title, '|');
        getline(ss, status, '|');
        getline(ss, type, '|');

        if (sid == id && status == "NEW") {
            newAssessments.push_back({title, tid});
        }
    }
    openFile.close();

    if (newAssessments.empty()) {
        cout << "No new assessments available.\n";
    } else {
        cout << "  You have new assessments!\n";
        for (size_t i = 0; i < newAssessments.size(); ++i)
            cout << i+1 << ". " << newAssessments[i].first
                 << " (Teacher: " << newAssessments[i].second << ")\n";
    }

    cout << "\nPress any key to continue...";
    _getch();
}
void student::startAssessment(){
    system("CLS");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ifstream openFile("open_assessments.txt");
    if (!openFile.is_open()) {
        cout << "Error: Could not open assessments file.\n";
        _getch();
        return;
    }

    string line;
    vector<tuple<string, string, int>> available;
    vector<string> lines;
    int lineNo = 0;

    while (getline(openFile, line)) {
        lines.push_back(line);
        if (line.empty()) { lineNo++; continue; }

        stringstream ss(line);
        string sid, tid, title, status;
        getline(ss, sid, '|');
        getline(ss, tid, '|');
        getline(ss, title, '|');
        getline(ss, status, '|');

        sid = trim(sid);
        tid = trim(tid);
        title = trim(title);
        status = trim(status);

        if (sid == id && status == "NEW") {
            available.push_back({title, tid, lineNo});
        }
        lineNo++;
    }
    openFile.close();

    if (available.empty()) {
        cout << "No assessments available.\n\nPress any key to continue...";
        _getch();
        return;
    }

    cout << "================================================================================\n"
         << "                               AVAILABLE ASSESSMENTS\n"
         << "================================================================================\n";
    for (size_t i = 0; i < available.size(); ++i)
        cout << i + 1 << ". " << get<0>(available[i]) << " (Teacher ID: " << get<1>(available[i]) << ")\n";
    cout << "================================================================================\n";

    string choiceStr;
    cout << "\nSelect assessment number (or 0 to cancel): ";
    getline(cin, choiceStr);
    choiceStr = trim(choiceStr);

    if (choiceStr.empty() || !all_of(choiceStr.begin(), choiceStr.end(), ::isdigit)) {
        cout << "Invalid input. Returning to menu.\n";
        _getch();
        return;
    }

    int choice = stoi(choiceStr);
    if (choice == 0) return;
    if (choice < 1 || choice > (int)available.size()) {
        cout << "Choice out of range. Returning to menu.\n";
        _getch();
        return;
    }

    string title = get<0>(available[choice - 1]);
    string teacherID = get<1>(available[choice - 1]);
    int targetLine = get<2>(available[choice - 1]);

    string teacherFolder = "teachers/" + teacherID;
    string assessmentFile = teacherFolder + "/assessments.txt";

    int totalTimeMinutes = 5;

    ifstream assessFile(assessmentFile);
    if (!assessFile.is_open()) {
        cout << "\nError: Could not open " << assessmentFile << "\n";
        _getch();
        return;
    }

    string assessLine;
    bool found = false;
    while (getline(assessFile, assessLine)) {
        stringstream ass(assessLine);
        string aTitle, aType, aSubj, aTime, aNumQ, aDeadline, aFile;
        getline(ass, aTitle, '|');
        getline(ass, aType, '|');
        getline(ass, aSubj, '|');
        getline(ass, aTime, '|');
        getline(ass, aNumQ, '|');
        getline(ass, aDeadline, '|');
        getline(ass, aFile, '|');
        aTitle = trim(aTitle);
        if (aTitle == title) {
            found = true;
            try { totalTimeMinutes = stoi(aTime); }
            catch (...) { totalTimeMinutes = 5; }
            break;
        }
    }
    assessFile.close();

    if (!found) {
        cout << "\nAssessment not found.\n";
        _getch();
        return;
    }

    // Mark as IN_PROGRESS
    stringstream ssLine(lines[targetLine]);
    string sid_p, tid_p, title_p, status_p, remaining;
    getline(ssLine, sid_p, '|');
    getline(ssLine, tid_p, '|');
    getline(ssLine, title_p, '|');
    getline(ssLine, status_p, '|');
    getline(ssLine, remaining); // rest of line

    lines[targetLine] = sid_p + "|" + tid_p + "|" + title_p + "|IN_PROGRESS|" + remaining;

    ofstream openOut("open_assessments.txt");
    for (auto &l : lines) openOut << l << "\n";
    openOut.close();

    // Load questions
    string questionFile = teacherFolder + "/questions/" + title + ".txt";
    ifstream qFile(questionFile);
    if (!qFile.is_open()) {
        cout << "\nError: Question file not found.\n";
        _getch();
        return;
    }

    vector<string> questions;
    while (getline(qFile, line))
        if (!line.empty()) questions.push_back(line);
    qFile.close();

    if (questions.empty()) {
        cout << "\nNo questions found.\n";
        _getch();
        return;
    }

    int totalTimeSec = totalTimeMinutes * 60;

    cout << "\n================================================================================\n"
         << "  Assessment: " << title << "\n"
         << "  Time Limit: " << totalTimeMinutes << " minutes\n"
         << "================================================================================\n"
         << "\nPress any key to start...";
    _getch();

    auto startTime = chrono::steady_clock::now();

    vector<string> answers(questions.size(), ""); // tracking answers
    double score = 0;
    int currentIndex = 0;

    // ======= START REAL-TIME TIMER + MENU LOOP =======
    // ======= START REAL-TIME TIMER + MENU LOOP =======
    while (true) {
        auto elapsed = chrono::duration_cast<chrono::seconds>(
            chrono::steady_clock::now() - startTime).count();
        int remaining_time = totalTimeSec - (int)elapsed;

        if (remaining_time <= 0) {
            cout << "\nTIME'S UP! Automatically submitted.\n";
            break;
        }

        int minLeft = remaining_time / 60;
        int secLeft = remaining_time % 60;

        // display question
        string qLine = questions[currentIndex];
        stringstream ss(qLine);
        string qNum, qType, qText, correctAnswer = "";
        vector<string> options;

        getline(ss, qNum, '|');
        getline(ss, qType, '|');
        getline(ss, qText, '|');

        string temp;
        while (getline(ss, temp, '|')) {
            string trimmed = trim(temp);
            string lower = trimmed;
            transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            if (lower.rfind("answer:", 0) == 0 || lower.rfind("ans:", 0) == 0)
                correctAnswer = trim(trimmed.substr(trimmed.find(':') + 1));
            else if (!trimmed.empty()) options.push_back(trimmed);
        }

        // ===== TIMER REFRESH LOOP =====
        while (true) {
            auto elapsed2 = chrono::duration_cast<chrono::seconds>(
                chrono::steady_clock::now() - startTime).count();
            int remaining2 = totalTimeSec - (int)elapsed2;

            if (remaining2 <= 0) {
                cout << "\nTIME'S UP! Automatically submitted.\n";
                goto endAssessment;
            }

            int minLeft2 = remaining2 / 60;
            int secLeft2 = remaining2 % 60;

            system("CLS");
            cout << "================================================================================\n"
                 << "Time Left: " << setw(2) << setfill('0') << minLeft2 << "m "
                 << setw(2) << setfill('0') << secLeft2 << "s\n"
                 << "================================================================================\n"
                 << qNum << ". " << qText << " [" << qType << "]\n\n";
            for (auto &opt : options) cout << "  " << opt << "\n";
            cout << "\nCurrent answer: "
                 << (answers[currentIndex].empty() ? "(none)" : answers[currentIndex]) << "\n"
                 << "================================================================================\n"
                 << "[1] Answer this question\n"
                 << "[2] Next question\n"
                 << "[3] Previous question (only if unanswered)\n"
                 << "[4] Submit assessment\n"
                 << "================================================================================\n"
                 << "Choose option: ";
            cout.flush();

            for (int i = 0; i < 1; ++i) {
                if (_kbhit()) goto gotInput;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }

        gotInput:
        string optChoice;
        getline(cin, optChoice);
        optChoice = trim(optChoice);

        if (optChoice == "1") {
            cout << "\nEnter your answer: ";
            string ans;
            getline(cin, ans);
            ans = trim(ans);
            if (ans.empty()) ans = "No Answer";
            answers[currentIndex] = ans;

            cout << "\nAnswer saved! This question is now locked.\n";
            _getch();

            // ✅ Automatically move to the next unanswered question
            bool foundNext = false;
            for (size_t i = currentIndex + 1; i < questions.size(); ++i) {
                if (answers[i].empty()) {
                    currentIndex = i;
                    foundNext = true;
                    break;
                }
            }

            // If no more unanswered questions, go to submission
            if (!foundNext) goto endAssessment;

        } else if (optChoice == "2") {
            // ✅ Move forward ONLY to unanswered questions
            bool foundNext = false;
            for (size_t i = currentIndex + 1; i < questions.size(); ++i) {
                if (answers[i].empty()) {
                    currentIndex = i;
                    foundNext = true;
                    break;
                }
            }
            if (!foundNext) {
                cout << "\nNo more unanswered questions ahead.\n";
                _getch();
            }

        } else if (optChoice == "3") {
            // ✅ Move backward ONLY to unanswered questions
            bool foundPrev = false;
            for (int i = currentIndex - 1; i >= 0; --i) {
                if (answers[i].empty()) {
                    currentIndex = i;
                    foundPrev = true;
                    break;
                }
            }
            if (!foundPrev) {
                cout << "\nNo unanswered previous question available.\n";
                _getch();
            }

        } else if (optChoice == "4") {
            char confirm;
            cout << "\nAre you sure you want to submit? (Y/N): ";
            cin >> confirm;
            confirm = toupper(confirm);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (confirm == 'Y') {
                goto endAssessment;
            } else {
                continue;
            }

        } else {
            cout << "\nInvalid choice.\n";
            _getch();
        }

    }

endAssessment:
    // compute score
    for (size_t i = 0; i < questions.size(); i++) {
        string qLine = questions[i];
        stringstream ss(qLine);
        string qNum, qType, qText, correctAnswer = "", temp;
        vector<string> opts;
        getline(ss, qNum, '|');
        getline(ss, qType, '|');
        getline(ss, qText, '|');
        while (getline(ss, temp, '|')) {
            string t = trim(temp);
            string lower = t;
            transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            if (lower.rfind("answer:", 0) == 0 || lower.rfind("ans:", 0) == 0)
                correctAnswer = trim(t.substr(t.find(':') + 1));
        }

        string userAns = answers[i];
        string a1 = userAns, a2 = correctAnswer;
        transform(a1.begin(), a1.end(), a1.begin(), ::tolower);
        transform(a2.begin(), a2.end(), a2.begin(), ::tolower);
        a1.erase(remove_if(a1.begin(), a1.end(), ::isspace), a1.end());
        a2.erase(remove_if(a2.begin(), a2.end(), ::isspace), a2.end());

        if (a1 == a2 && !a1.empty()) score++;
    }

    // Save result
    ofstream resFile("results.txt", ios::app);
    resFile << id << "|" << teacherID << "|" << title << "|" << score << "|" << questions.size() << "|" << __DATE__ << "\n";
    resFile.close();

    // CRITICAL FIX: Mark as COMPLETED after finishing the assessment
    stringstream ssLine2(lines[targetLine]);
    string sid_p2, tid_p2, title_p2, status_p2, remaining2;
    getline(ssLine2, sid_p2, '|');
    getline(ssLine2, tid_p2, '|');
    getline(ssLine2, title_p2, '|');
    getline(ssLine2, status_p2, '|');
    getline(ssLine2, remaining2);

    lines[targetLine] = sid_p2 + "|" + tid_p2 + "|" + title_p2 + "|COMPLETED|" + remaining2;

    ofstream openOut2("open_assessments.txt");
    for (auto &l : lines) openOut2 << l << "\n";
    openOut2.close();

    system("CLS");
    cout << "\n================================================================================\n"
         << "                             ASSESSMENT COMPLETED!\n"
         << "================================================================================\n"
         << "Assessment: " << title << "\n"
         << "Score: " << score << " / " << questions.size() << "\n"
         << "================================================================================\n"
         << "\nPress any key to continue...";
    _getch();
}
void student::viewResultsAssessmentMenu(){
    int choice;

    while (true) {
        system("CLS");
        cout << "\f\f\n================================================================================\n"
             << "                         VIEW RESULTS ASSESSMENT   \n"
             << "================================================================================\n"
             << "  1. View Latest Result\n"
             << "  2. Review Previous Assessments\n"
             << "  3. Back to Student Menu\n"
             << "================================================================================\n"
             << "  Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n  Invalid input. Please enter a number.\n";
            system("pause");
            continue;
        }

        if (choice == 1) {
            system("CLS");
            viewLatestResult();
        }
        else if (choice == 2) {
            system("CLS");
            reviewPreviousAssessments();
        }
        else if (choice == 3) {
           studentMenu(0);
        }
        else {
            cout << "\n  Invalid choice. Please try again.\n";
            system("pause");
        }
    }
}
void student::viewLatestResult(){
    system("CLS");
    cout << "\n  [View Latest Assessment Result]\n\n";

    ifstream resFile("results.txt");
    if (!resFile) {
        cout << "No results found.\n";
        _getch();
        return;
    }

    string line;
    string latestLine;
    while (getline(resFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string sid, tid, title, scoreStr, totalStr, date;
        getline(ss, sid, '|');
        getline(ss, tid, '|');
        getline(ss, title, '|');
        getline(ss, scoreStr, '|');
        getline(ss, totalStr, '|');
        getline(ss, date, '|');

        if (sid == id)
            latestLine = line; // last matching line is the latest
    }
    resFile.close();

    if (latestLine.empty()) {
        cout << "No results found.\n";
        _getch();
        return;
    }

    stringstream ss(latestLine);
    string sid, tid, title, scoreStr, totalStr, date;
    getline(ss, sid, '|');
    getline(ss, tid, '|');
    getline(ss, title, '|');
    getline(ss, scoreStr, '|');
    getline(ss, totalStr, '|');
    getline(ss, date, '|');

    // Convert safely
    double score = 0.0, total = 0.0;
    try { score = stod(scoreStr); } catch (...) {}
    try { total = stod(totalStr); } catch (...) {}

    // Compute percentage (always based on total items)
    double percent = (total > 0) ? (score / total) * 100.0 : 0.0;

    // Show results
    cout << "  Assessment: " << title << "\n";
    cout << "  Correct Items: " << score << " / " << total << "\n";
    cout << "  Percentage: " << fixed << setprecision(2) << percent << "%\n";

    string remark;
    if (percent >= 97) remark = "Excellent";
    else if (percent >= 85) remark = "Good";
    else if (percent >= 80) remark = "Fair (Passed)";
    else remark = "Failed";

    cout << "  Remark: " << remark << "\n";
    cout << "  Date Taken: " << date << "\n";

    cout << "\n  Passing Score: 80%\n";
    cout << "\n  Press any key to continue...";
    _getch();
}
void student::reviewPreviousAssessments(){
    system("CLS");
    cout << "\n [Review Previous Assessments]\n\n";

    ifstream resFile("results.txt");
    if (!resFile) {
        cout << "No results found.\n";
        _getch();
        return;
    }

    string line;
    vector<string> studentResults;
    vector<string> allResults; // store all lines to help with update later

    while (getline(resFile, line)) {
        if (line.empty()) continue;
        allResults.push_back(line);

        stringstream ss(line);
        string sid, tid, title, scoreStr, totalStr, date, subject;
        getline(ss, sid, '|');
        getline(ss, tid, '|');
        getline(ss, title, '|');
        getline(ss, scoreStr, '|');
        getline(ss, totalStr, '|');
        getline(ss, date, '|');
        getline(ss, subject, '|'); // assuming you store subject/major in results.txt

        if (sid == id) {
            studentResults.push_back(subject + " | " + scoreStr + "/" + totalStr + " | " + date);
        }
    }
    resFile.close();

    if (studentResults.empty()) {
        cout << "  No previous assessments found.\n";
    } else {
        cout << "  Previous Assessments:\n";
        for (size_t i = 0; i < studentResults.size(); ++i)
            cout << i + 1 << ". " << studentResults[i] << "\n";
    }

    cout << "\n  Press any key to continue...";
    _getch();
}
void student::changeCredentials(){
    system("CLS");
    fstream file("students.txt", ios::in);
    if (!file) {
        cerr << "Error opening teachers.txt!\n";
        system("pause");
        return;
    }

    // Read all teacher records
    vector<string> records;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) records.push_back(line);
    }
    file.close();

    string currentID = id;
    bool found = false;

    for (string &record : records) {
        stringstream ss(record);
        string id, first_name, last_name, username, password, course, section;
        getline(ss, id, ',');
        getline(ss, last_name, ',');
        getline(ss, first_name, ',');
        getline(ss, username, ',');
        getline(ss, course, ',');
        getline(ss, section, ',');
        getline(ss, password, ',');
        if (id == currentID) {
            found = true;

            cout << "\f\f\n================================================================================\n"
                 << "                          CHANGE CREDENTIALS\n"
                 << "================================================================================\n"
                 << "  Current Username: " << username << "\n"
                 << "  Current Password: " << password << "\n"
                 << "================================================================================\n";

            string newUsername, newPassword;

            cin.ignore();
            cout << "  Enter New Username (leave blank to keep current): ";
            getline(cin, newUsername);
            if (newUsername.empty()) newUsername = username;

            cout << "  Enter New Password (leave blank to keep current): ";
            getline(cin, newPassword);
            if (newPassword.empty()) newPassword = password;

            // Confirm before saving
            char confirm;
            cout << "\n  Confirm changes? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') {
                record = id + "," + last_name + ","+ first_name +"," + newUsername + "," + newPassword + "," + course + "," + section;
                cout << "\n  Credentials updated successfully!\n";
            } else if (confirm == 'N' || confirm == 'n'){
                cout << "\n  No changes were made.\n";
            }else { cout << "\nInvalid input!\n";}

            break;
        }
    }

    if (!found) {
        cout << "\n  Error: Teacher record not found.\n";
    } else {
        // Rewrite updated data to file
        ofstream out("students.txt", ios::trunc);
        for (auto &r : records) out << r << "\n";
        out.close();
    }
    cout << "\n";
    system("pause");
    system("CLS");
}
