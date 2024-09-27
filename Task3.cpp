#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileManager {
public:
    void createFile(const string& fileName) {
        ofstream file(fileName);
        if (file.is_open()) {
            cout << "File " << fileName << " created successfully!" << endl;
            file.close();
        } else {
            cerr << "Error creating file!" << endl;
        }
    }

    void writeFile(const string& fileName, const string& content) {
        ofstream file(fileName);
        if (file.is_open()) {
            file << content;
            cout << "Content written to " << fileName << endl;
            file.close();
        } else {
            cerr << "Error opening file!" << endl;
        }
    }

    void appendToFile(const string& fileName, const string& content) {
        ofstream file(fileName, ios::app);
        if (file.is_open()) {
            file << content;
            cout << "Content appended to " << fileName << endl;
            file.close();
        } else {
            cerr << "Error opening file for appending!" << endl;
        }
    }

    void readFile(const string& fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
            string line;
            cout << "Reading file " << fileName << ":\n";
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cerr << "Error opening file!" << endl;
        }
    }

    void deleteFile(const string& fileName) {
        if (remove(fileName.c_str()) == 0) {
            cout << "File " << fileName << " deleted successfully!" << endl;
        } else {
            cerr << "Error deleting file!" << endl;
        }
    }
};

int main() {
    FileManager fileManager;
    string fileName, content;

    int choice;
    do {
        cout << "\nFile Manager Menu:\n";
        cout << "1. Create a File\n";
        cout << "2. Write to a File\n";
        cout << "3. Append to a File\n";
        cout << "4. Read a File\n";
        cout << "5. Delete a File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            fileManager.createFile(fileName);
            break;
        case 2:
            cout << "Enter file name: ";
            cin >> fileName;
            cin.ignore();
            cout << "Enter content to write: ";
            getline(cin, content);
            fileManager.writeFile(fileName, content);
            break;
        case 3:
            cout << "Enter file name: ";
            cin >> fileName;
            cin.ignore();
            cout << "Enter content to append: ";
            getline(cin, content);
            fileManager.appendToFile(fileName, content);
            break;
        case 4:
            cout << "Enter file name: ";
            cin >> fileName;
            fileManager.readFile(fileName);
            break;
        case 5:
            cout << "Enter file name: ";
            cin >> fileName;
            fileManager.deleteFile(fileName);
            break;
        case 6:
            cout << "Exiting file manager..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
