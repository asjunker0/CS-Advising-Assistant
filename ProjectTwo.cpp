//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Abbigale Junker
// Description : 7-1 Project Two (I am very proud of this project! c: )
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Structure to hold course information
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};


class HashTable {

private:
    // Structures to hold courses
    struct Node {
        Course course;
        unsigned int key;
        Node* next;

        // Default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // Initialize with a course
        Node(Course aCourse) : Node() {
            course = aCourse;
            key = UINT_MAX;
            next = nullptr;
        }

        // Initialize with a coures and key
        Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
            course = aCourse;
            key = aKey;
            next = nullptr;
        }
    };
    // The hash table of nodes
    vector<Node> nodes;
    // Size of hash table
    unsigned int tableSize;
    // Hash function to map string courseNumber to index
    unsigned int hashFunction(const string& courseNumber) const;

public:
    HashTable();
    HashTable(unsigned int size);
    ~HashTable();

    // Loads coure data from the CSV
    void loadFromFile(const string& filename);

    // Prints all courses sorted in alphanumeric order
    void printAllCourses();

    // Prints details of a single course
    void printCourseDetails(const string& courseNumber);
};

HashTable::HashTable() {
    tableSize = 11; // Default prime number
    nodes.resize(tableSize);
};

HashTable::HashTable(unsigned int size) {
    this->tableSize = size;
    nodes.resize(tableSize);
};

HashTable::~HashTable() {
    for (unsigned int i = 0; i < tableSize; i++) { // loop through each bucket
        Node* current = nodes[i].next; // starts at first linked node
        while (current != nullptr) { // traverses through and deletes nodes
            Node* temp = current; // stores current node
            current = current->next; // moves to next node
            delete temp; // deletes current node
        }
        nodes[i].next = nullptr; // sets head node's pointer again
    }
    nodes.clear();  // Clears the vector
};

// Helper function so we can search for course details with lowercase letters
string toUpperCase(const string& str) {
    string upperStr = str;
    for (char& c : upperStr) {
        c = toupper(c);
    }
    return upperStr;
}

void HashTable::loadFromFile(const string& filename) {
    ifstream file(filename);
    // File validation
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNum, title, prereq;
        vector<string> prereqs;

        // Reads course number and title
        getline(ss, courseNum, ',');
        getline(ss, title, ',');

        // Reads prerequisites if available
        while (getline(ss, prereq, ',')) {
            if (!prereq.empty()) {
                prereqs.push_back(prereq);
            }
        }

        // Creating a course
        Course newCourse = { courseNum, title, prereqs };
        unsigned int index = hashFunction(courseNum);

        // Inserting into hash table
        Node* current = &nodes[index];
        if (current->key == UINT_MAX) {
           *current = Node(newCourse, index);
        }
        else {
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(newCourse, index);
        }
        count++;
    }
    file.close();
    cout << count << " courses loaded" << endl;
};

void HashTable::printAllCourses() {
    // Checks if hash table is empty
    bool isEmpty = true;
    for (const Node& node : nodes) {
        if (node.key != UINT_MAX) {
            isEmpty = false;
            break;
        }
    }

    if (isEmpty) {
        cout << "No courses loaded. Choose option 1 to load courses." << endl;
        return;
    }

    vector<Course> courses;

    // Gets courses from hash table
    for (const Node& node : nodes) {
        if (node.key != UINT_MAX) {
            courses.push_back(node.course);
            Node* current = node.next;
            while (current != nullptr) {
                courses.push_back(current->course);
                current = current->next;
            }
        }
    }

    // Sorts courses with bubble sort
    size_t n = courses.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (courses[j].courseNumber > courses[j + 1].courseNumber) {
                // Swap course
                Course temp = courses[j];
                courses[j] = courses[j + 1];
                courses[j + 1] = temp;
            }
        }
    }

    // Prints all courses
    cout << "Here is a sample schedule: " << endl << endl;
    for (const Course& course : courses) {
        cout << course.courseNumber << ", " << course.title << endl;
    }
    cout << endl;
};

void HashTable::printCourseDetails(const string& courseNumber) {
    unsigned int index = hashFunction(courseNumber);
    Node* current = &nodes[index];

    // To track if course is found
    bool courseFound = false;

    // Traverse hash table
    while (current != nullptr) {
        if (toUpperCase(current->course.courseNumber) == toUpperCase(courseNumber)) {
            // Course found
            courseFound = true;
            cout << current->course.courseNumber << ", " << current->course.title << endl;
            cout << "Prerequisites: ";

            if (current->course.prerequisites.empty()) {
                cout << "No prerequisites";
            }
            else {
                for (size_t i = 0; i < current->course.prerequisites.size(); i++) {
                    cout << current->course.prerequisites[i];
                    if (current->course.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << endl << endl;
            return;
        }
    current = current->next;
    }
    if (!courseFound) {
        cout << courseNumber << " was not found." << endl;
    }
};

// Converts course string number into hash index
unsigned int HashTable::hashFunction(const string& courseNumber) const {
    unsigned int hashValue = 5381;
    // Loops through each character in courseNumber
    for (char ch : courseNumber) {
        // Converts each character to ASCII value
        hashValue = ((hashValue << 5) + hashValue) + ch;
    }
    // Return while keeping index within bounds
    return hashValue % tableSize;
};

int main() {
    cout << "Welcome to the course planner. \n \n";
    HashTable courseTable;
    int choice = 0;
    while (choice != 9) {
        // Print menu options
        cout << "  1. Load Data Structure\n";
        cout << "  2. Print Course List\n";
        cout << "  3. Print Course\n";
        cout << "  9. Exit\n \n";
        cout << "What would you like to do? ";

        // Input validation
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number. \n \n";

            // Clear error flag on cin
            cin.clear();
            // Ignore invalid inuput
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Restart loop
            continue;
        }

        switch (choice) {
        case 1:
            // Call function to load data
            courseTable.loadFromFile("CS 300 ABCU_Advising_Program_Input.csv");
            break;
        case 2:
            // Call function to display all courses
            courseTable.printAllCourses();
            break;
        case 3:
        {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;

            // Uppercase user input for comparison
            courseNumber = toUpperCase(courseNumber);

            // Input validation for if input is empty
            if (courseNumber.empty()) {
                cout << "Invalid input, course number cannot be empty. \n \n";
                continue;
            }

            // Input validation to check that input only contains letters and numbers
            for (char c : courseNumber) {
                if (!isalnum(c)) {
                    cout << "Invalid input, course number must contain only letters and numbers. \n \n";
                    continue;
                }
            }

            // Call function to display courses
            courseTable.printCourseDetails(courseNumber);
        }
        break;
        default:
            cout << choice << " is not a valid option. \n \n";
        }
    }
    cout << "Thank you for using the course planner!" << endl;
    return 0;
};