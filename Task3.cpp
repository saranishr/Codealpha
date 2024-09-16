#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

// Function prototypes
void showMenu();
void changeDirectory();
void viewFiles();
void createDirectory();
void copyFile();
void moveFile();
string getCurrentPath();

int main() {
    int choice;

    while (true) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: changeDirectory(); break;
            case 2: viewFiles(); break;
            case 3: createDirectory(); break;
            case 4: copyFile(); break;
            case 5: moveFile(); break;
            case 0: return 0; // Exit the program
            default: cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

void showMenu() {
    cout << "\nFile Manager Menu:\n";
    cout << "1. Change Directory\n";
    cout << "2. View Files\n";
    cout << "3. Create Directory\n";
    cout << "4. Copy File\n";
    cout << "5. Move File\n";
    cout << "0. Exit\n";
}

void changeDirectory() {
    string path;
    cout << "Enter the directory path: ";
    cin.ignore(); // To ignore leftover newline character
    getline(cin, path);

    try {
        fs::current_path(path);
        cout << "Directory changed to: " << fs::current_path() << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void viewFiles() {
    cout << "Files in directory: " << fs::current_path() << "\n";
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << "\n";
    }
}

void createDirectory() {
    string dirName;
    cout << "Enter the new directory name: ";
    cin.ignore(); // To ignore leftover newline character
    getline(cin, dirName);

    try {
        if (fs::create_directory(dirName)) {
            cout << "Directory created successfully.\n";
        } else {
            cout << "Directory already exists.\n";
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void copyFile() {
    string sourceFile, destFile;
    cout << "Enter the source file path: ";
    cin.ignore(); // To ignore leftover newline character
    getline(cin, sourceFile);
    cout << "Enter the destination file path: ";
    getline(cin, destFile);

    try {
        fs::copy(sourceFile, destFile);
        cout << "File copied successfully.\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void moveFile() {
    string sourceFile, destFile;
    cout << "Enter the source file path: ";
    cin.ignore(); // To ignore leftover newline character
    getline(cin, sourceFile);
    cout << "Enter the destination file path: ";
    getline(cin, destFile);

    try {
        fs::rename(sourceFile, destFile);
        cout << "File moved successfully.\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

string getCurrentPath() {
    return fs::current_path().string();
}

