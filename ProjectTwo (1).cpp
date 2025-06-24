//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Nicole Hutto
// Version     : 1.0
// Description : CS300 Project 2 
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course) {
        if (course.courseId < node->course.courseId) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            } else {
                addNode(node->left, course);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            } else {
                addNode(node->right, course);
            }
        }
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseId << ": " << node->course.title << endl;
            inOrder(node->right);
        }
    }

    Course search(Node* node, string courseId) {
        if (node == nullptr) return Course();
        if (node->course.courseId == courseId) return node->course;
        if (courseId < node->course.courseId) return search(node->left, courseId);
        return search(node->right, courseId);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        } else {
            addNode(root, course);
        }
    }

    void printCourseList() {
        inOrder(root);
    }

    Course getCourse(string courseId) {
        return search(root, courseId);
    }
};

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void loadCourses(const string& filename, BinarySearchTree& bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> parts = split(line, ',');
        Course course;
        course.courseId = parts[0];
        course.title = parts[1];
        for (size_t i = 2; i < parts.size(); ++i) {
            course.prerequisites.push_back(parts[i]);
        }
        bst.insert(course);
    }
    file.close();
    cout << "Courses loaded successfully.\n";
}

void printCourseDetails(Course course) {
    if (course.courseId.empty()) {
        cout << "Course not found.\n";
        return;
    }
    cout << course.courseId << ": " << course.title << endl;
    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (const string& prereq : course.prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    } else {
        cout << "No prerequisites.\n";
    }
}

int main() {
    BinarySearchTree bst;
    string filename;
    int choice = 0;

    while (choice != 9) {
        cout << "\nMenu:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename: ";
            cin >> filename;
            loadCourses(filename, bst);
            break;
        case 2:
            bst.printCourseList();
            break;
        case 3: {
            string courseId;
            cout << "Enter course ID: ";
            cin >> courseId;
            Course course = bst.getCourse(courseId);
            printCourseDetails(course);
            break;
        }
        case 9:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    }
    return 0;
}
